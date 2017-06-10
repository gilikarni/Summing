/*
 * exact_main.cpp
 *
 *  Created on: Jun 10, 2017
 *      Author: compm
 */
#include "exact.h"
#include <random>
#include "../utils.h"
#include <iostream>
#include <string>

/* Namespace: */

/* Macros: */

#define NUM_OF_ITER 50

/* Globals: */

int main()
{
	uint64_t range = 1000;
	uint16_t window = 10;
	double mean = 0;
	ExactSumming exactSumming(range, window);
	for (int p = 0; p < NUM_OF_ITER; p++)
	{
		int packetSize = rand() % range;

		printLogs(
				"Update with packet size: " << packetSize);
		exactSumming.update(packetSize);
		mean = exactSumming.query();
		printLogs(
				"Mean is: " << mean);
	}
	return 0;
}



