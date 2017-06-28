#! /usr/bin/python

from subprocess import call, check_call
import sys
import os
import statistics

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
    calc_list = ["calc_times", "calc_times_update"]
    file = open("results", 'w');

    # Run over algorithms and create statistics
    for algo in algo_list:
        header = "For algorithm %s:\n" %(algo)
        file.write(header)
        for c in calc_list:
            call(["rm", sys.argv[1]])
            for i in xrange(int(sys.argv[2])):
                check_call(["../obj/main_bin", "--" + algo, "--" + c, "--iterations", "1000000"])
            output_file = open(sys.argv[1], 'r+')
    	    times = []
            for line in output_file:
                split_line = line.split()
                times.append(float(split_line[-1]))
            if (c == 'calc_times'):
                op = 'update and query'
            else:
                op = 'update'
            output = "%s: average time = %f (ms)" %(op, statistics.mean(times))
         #   if sys.argv[2] > 1:
        #        output = output + ", standard deviation = %f (ms)\n" %(statistics.stdev(times))
            file.write(output)
            output_file.close()
    
    return 0


if __name__ == "__main__":
    main()
