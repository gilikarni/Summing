/* Includes: */
#include "exact_slack_window.h"
#include "../utils.h"
#include <cmath>

/* Namespace: */

/* Macros: */

/* Globals: */

std::ofstream ExactSlackSumming_outputFile;

/* Constructors: */

ExactSlackSumming::ExactSlackSumming(
    		const uint64_t& _range,
			const uint64_t& _window,
			const double& _tau) :
		range(_range), window(_window), sum(0), numberOfElementsSeen(0),
		tau(_tau), lastElements(0), diff(0)
{
	blockSize = (uint64_t)round((double(window)*tau));

	ExactSlackSumming_outputFile.open(
			OUTPUT_FILE_NAME,
			std::ofstream::out | std::ofstream::app);
	if (!ExactSlackSumming_outputFile || !ExactSlackSumming_outputFile.good())
	{
		std::cout << "Could not open " << OUTPUT_FILE_NAME << " in "
				<< __FILE__ << std::endl;
		throw std::bad_alloc();
	}
}

ExactSlackSumming::~ExactSlackSumming()
{
	ExactSlackSumming_outputFile.close();
}

/* Static functions: */

/* API: */

/*
 * Function name: ExactSlackSumming::update
 *
 * Description:
 *  Update the mean of the sliding window.
 *
 * Parameters:
 *  packatSize - The size of the new element
 *
 * Return values:
 *  None
*/
void ExactSlackSumming::update(
		const uint16_t& packetSize)
{
	numberOfElementsSeen++;

	lastElements += packetSize;
	diff++;

	if (blockSize == diff)
	{
		elements.push(lastElements);
		sum += lastElements;
		lastElements = 0;
		diff = 0;
		if (numberOfElementsSeen > window)
		{
			sum -= elements.back();
			elements.pop();
		}
	}
}

/*
 * Function name: ExactSlackSumming::query
 *
 * Description:
 *  Return the mean of the last "window" elements
 *
 * Parameters:
 *  windowSizeMistake - output. The difference between the size of the
 *  window that was summed and w.
 *
 * Return values:
 *  The mean of the last "window" + windowSizeMistake elements
*/
double ExactSlackSumming::query(uint64_t& windowSizeMistake) const
{
	double mean = 0;
	if (0 == numberOfElementsSeen){
		mean = 0;
		windowSizeMistake = 0;
	}
	else if (numberOfElementsSeen < window)
	{
		mean = (double)(sum + lastElements) / (double)(numberOfElementsSeen);
		windowSizeMistake = 0;
	}
	else
	{
		mean = (double)(sum + lastElements) / (double)(window + diff);
		windowSizeMistake = diff;
	}

	printLogsToFile(ExactSlackSumming_outputFile,
			"Query - Mean = " << mean << " Diff = " << diff);
	return mean;
}
