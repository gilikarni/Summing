#! /usr/bin/python

from subprocess import call, check_call
import sys
import os
import statistics
from operator import is_

def main():
    
    # Input checks
    if len(sys.argv) < 2:
        sys.exit("No output file was entered\n")
    if len(sys.argv) < 3:
        sys.exit("Number of iterations not defined\n")
    str1=os.getcwd()
    str2=str1.split('/')
    n=len(str2)
    if str2[n-1] != "src":
        sys.exit("Should run the script from src directory")
    
    # Generate tests
    algo_list = ["exact", "mul", "add", "exact_slack", "mul_slack", "add_slack"]
    file = open("results", 'w');

    # Run over algorithms and create statistics
    for algo in algo_list:
        header = "For algorithm %s:\n" %(algo)
        file.write(header)
        call(["rm", sys.argv[1]])
        for i in xrange(int(sys.argv[2])):
            check_call(["../obj/main_bin", "--" + algo, "--iterations", "33674081"])
        output_file = open(sys.argv[1], 'r+')
        mistake = []
        window = []
        count = 0
        is_slack = ((algo.split('_'))[-1] == "slack") 
        for line in output_file:
            count+=1
            split_line = line.split()
            if 0 == len(split_line):
                continue
            if (count % 2 == 0) or (not is_slack):
                mistake.append(float(split_line[-1]))
            else:
                window.append(float(split_line[-1]))
        output = "sum: average mistake = %f (ms), standard deviation = %f (ms)\n" %(statistics.mean(mistake), statistics.stdev(mistake))
        file.write(output)
        if is_slack:
            output = "window size: average mistake = %f (ms), standard deviation = %f (ms)\n" %(statistics.mean(window), statistics.stdev(window))
            file.write(output)  
        output_file.close()
    
    return 0


if __name__ == "__main__":
    main()

