"""Copyright Leo Peckham 2023

This script generates a .h file from an input .txt file to create operator
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
override: if a specific type combination is to be defined later, prevents
          the new definition
          e.g: in `override real: do something; numeric: do something else;`
               numeric does not create a definition for reals.
each: in a dyadic operator, mirrors the code for each permutation of types
promote: (dyadic) promote both types to their greatest common type
               before operation
               e.g: `promote int, float: x + y` is equivalent to
                    `int, float: (float) x + y`

TODO: set[type]: overrides how sets work (MIGHT NOT BE NECESSARY)
TODO: something to reduce 'return arg' usage
TODO: comment everything
TODO: error handeling
"""


"""
times (x, y)
    promote int, float: x * y;

GENERATES:
struct OPERATOR_TIMES_PACKAGE {
    Literal operator(SN_int x_, SN_float y_) {
        SN_float x = static_cast<SN_float>(x_)
        x * y;
    }
}
"""





"""
IMPORTS
"""


import sys
import os
from typing import Dict, TypedDict, List, TextIO, Tuple, Iterable
import re




"""
CONSTANTS
"""


DEFAULT_INPUT_FILENAME = DEFAULT_OUTPUT_FILENAME = 'operators'
DEFAULT_INPUT_EXTENSION = '.txt'
DEFAULT_RELATIVE_WORKING_PATH = os.path.relpath(os.path.dirname(__file__))

INCLUDES = [
    '<iostream>',
    '"src/parser/tokens.h"',
    '"src/types/types.h"',
    '"src/type_definitions.h"',
    '"src/parser/expression.h"',
    '"src/parser/phrase.h"'
    ]

TYPES = {
    'null': ['Null'],
    'bool': ['SN_bool'],
    'int': ['SN_int'],
    'rational': ['Rational'],
    'real': ['SN_real'],
    'string': ['std::wstring'],
    'set': ['Set'],

    'default': ['auto'],
    'numeric': ['SN_int', 'Rational', 'SN_real'],
    }

PROMOTE_ORDER = (
    'SN_int',
    'Rational',
    'SN_real',
    )

KEYWORDS = [
    'override',
    'each',
    'promote',
    ]




"""
FILE ARGUMENT AND PATH READING
"""

def get_file_args(arg_str: str):
    """Gets file arguments from a string

    >>> get_args('-i INPUT -k ./PATH/')
    {'i': 'INPUT', 'k': './PATH/'}
    """
    arg_pattern = re.compile(r'-(.)?\s*(?!-)(\S+)?')
    return {k: v for k, v in arg_pattern.findall(arg_str)}


def get_file_paths(input_filename: str, output_filename: str,
              relative_working_path: str) -> Tuple[str, str, str]:
    """Returns the paths used for input and output files
    """
    ipath = relative_working_path + '\\' + input_filename
    if os.path.splitext(ipath)[1] == '':  # no extension provided
        ipath += DEFAULT_INPUT_EXTENSION
    opath = relative_working_path + '\\' + output_filename
    hopath = opath + '.h'
    cppopath = opath + '.cpp'
    return ipath, hopath, cppopath




"""
REGEX UTILITY
"""


def _re_all_of(iterator: Iterable[str]):
    """Makes an "or" group in regex from a string iterator"""
    return f'(({")|(".join(iterator)}))'


PACKAGE_PATTERN = re.compile(rf'''(
    [ \t]*(?P<name>\w+)
    (
        [ \t]*\(
        [ \t]*(?P<left>\w*)
        (
            [ \t]*,
            [ \t]*(?P<right>\w*)
        )?
        [ \t]*\)
    )
    ([ \t]*\n)+

    (?P<functions>
        (
            (?P<indent> [ \t]*)
            ({_re_all_of(KEYWORDS)}[ \t]+)*
            {_re_all_of(TYPES)} ([ \t]*{_re_all_of(TYPES)})? [ \t]* : .*\n
            ( ((?P=indent) [ \t]+.*?\n) | ([ \t]*?\n) )* 
        )+
    )
    )''', re.VERBOSE)
 
 
