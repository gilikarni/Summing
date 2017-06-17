
/* Includes: */

#include "additive_mistake_slack_window.h"
#include "../utils.h"
#include <cmath>
#include <deque>
#include <algorithm>

/* Namespace: */

/* Macros: */

/* Globals */

std::ofstream AdditiveSlackMistake_outputFile;

/* Constructors: */

AdditiveSlackMistake::AdditiveSlackMistake(
		const uint64_t& _window,
		const uint64_t& _range,
		const double& _tau,
		const double& _epsilon) :
		window(_window), range(_range), tau(_tau), epsilon(_epsilon),
		currentSum(0), blockSums(std::deque<uint16_t>((int)ceil(1/tau), 0)),
		sum(0),	diff(0), v1((int)ceil(log(1/epsilon)/log(2) + 1)),
		v2((int)ceil(log(tau/epsilon)/log(2)))
{
	AdditiveSlackMistake_outputFile.open(
			OUTPUT_FILE_NAME,
			std::ofstream::out | std::ofstream::app);
	if (!AdditiveSlackMistake_outputFile || !AdditiveSlackMistake_outputFile.good())
	{
		std::cout << "Could not open " << OUTPUT_FILE_NAME << " in "
				<< __FILE__ << std::endl;
		throw std::bad_alloc();
	}

	blockSize = (uint64_t)round((double(window)*tau));
	if (0 == blockSize)
	{
		printLogsToFile(AdditiveSlackMistake_outputFile,
				"ERROR: tau is too small!");
		throw std::bad_alloc();
	}
}

/* Destrucrors */

AdditiveSlackMistake::~AdditiveSlackMistake()
{
	AdditiveSlackMistake_outputFile.close();
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
	double x = roundV((double)packetSize / (double)range, v1);

	currentSum += x;
	diff++;

	if (blockSize == diff)
	{
		sum -= blockSums.front();
		blockSums.pop();
		double bi = roundV((double) currentSum / (double)blockSize, v2);
		sum += bi;
		blockSums.push(bi);
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
