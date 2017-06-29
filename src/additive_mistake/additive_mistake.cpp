/* Includes: */
#include "additive_mistake.h"
#include "../utils.h"
#include <cmath>
#include <deque>
#include <stdexcept>

/* Namespace: */

/* Macros: */

/* Constructors: */

AdditiveMistake::AdditiveMistake(
	const uint64_t& _range,
	const uint16_t& _window,
	const double& _epsilon) :
	range(_range), window(_window), sum(0),
	elements(), lastElements(_window, 0),
	subSum(0), v((uint64_t)ceil(log((1./_epsilon)*(log(_window)/log(2)))/ (log(2)))),
	epsilon(_epsilon), bitSetIndex(0), blockIndex(0)
{
	bLargeEpsilon = (1./epsilon) <= (double)window*(2. - (1./log(window)));
	if (bLargeEpsilon)
	{
		blockSize = floor(window*(2*epsilon - (1. / pow(2., v))));
		elements = vector<bool>(ceil(window / blockSize), false);
	}
	else
	{
		blockSize = window*(2*epsilon - (1. / pow(2., v)));
	}

	if (blockSize <= 0)
	{
		std::cout << "Block size is " << blockSize << std::endl;
		throw std::out_of_range("Non positive block size");
	}
}

/* Static functions: */

/* API: */

/*
 * Function name: AdditiveMistake::update
 *
 * Description:
 *  Update the sum of the sliding window, i.e, Adding the new
 *  element to the sub sum, If needed add the sub sum to the queue
 *  and to the sum and pop out the last element in the queue and
 *  Subtract from the sum.
 *
 * Parameters:
 *  packatSize - The size of the new element
 *
 * Return values:
 *  None
*/
void AdditiveMistake::update(const uint64_t& packatSize)
{
	static double powV = pow(2,v);
	double xx = roundV((double)packatSize / range, powV); /* x' */

	if (bLargeEpsilon)
	{
		blockIndex++;
		subSum += xx;

		if (blockSize == blockIndex)
		{
			sum -= (elements[bitSetIndex]) ? 1: 0;
			elements[bitSetIndex] = (1 == floor(subSum / blockSize)) ? true : false;
			subSum -= blockSize*((elements[bitSetIndex]) ? 1: 0);
			sum += (elements[bitSetIndex]) ? 1: 0;
			bitSetIndex = (bitSetIndex + 1) % elements.size();
			blockIndex = 0;
		}
	}
	else
	{
		/* Small epsilon */
		sum -= lastElements.back();
		lastElements.pop_back();
		lastElements.insert(lastElements.begin(), floor((double)(subSum + xx) / blockSize));
		subSum += xx - lastElements.front()*blockSize;
		sum += lastElements.front();
	}
}

/*
 * Function name: AdditiveMistake::query
 *
 * Description:
 *  Return the sum of the last "window" elements
 *  (maybe with a mistake)
 *
 * Parameters:
 *  None
 *
 * Return values:
 *  The sum of the last "window" elements
*/
double AdditiveMistake::query() const
{
	/* Calculate only once */
	static double constant = 1./pow(2, v+1) - (double)blockSize/2;
	return range*((double)blockSize*sum + subSum -
			blockIndex*subSum + constant);
}

