FUNCTION_PATTERN = re.compile(rf'''(
    ([ \t]*\n)*
    (?P<indent> [ \t]*)
    (?P<flags> ({_re_all_of(KEYWORDS)}[ \t]+)* )
    (?P<types> {_re_all_of(TYPES)} ([ \t]*{_re_all_of(TYPES)})?) [ \t]* : [ \t]*
    (?P<inline> .*?)\n
    ([ \t]*\n)*
    (?P<operations>(( (?P<real_indent>(?P=indent) [ \t]+).+\n ) | ([ \t]*?\n) )*)
    ([ \t]*\n)*
    )''', re.VERBOSE)




"""
DATATYPES
"""


ArgInfo = Tuple[str, str]


class FunctionInfo(TypedDict):
    flags: List[str]
    types: Tuple[str, str]
    operations: List[str]


class PackageInfo(TypedDict):
    args: ArgInfo
    functions: List[FunctionInfo]




"""
PARSING
"""


def parse_function(match: re.Match) -> FunctionInfo:
    func = match.groupdict()

    flags = func['flags'].split()
    types = func['types'].split()
    if len(types) == 1:
        types.insert(0, 'null')

    if func['inline'] != '' and func['operations'] != '':
        print(f'''SYNTAX ERROR: do not provide both inline and block operations
                  \t{match.string}''')
        raise SyntaxError
    elif func['inline'] != '':
        operations = [func['inline'].strip()]
    elif func['operations'] != '':
        operations = [op.replace(func['real_indent'], '', 1)
                      for op in func['operations'].split('\n')
                      if op != '']

    return {'flags': flags,
            'types': types,
            'operations': operations}


def parse_package(match: re.Match) -> Tuple[str, PackageInfo]:
    package = match.groupdict()

    name = package['name'].upper()

    left: str
    right: str
    if package['right'] is not None:
        left, right = package['left'], package['right']
    else:
        left, right = '', package['left']
    args = left, right

    functions: List[FunctionInfo] = []
    for func in FUNCTION_PATTERN.finditer(package['functions']):
        functions.append(parse_function(func))

    return name, {'args': args, 'functions': functions}


def parse(file: TextIO) -> Dict[str, List[PackageInfo]]:
    packages: Dict[str, List[PackageInfo]] = {}
    for package in PACKAGE_PATTERN.finditer(file.read()):
        name, info = parse_package(package)
        if packages.get(name):
            packages[name].append(info)
        else:
            packages[name] = [info]
    return packages




"""
C++ CODE GENERATION
"""


def generate_copyright() -> List[str]:
    return ['// Copyright 2023 Leo Peckham']

 
def generate_header_guard(path: str) -> Tuple[List[str], List[str]]:
    header_path = re.sub(r'[\\.]', '_', path + '_').upper()
    return [f'#ifndef {header_path}',
            f'#define {header_path}'],\
           [f'#endif  // {header_path}']


def normalize_types(functions: List[FunctionInfo]) -> List[FunctionInfo]:
    id_expanded: Dict[Tuple[str, str], int] = {}

    for i, func in enumerate(functions):
        left_types = TYPES[func['types'][0]]
        right_types = TYPES[func['types'][1]]
        expanded = {(l, r): i for l in left_types for r in right_types}

        if 'each' in func['flags']:
            expanded.update({(r, l): i for l, r in expanded if l != r})

        if 'override' in func['flags']:
            id_expanded.update(expanded)
        else:
            id_expanded.update({k: v for k, v in expanded.items()
                                   if k not in id_expanded})

    return [{'flags': functions[v]['flags'],
            'types': k,
            'operations': functions[v]['operations']}
            for k, v in id_expanded.items()]


def generate_includes():
    return [f'#include {include}' for include in INCLUDES]


