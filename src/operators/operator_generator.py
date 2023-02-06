"""This script generates a .h file from an input .txt file to create operator
functionality.

"operators.h" has a lot of repetitive, exhaustive code that, due to the
implementation of std::variant, cannot be meaningfully reduced. This code aims
to provide a solution by generating the repetitive code in many fewer lines.

=== Usage ===
py cwd/path/operator_generator.py -p "path" -i "input" -o "output"
-p: Specifies the path for the input and output files, relative to the cwd.
    If not specified defaults to the directory of this script.
    Used in header guard.
-i: Specifies the name of the input file. Assumes .txt if no extension written.
    Assumes operators.txt if unspecified. Relative to path.
-o: Specifies the name of the output file. Assumes .h if no extension written.
    Assumes operators.h if unspecified. Relative to path.

=== Syntax ===
name_monad (arg)
    [override] type: operation;
name_dyad (x, y)
    [override each] type, type:
        operation;
        operation;

Names are case-insensitive. If both names are the same, the monadic and dyadic
implementation are put into the same package.

=== Keywords ===
each: in a dyadic operator, mirrors the code for each permutation of types
override: if a specific type combination is to be defined later, prevents
          the new definition
          e.g: override real: do something; numeric: do something else;
"""


import sys
import os
from typing import List, TextIO, Tuple
import re


DEFAULT_INPUT_FILENAME = DEFAULT_OUTPUT_FILENAME = 'operators'
DEFAULT_INPUT_EXTENSION = '.txt'
DEFAULT_OUTPUT_EXTENSION = '.h'
DEFAULT_RELATIVE_WORKING_PATH = os.path.relpath(os.path.dirname(__file__))

INCLUDES = [
    '<iostream>',
    '"src/tokens.h"',
    '"src/types/types.h"',
    '"src/type_definitions.h"'
    ]

TYPEDEFS = {
    'null': ['Null'],
    'bool': ['TYPE_BOOL'],
    'int': ['TYPE_INT'],
    'real': ['TYPE_REAL'],
    'string': ['std::string'],
    'set': ['Set'],

    'default': ['auto'],
    'numeric': ['TYPE_INT', 'Rational', 'TYPE_REAL'],
    }


def generate_function(types: List[str], args: List[str],
                      operations: List[str]) -> List[str]:
    """Creates line by line list of a c++ operator() function

    >>> generate_function(['nulltype', 'int'], ['', 'x'], ['return +x;\\n'])
    ['\\tLiteral operator()(nulltype, int x) {', '\\t\\treturn +x;\\n', '\\t}']
    """
    if args[0] != '':
        args[0] = ' ' + args[0]
    if args[1] != '':
        args[1] = ' ' + args[1]
    type_args = f'{types[0]}{args[0]}, {types[1]}{args[1]}'
    ret = [f'\tLiteral operator()({type_args}) {{']
    for operation in operations:
        ret.append('\t\t' + operation)
    ret.append('\t}')
    return ret


def format_packages(file: TextIO) -> List[List[str]]:
    """Splits file into head-function package prototypes

    >>> from io import StringIO
    >>> t = '''
    ... foo (arg)
    ...     string: return 'foo' + arg;
    ... bar (arg)
    ...     numeric:
    ...         bar = 'bar' + (char) arg;
    ...         return 'foo' + bar;'''
    >>> f = StringIO(t)
    >>> format_packages(f)
    [\
['foo (arg)\\n', \
"string: return 'foo' + arg;\\n"], \
['bar (arg)\\n', \
"numeric: bar = 'bar' + (char) arg;\\nreturn 'foo' + bar;\\n"]]
    """
    packages = []
    current_package = []
    whitespace = 0

    match_blank = re.compile(r'\s*')
    match_multi_line_start = re.compile(r'.+:\n')
    match_indented = re.compile(r'\s+')

    for line in file:
        if match_blank.fullmatch(line):
            continue
        elif match_multi_line_start.fullmatch(line):
            # keep track of current whitespace, so we know when indenting stops
            whitespace = len(line) - len(line.lstrip())
            current_package.append(line.strip() + ' ')
        elif match_indented.match(line):
            if len(line) - len(line.lstrip()) > whitespace != 0:
                # if we haven't stopped indenting, just tack onto the end
                current_package[-1] += line.strip() + '\n'
            else:
                current_package.append(line.strip() + '\n')
                whitespace = 0
        else:
            packages.append(current_package)
            current_package = [line]
    packages.append(current_package)
    # first package is always empty, discard
    return packages[1:]


