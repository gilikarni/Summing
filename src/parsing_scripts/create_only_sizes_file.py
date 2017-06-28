#! /usr/bin/python

import sys

def main():
    if len(sys.argv) < 2:
        sys.exit("No input file was entered\n")
    input_file = open(sys.argv[1], 'r')
    output_file = open("traces_by_size_only", 'w')
    for line in input_file:
        split_line = line.split()
        if 0 == len(split_line):
            continue
        output_file.write(split_line[-1])
        output_file.write("\n")
    input_file.close()
    output_file.close()
    return 0


if __name__ == "__main__":
    main()