def generate_function(args: ArgInfo, func: FunctionInfo) -> List[str]:
    left_arg, right_arg = args
    left_type, right_type = func['types']
    ls = ' ' if left_arg else ''
    rs = ' ' if right_arg else ''

    promotion: str = ''
    if 'promote' in func['flags']:
        if left_type not in PROMOTE_ORDER:
            print(f'PROMOTE_ERROR: {left_type} cannot be promoted\n\t{func}')
            raise Exception
        if right_type not in PROMOTE_ORDER:
            print(f'PROMOTE_ERROR: {right_type} cannot be promoted\n\t{func}')
            raise Exception

        li = PROMOTE_ORDER.index(left_type)
        ri = PROMOTE_ORDER.index(right_type)
        if li < ri:
            promotion = (f'{right_type} {left_arg} = '
                         f'static_cast<{right_type}>({left_arg + "_"});')
            left_arg += '_'
        elif ri < li:
            promotion = (f'{left_type} {right_arg} = '
                         f'static_cast<{left_type}>({right_arg + "_"});')
            right_arg += '_'

    type_args = f'{left_type + ls + left_arg}, {right_type + rs + right_arg}'
    return [f'Literal operator()({type_args}) {{'] + \
           ([f'\t{promotion}'] if promotion != '' else []) + \
           [f'\t{operation}' for operation in func['operations']] + \
           [f'}}']


def generate_package(name: str, infos: List[PackageInfo]) -> List[str]:
    functions: List[str] = []
    for info in infos:
        for func in normalize_types(info['functions']):
            functions += generate_function(info['args'], func) + ['']
    return [f'struct OPERATOR_{name}_PACKAGE {{'] + \
           ['\tLiteral operator()(auto, auto) { return Null(); }  // Error'] + \
           ['\t' + l for l in functions[:-1]] + ['};'] + [''] + \
           generate_operator(name)


def generate_operator(name: str) -> List[str]:
    return [f'Literal OPERATOR_{name}(Literal l, Literal r) {{',
            f'\treturn std::visit(OPERATOR_{name}_PACKAGE(), l, r);',
            '}']


def generate_cpp_file(packages: Dict[str, List[PackageInfo]],
                  h_path: str) -> List[str]:
    cpp_packages = sum([generate_package(k, v) + \
                        ['', ''] 
                        for k, v in packages.items()], [])
    return generate_copyright() + ['', ''] + \
           [f'#include "{h_path}"', '', ''] + \
           cpp_packages

def generate_h_file(packages: Dict[str, List[PackageInfo]],
                    h_path: str) -> List[str]:
    start_guard, end_guard = generate_header_guard(h_path)
    function_defs: List[str] = []
    for name in packages.keys():
        function_defs += [f'Literal OPERATOR_{name}(Literal l, Literal r);']
        function_defs += ['']
    return generate_copyright() + ['', ''] + \
           start_guard + ['', ''] + \
           generate_includes() + ['', ''] + \
           function_defs + [''] + \
           end_guard + ['']




"""
MAIN
"""

if __name__ == '__main__':
    file_args = get_file_args(' '.join(sys.argv[1:]))
    input_path, h_output_path, cpp_output_path = get_file_paths(
        file_args.get('i', DEFAULT_INPUT_FILENAME),
        file_args.get('o', DEFAULT_OUTPUT_FILENAME),
        file_args.get('p', DEFAULT_RELATIVE_WORKING_PATH))

    input_file = open(input_path, 'r')
    h_output_file = open(h_output_path, 'w')
    cpp_output_file = open(cpp_output_path, 'w')

    parsed_packages = parse(input_file)

    h_output_file.write(
        '\n'.join(generate_h_file(parsed_packages, h_output_path)))
    cpp_output_file.write(
        '\n'.join(generate_cpp_file(parsed_packages, h_output_path)))

    input_file.close()
    h_output_file.close()
    cpp_output_file.close()
