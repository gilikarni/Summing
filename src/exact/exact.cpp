/* Includes: */
#include "exact.h"
#include "../utils.h"

/* Namespace: */

/* Macros: */

/* Globals: */

std::ofstream ExactSumming_outputFile;

/* Constructors: */

ExactSumming::ExactSumming(
		const uint64_t& _range,
		const uint16_t& _window) :
		range(_range), window(_window), mean(0), numberOfElementsSeen(0)
{
	ExactSumming_outputFile.open(
			OUTPUT_FILE_NAME,
			std::ofstream::out | std::ofstream::app);
	if (!ExactSumming_outputFile || !ExactSumming_outputFile.good())
	{
		std::cout << "Could not open " << OUTPUT_FILE_NAME << " in "
				<< __FILE__ << std::endl;
		throw std::bad_alloc();
	}
}

ExactSumming::~ExactSumming()
{
	ExactSumming_outputFile.close();
}

/* Static functions: */

/* API: */

/*
 * Function name: ExactSumming::update
 *
 * Description:
 *  Update the mean of the sliding window, i.e, Adding the new
 *  element to the sum and omit the oldest element.
 *
 * Parameters:
 *  packatSize - The size of the new element
 *
 * Return values:
 *  None
*/
void ExactSumming::update(const uint16_t& packatSize)
{
	double newPacket = (double)packatSize/(double)window;
	elements.push(newPacket);

	if (numberOfElementsSeen < window)
	{
		mean *= numberOfElementsSeen;
		mean += packatSize;
		numberOfElementsSeen++;
		mean /= numberOfElementsSeen;
	}
	else
	{
		mean -= elements.front();
		elements.pop();
		mean += newPacket;
	}
}

/*
 * Function name: ExactSumming::query
 *
 * Description:
 *  Return the mean of the last "window" elements
 *
 * Parameters:
 *  None
 *
 * Return values:
 *  The mean of the last "window" elements
*/
double ExactSumming::query() const
{
	printLogsToFile(ExactSumming_outputFile, "Query - Mean = " << mean);
	return mean;
}
