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
    "<iostream>",
    "\"src/tokens.h\""
    ]

keytypes = {
    "numeric": ["int", "float"],
    "null": ["nulltype"],
    "string": ["std::string"],
    "default": ["auto"],
    }


def generate_function(types: List[str], args: List[str],
                      operations: List[str]) -> List[str]:
    """Creates line by line list of a c++ operator() function
    """
    arity = len(types)
    if len(args) == 1:
        args = ["_"] + args

    type_args = f"{types[0]} {args[0]}, {types[1]} {args[1]}"

    ret = [f"\tauto operator()({type_args}) {{"]
    for operation in operations:
        ret.append("\t\t" + operation)
    ret.append("\t}")

    return ret


def format_packages(file: TextIO) -> List[List[str]]:
    packages = []
    current_package = []
    whitespace = 0
    for line in file:
        if re.fullmatch('\\s*', line):
            continue
        elif re.fullmatch('.+:\n', line):
            whitespace = len(line) - len(line.lstrip())
            current_package.append(line.strip())
        elif re.match('\\s+', line):
            if len(line) - len(line.lstrip()) > whitespace != 0:
                current_package[-1] += line.strip()
            else:
                current_package.append(line.strip())
                whitespace = 0
        else:
            packages.append(current_package)
            current_package = [line]
    packages.append(current_package)
    return packages[1:]


def parse(file: TextIO) -> List[str]:
    formatted_packages = format_packages(file)
    parsed_packages = {}
    for package in formatted_packages:
        name, left, right = re.split("\\s*[(),]\\s*", package[0] + "(,")[:3]
        if right:
            args = [left, right]
        elif left:
            args = [left]
        else:
            args = []
        functions = []

        for func in package[1:]:
            types, operations = re.split("\\s*:\\s*", func, 1)
            types = re.split("\\s*,\\s*", types.strip())
            if len(types) == 1:
                types = ["nulltype"] + types
            operations = re.split("\n", operations)
            types_alias = [keytypes.get(types[0], [types[0]]),
                           keytypes.get(types[1], [types[1]])]
            types_pairs = [[i,j] for i in types_alias[0] for j in types_alias[1]]
            for pair in types_pairs:
                functions += generate_function(pair, args, operations)

        if not parsed_packages.get(name):
            parsed_packages[name] = []
        parsed_packages[name] += functions

    lines = []
    for name, package in parsed_packages.items():
        lines += [f"struct OPERATOR_{name.upper()}_PACKAGE {{",
                  "\tauto operator()(auto, nulltype) { /* ERROR */ }"]
        lines += package
        lines += ["};\n"]

    return lines


if __name__ == "__main__":
    program_path, ifile_path, ofile_path = argv
    header_path = re.sub('[\\\.]', '_', ofile_path + '_').upper()
    ifile = open(ifile_path, 'r')
    ofile = open(ofile_path, 'w')

    ofile.write(f"#ifndef {header_path}\n#define {header_path}\n\n")

    for include in includes:
         ofile.write(f"#include {include}\n")
    ofile.write('\n')

    for parsed_line in parse(ifile):
        ofile.write(parsed_line + '\n')

    ofile.write(f"#endif  // {header_path}")

    ifile.close()
    ofile.close()
