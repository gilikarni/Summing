/* Includes: */
#include "multiplicative_mistake_slack_window.h"
#include <cmath>
#include "../utils.h"

/* Namespace: */

/* Macros: */

#define minus_inf -1

/* Globals */

std::ofstream MultiplicativeMistakeSlackSumming_outputFile;

/* Constructors: */

MultiplicativeMistakeSlackSumming::MultiplicativeMistakeSlackSumming(
    		const uint64_t& _range,
			const uint64_t& _window,
			const double& _tau,
			const double& _epsilon) :
			range(_range), window(_window), sum(0), tau(_tau),
			epsilon(_epsilon), lastElements(0),
			elements(std::deque<double>((int)ceil(1/_tau), 0)), diff(0)
{
	MultiplicativeMistakeSlackSumming_outputFile.open(
			OUTPUT_FILE_NAME,
			std::ofstream::out | std::ofstream::app);
	if (!MultiplicativeMistakeSlackSumming_outputFile ||
			!MultiplicativeMistakeSlackSumming_outputFile.good())
	{
		std::cout << "Could not open " << OUTPUT_FILE_NAME << " in "
				<< __FILE__ << std::endl;
		throw std::bad_alloc();
	}

	blockSize = (uint64_t)round((double(window)*tau));
	if (0 == blockSize)
	{
		printLogsToFile(MultiplicativeMistakeSlackSumming_outputFile,
				"ERROR: tau is too small!");
		throw std::bad_alloc();
	}
}

/* Destructors */

MultiplicativeMistakeSlackSumming::~MultiplicativeMistakeSlackSumming()
{
	MultiplicativeMistakeSlackSumming_outputFile.close();
}

/* Static functions: */

/*
 * Function name: calcRo
 *
 * Description:
 *  Calculate ro according to the essay.
 *
 * Parameters:
 *  epsilon - The allowed mistake in the sum
 *  y - the sum of the elements in the last block.
 *
 * Return values:
 *  ro
*/
static double calcRo(const double& epsilon, const double& y)
{
	if (0 == y)
	{
		return minus_inf;
	}

	double ro = log(y) / log (1 + epsilon/2);

	return floor(ro);
}

/*
 * Function name: roundDown
 *
 * Description:
 *  Calculate round down according to the essay.
 *
 * Parameters:
 *  epsilon - The allowed mistake in the sum
 *  x - the number to round
 *
 * Return values:
 *  the rounded result
*/
static double roundDown(const double& epsilon, const double& ro)
{
	double x = 0;
	if (minus_inf != ro)
	{
		x = pow(1.0 + epsilon/2.0, ro);
	}

	double k = ceil(4/epsilon);

	return floor(x * k)/k;
}

/* API: */

/*
 * Function name: MultiplicativeMistakeSlackSumming::update
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
void MultiplicativeMistakeSlackSumming::update(const uint16_t& packetSize)
{
	lastElements += packetSize;
	diff++;

	if (diff == blockSize)
	{
		double ro = calcRo(epsilon, (double)lastElements);
		sum += roundDown(epsilon, ro) - roundDown(epsilon, elements.front());
		elements.pop();
		elements.push(ro);
		lastElements = 0;
		diff = 0;
	}
}

/*
 * Function name: MultiplicativeMistakeSlackSumming::query
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
double MultiplicativeMistakeSlackSumming::query(uint64_t& windowSizeMistake) const
{
	windowSizeMistake = diff;

	return sum + lastElements;
}

