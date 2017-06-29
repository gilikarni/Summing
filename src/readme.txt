
SUMMING OVER A SLIDING WINDOW:
------------------------------

CONTENTS OF THIS FILE
---------------------
 * Introduction
 * Requirements
 * Installation
 * Configuration
 
 INTRODUCTION
-------------

 This project implements 6 solutions for summing over a sliding window:

	---------------------------------------------
	| MISTAKE					|	WINDOW SIZE | 
	---------------------------------------------
	| No mistake				|	Exact		|
	---------------------------------------------
	| No mistake				| 	Slacky		|
	---------------------------------------------
	| Additive mistake			| 	Exact		|
	---------------------------------------------
	| Additive mistake			| 	Slacky		|
	---------------------------------------------
	| Multiplicative mistake	| 	Exact		|
	---------------------------------------------
	| Multiplicative mistake	| 	Slacky		|
	---------------------------------------------
	
 This projects implements those algorithms and ofer benchmarks to determine time 
 efficiency and the averge mistake size.
 This project is available only for UNIX operation systems.

 REQUIREMENTS
-------------

 In order to use this package you will need to have:
	1. g++ compiler.
	2. python 2.7 installed on your computer (only for benchmarks).
	3. python statistics package installed on your computer.
	For the last one use 'sudo pip install statistics'.

 INSTALLATION
------------- 

 Run make from the src directory, the executable will be created in obj directory.
 In order to run the code there needs to be a file with sizes only named 
 traces_by_size_only.
 There is a python script create_only_sizes_file.py which expect traces in the format:
 16:00:00.000001 99.158.44.6.42754 202
 And creates a file from the sizes, any trace which has the sizes at the end of
 the line will work.
 The output of the program is at output.txt.

 CONFIGURATION
--------------

 There are two ways of configuration:
 	1. There is file named conf.txt in the src/ directory. This file 
 	contains all the default configuration for running the program.
 	It is possible to edit that file and the default configuration will change - 
 	no need to compile!
 	Note: It is possible to change the order of the file but not the format.
 	2. It is possible to configure all the parameters using thre command line.
 	In order to see the possible parameters use the flag "--help".
 	The parameters are:
 	--mul                Calculate with a multiplicative mistake
	--add                Calculate with an additive mistake
	--mul_slack          Calculate with a multiplicative mistake and a slack window size
	--add_slack          Calculate with an additive mistake and a slack window size
	--exact              Calculate the exact sum
	--exact_slack        Calculate the exact sum on a slack window
	--calc_times         Calculate the average time for updates and query, can calculate only for only one algorithm at a time.
	--calc_times_update  Calculate the average time for updates, can calculate only for only one algorithm at a time.
	--print_query        Print the sum that was queried (works only if the input is not too large)
	--window             The size of the window to sum of
	--range              The range of the packet sizes
	--epsilon            The allowed mistake in the sum
	--tau                The allowed mistake in the window size
	--iterations         The allowed number of iterations
	--help               Print optional parameters
