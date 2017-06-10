/* Includes: */
#include "exact.h"
#include "../utils.h"

/* Namespace: */

/* Macros: */

/* Globals: */
std::ofstream outputFile;

/* Constructors: */

ExactSumming::ExactSumming(
		const uint64_t& _range,
		const uint16_t& _window) :
		range(_range), window(_window), mean(0), numberOfElementsSeen(0)
{
	outputFile.open(OUTPUT_FILE_NAME);
	if (!outputFile.is_open())
	{
		std::cout << "Can not open" << OUTPUT_FILE_NAME << std::endl;
		throw std::bad_alloc();
	}
}

ExactSumming::~ExactSumming()
{
	outputFile.close();
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
	printLogs("The mean is " << mean);
	return mean;
}