def parse(file: TextIO) -> List[str]:
    """Turns a file into a line by line list of operator packages

    >>> from io import StringIO
    >>> t = '''
    ... foo (arg)'''
    >>> f = StringIO(t)
    >>> parse(f)
    [\
'struct OPERATOR_FOO_PACKAGE {', \
'\\tLiteral operator()(auto, auto) {', \
'\\t\\treturn Null();  // ERROR', \
'\\t}', '};\\n', 'Literal OPERATOR_FOO(Literal l, Literal r) {', \
'\\treturn std::visit(OPERATOR_FOO_PACKAGE(), l, r);', \
'}\\n\\n']
    """
    formatted_packages = format_packages(file)
    parsed_packages = {}
    split_type_args = re.compile(r'\s*[(),]\s*')
    split_type_operations = re.compile(r'\s*:\s*')
    split_types = re.compile(r'\s*,\s*')
    split_newlines = re.compile(r'\n')
    remove_override = re.compile(r'\s*override\s+')
    remove_each = re.compile(r'\s*each\s+')
    for package in formatted_packages:
        # add '(,' to ensure there's always enough blanks to cut down with [:3]
        name, left, right = split_type_args.split(package[0] + '(,')[:3]
        if right:
            args = [left, right]
        elif left:
            args = ['', left]
        else:
            args = ['', '']
        functions = []

        override = []
        for func in package[1:]:
            types, operations = split_type_operations.split(func, 1)
            types = split_types.split(types.strip())
            overridden = remove_override.sub('', types[0])
            was_overridden = types[0] != overridden
            types[0] = overridden
            each = remove_each.sub('', types[0])
            was_each = types[0] != each
            types[0] = each
            if len(types) == 1:
                types = ['null'] + types
            operations = split_newlines.split(operations.strip())
            type_alias = [TYPEDEFS.get(types[0], [types[0]]),
                          TYPEDEFS.get(types[1], [types[1]])]
            type_pairs = [[i, j] for i in type_alias[0] for j in type_alias[1]]
            if not was_overridden:
                type_pairs = [p for p in type_pairs if p not in override]
            else:
                override += type_pairs
            for pair in type_pairs:
                functions += generate_function(pair, args, operations)
                if was_each and pair[0] != pair[1]:
                    functions += generate_function([pair[1], pair[0]],
                                                   args, operations)

        if not parsed_packages.get(name):
            parsed_packages[name] = []
        parsed_packages[name] += functions

    lines = []
    for name, package in parsed_packages.items():
        name = name.upper()
        lines += [f'struct OPERATOR_{name}_PACKAGE {{',
                  '\tLiteral operator()(auto, auto) {',
                  '\t\treturn Null();  // ERROR',
                  '\t}']
        lines += package
        lines.append('};\n')
        lines.append(f'Literal OPERATOR_{name}(Literal l, Literal r) {{')
        lines.append(f'\treturn std::visit(OPERATOR_{name}_PACKAGE(), l, r);')
        lines.append('}\n\n')

    return lines


def get_args(arg_str: str):
    """Gets file arguments from a string

    >>> get_args('-i INPUT -k ./PATH/')
    {'i': 'INPUT', 'k': './PATH/'}
    """
    arg_pattern = re.compile(r'-(.)?\s*(?!-)(\S+)?')
    return {k: v for k, v in arg_pattern.findall(arg_str)}


def get_paths(input_filename: str, output_filename: str,
              relative_working_path: str) -> Tuple[str, str]:
    """Returns the paths used for input and output files
    """
    ipath = relative_working_path + '\\' + input_filename
    if os.path.splitext(ipath)[1] == '':  # no extension provided
        ipath += DEFAULT_INPUT_EXTENSION
    opath = relative_working_path + '\\' + output_filename
    if os.path.splitext(opath)[1] == '':
        opath += DEFAULT_OUTPUT_EXTENSION
    return ipath, opath


if __name__ == '__main__':
    # import doctest
    # doctest.testmod()

    file_args = get_args(' '.join(sys.argv[1:]))
    input_path, output_path = get_paths(
        file_args.get('i', DEFAULT_INPUT_FILENAME),
        file_args.get('o', DEFAULT_OUTPUT_FILENAME),
        file_args.get('p', DEFAULT_RELATIVE_WORKING_PATH))
    header_path = re.sub(r'[\\.]', '_', output_path + '_').upper()

    input_file = open(input_path, 'r')
    output_file = open(output_path, 'w')

    output_file.write(f'#ifndef {header_path}\n#define {header_path}\n\n')

    for include in INCLUDES:
        output_file.write(f'#include {include}\n')
    output_file.write('\n')

    for parsed_line in parse(input_file):
        output_file.write(parsed_line + '\n')

    output_file.write(f'#endif  // {header_path}\n')

    input_file.close()
    output_file.close()
