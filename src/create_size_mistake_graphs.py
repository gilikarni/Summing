#! /usr/bin/python

from subprocess import call, check_call
import sys
import os
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import *
from pylab import *

NUMBER_OF_ITERATIONS = 100
mistake_suffix = "MistakeOutput.txt"
size_suffix = "SizeOutput.txt"
fig_suffix = "_graph.png"

def main():
    
    str1=os.getcwd()
    str2=str1.split('/')
    n=len(str2)
    if str2[n-1] != "src":
        sys.exit("Should run the script from src directory")
    
    # Make sure there are no left overs from previous runs
    check_call(["make", "clean", "all"])
    
    epsilon = np.linspace(1.0 / NUMBER_OF_ITERATIONS, 1.0, NUMBER_OF_ITERATIONS)
    
    for e in epsilon:
        check_call(["../obj/main_bin", "--calc_size", "--epsilon", str(e), "--iterations", "33674081"])
        
    algo_list = ["exact", "mul", "add", "exact_slack", "mul_slack", "add_slack"]
    
    for algo in algo_list:
        size_file = open(algo + size_suffix, 'r')
        mistake_file = open(algo + mistake_suffix, 'r')
        sizes = [float(line) for line in size_file]
        mistakes = [float(line) for line in mistake_file]
        
        plt.figure()
        
        plt.subplot(2, 1, 1)
        plt.plot(epsilon, np.array(mistakes), linestyle='--', color='r')
        plt.title(algo)
        plt.ylabel("mistake")
        
        plt.subplot(2, 1, 2)
        plt.plot(epsilon, np.array(sizes), linestyle=':',color='b')
        plt.ylabel("size")
        plt.xlabel('epsilon')
        
        savefig(algo + fig_suffix)
    return 0

if __name__ == "__main__":
    main()