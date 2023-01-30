"""
this script generates an operators.h file from an input .txt file

operators.h has a lot of repetitive exhaustive code that, due to the
implementation of std::variant, cannot be meaningfully reduced

this script is messy as fuck, and that fine
very exhaustive TODO: clean up and comment this code but!
it works! and thats all that really matters

example .txt file:
print (arg)
    null: std::cout << "NULL\n";
    default: std::cout << arg << '\n';

plus (x)
    numeric: return +x;
plus (x, y)
    numeric, numeric: return x + y;
    string, string: return x + y;

current command:
py .\src\operator_generator.py "src\operators.txt" "src\operators.h"
"""

from sys import argv
from typing import List, TextIO
import re


includes = [
    '<iostream>',
    '"src/tokens.h"',
    ]

keytypes = {
    'numeric': ['int', 'rational', 'float'],
    'null': ['nulltype'],
    'string': ['std::string'],
    'default': ['auto'],
    }


def generate_function(types: List[str], args: List[str],
                      operations: List[str]) -> List[str]:
    """Creates line by line list of a c++ operator() function
    """
    type_args = f'{types[0]} {args[0]}, {types[1]} {args[1]}'

    ret = [f'\tLiteral operator()({type_args}) {{']
    for operation in operations:
        ret.append('\t\t' + operation)
    ret.append('\t}')

    return ret


def format_packages(file: TextIO) -> List[List[str]]:
    """Splits packages into their header and functions
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
            # keep track of current whitespace so we know when indenting stops
            whitespace = len(line) - len(line.lstrip())
            current_package.append(line.strip())
        elif match_indented.match(line):
            if len(line) - len(line.lstrip()) > whitespace != 0:
                # if we haven't stopped indenting, just tack onto the end
                current_package[-1] += line.strip()
            else:
                current_package.append(line.strip())
                whitespace = 0
        else:
            packages.append(current_package)
            current_package = [line]
    packages.append(current_package)
    # first package is always empty, discard
    return packages[1:]


def parse(file: TextIO) -> List[str]:
    formatted_packages = format_packages(file)
    parsed_packages = {}
    split_type_args = re.compile(r'\s*[(),]\s*')
    split_type_operations = re.compile(r'\s*:\s*')
    split_types = re.compile(r'\s*,\s*')
    split_newlines = re.compile(r'\n')
    remove_override = re.compile(r'\s*override\s+')
    for package in formatted_packages:
        # add '(,' to ensure theres always enough blanks to cut down with [:3]
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
            if len(types) == 1:
                types = ['nulltype'] + types
            operations = split_newlines.split(operations)
            type_alias = [keytypes.get(types[0], [types[0]]),
                           keytypes.get(types[1], [types[1]])]
            type_pairs = [[i,j] for i in type_alias[0] for j in type_alias[1]]
            if not was_overridden:
                type_pairs = [p for p in type_pairs if p not in override]
            else:
                override += type_pairs
            for pair in type_pairs:
                functions += generate_function(pair, args, operations)

        if not parsed_packages.get(name):
            parsed_packages[name] = []
        parsed_packages[name] += functions

    lines = []
    for name, package in parsed_packages.items():
        name = name.upper()
        lines += [f'struct OPERATOR_{name}_PACKAGE {{',
                  '\tLiteral operator()(auto, auto) {',
                  '\t\treturn nulltype();  // ERROR',
                  '\t}']
        lines += package
        lines.append('};\n')
        lines.append(f'Literal OPERATOR_{name}(Literal l, Literal r) {{')
        lines.append(f'\treturn std::visit(OPERATOR_{name}_PACKAGE(), l, r);')
        lines.append('}')

    return lines


if __name__ == '__main__':
    program_path, ifile_path, ofile_path = argv
    header_path = re.sub(r'[\\\.]', '_', ofile_path + '_').upper()
    ifile = open(ifile_path, 'r')
    ofile = open(ofile_path, 'w')

    ofile.write(f'#ifndef {header_path}\n#define {header_path}\n\n')

    for include in includes:
         ofile.write(f'#include {include}\n')
    ofile.write('\n')

    for parsed_line in parse(ifile):
        ofile.write(parsed_line + '\n')

    ofile.write(f'#endif  // {header_path}')

    ifile.close()
    ofile.close()
