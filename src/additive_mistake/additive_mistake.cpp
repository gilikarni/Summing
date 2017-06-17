/* Includes: */
#include "additive_mistake.h"
#include "../utils.h"
#include <cmath>

/* Namespace: */

/* Macros: */

/* Constructors: */

AdditiveMistake::AdditiveMistake(
	const uint64_t& _range,
	const uint16_t& _window,
	const uint64_t& _epsilon) :
	range(_range), window(_window), sum(0),
	elements(), subSum(0), v((uint64_t)ceil(log((1/_epsilon)*log(_window)))),
	blockSize((uint64_t)floor(window*(2*epsilon - (1/pow(2, v))))),
	epsilon(_epsilon), bitSetIndex(0), blockIndex(0)
{
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
	double xx = roundV((double)packatSize / range, v); /* x' */
	blockIndex = (blockIndex + 1) % blockSize;
	subSum += xx;

	if (0 == bitSetIndex)
	{
		sum -= elements[bitSetIndex];
		elements[bitSetIndex] = floor(subSum / blockSize);
		subSum -= blockSize*elements[bitSetIndex];
		sum += elements[bitSetIndex];
		bitSetIndex = (bitSetIndex + 1) % elements.size();
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
	return range*((double)blockSize*sum + subSum - (double)blockSize/2 -
			blockIndex*subSum + (1/pow(2, v+1)));
}

















