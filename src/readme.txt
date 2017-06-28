
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