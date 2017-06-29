
/* Includes: */

#include "additive_mistake_slack_window.h"
#include "../utils.h"
#include <cmath>
#include <deque>
#include <algorithm>

/* Namespace: */

/* Macros: */

/* Globals */

/* Constructors: */

AdditiveSlackMistake::AdditiveSlackMistake(
		const uint64_t& _window,
		const uint64_t& _range,
		const double& _tau,
		const double& _epsilon) :
		window(_window), range(_range), tau(_tau), epsilon(_epsilon),
		currentSum(0), blockSums((int)ceil(1/_tau), 0),
		sum(0),	diff(0), v1((int)ceil(log(1/_epsilon)/log(2) + 1)),
		v2((int)ceil(log(_tau/_epsilon)/log(2)))
{
	blockSize = (uint64_t)round((double(window)*tau));
	if (0 == blockSize)
	{
		printLogsToFile(std::cout,
				"ERROR: tau is too small!");
		throw std::bad_alloc();
	}
}

/* Destrucrors */

AdditiveSlackMistake::~AdditiveSlackMistake()
{
}

/* Static functions: */

/* API: */

/*
 * Function name: AdditiveSlackMistake::update
 *
 * Description:
 *  Update the sum of the sliding window.
 *
 * Parameters:
 *  packatSize - The size of the new element
 *
 * Return values:
 *  None
*/
void AdditiveSlackMistake::update(const uint16_t& packetSize)
{
	static double powV1 = pow(2, v1);
	static double powV2 = pow(2, v2);
	double x = roundV((double)packetSize / (double)range, powV1);

	currentSum += x;
	diff++;

	if (blockSize == diff)
	{
		sum -= blockSums.back();
		blockSums.pop_back();
		double bi = roundV((double) currentSum / (double)blockSize, powV2);
		sum += bi;
		blockSums.insert(blockSums.begin(), bi);
		currentSum -= blockSize*bi;
		diff = 0;
	}
}

/*
 * Function name: AdditiveSlackMistake::query
 *
 * Description:
 *  Return the sum of the last "window" elements
 *
 * Parameters:
 *  windowSizeMistake - output. The difference between the size of the
 *  window that was summed and w.
 *
 * Return values:
 *  The sum of the last "window" + windowSizeMistake elements
*/
double AdditiveSlackMistake::query(uint64_t& windowSizeMistake) const
{
	double resultSum = (double)range*((double)blockSize*(double)sum + (double)currentSum);
	windowSizeMistake = diff;

	return resultSum;
}
