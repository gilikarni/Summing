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
		range(_range), window(_window), sum(0),
		elements(window, 0)
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
 *  Update the sum of the sliding window, i.e, Adding the new
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
	elements.insert(elements.begin(), packatSize);
	sum += packatSize;
	sum -= elements.back();
	elements.pop_back();
}

/*
 * Function name: ExactSumming::query
 *
 * Description:
 *  Return the sum of the last "window" elements
 *
 * Parameters:
 *  None
 *
 * Return values:
 *  The sum of the last "window" elements
*/
double ExactSumming::query() const
{
	return sum;
}

/*
 * Function name: ExactSumming::getSize
 *
 * Description:
 *  TODO
 *
 * Parameters:
 *  None
 *
 * Return values:
 *  TODO
*/
uint64_t ExactSumming::getSize() const
{
	return sizeof(range) + sizeof(window) + sizeof(sum) +
			sizeof(elements) + (elements.size() * sizeof(uint16_t));
}
