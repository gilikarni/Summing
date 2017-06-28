/* Includes: */
#include "multiplicative_mistake.h"
#include "../utils.h"
#include <stdexcept>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <thread>

/* Macros: */

/****************************** BasicCounting: ********************************/

/* Constructors: */

BasicCounting::BasicCounting(
		const uint64_t& _window,
		const double& epsilon) :
				window(_window), lastArrivalTime(0), expiryTime(_window),
				totalSum(0), lastSum(0), k((uint64_t)ceil(1/epsilon))
{
	bucketHistogram[1] = 0;
}

BasicCounting::~BasicCounting()
{
}

/* Static functions: */

/* API: */

/*
 * Function name: BasicCounting::updateEH
 *
 * Description:
 *  Update the EH - merge buckets and remove all the expired elements.
 *
 * Parameters:
 *  None
 *
 * Return values:
 *  None
*/
void BasicCounting::updateEH()
{
	/* Remove expired elements */
	while (!EH.empty() && EH.front().second == expiryTime)
	{
		uint64_t size = EH.front().first;
		totalSum -= size;
		bucketHistogram[size]--;
		if (size > 1 && 0 == bucketHistogram[size])
		{
			bucketHistogram.erase(size);
		}
		EH.erase(EH.begin());
	}

	/* Merge buckets */

	uint64_t treshHold = ((k + 1)/2) + 2;

	uint16_t numberOfDifferentValues = bucketHistogram.size(), lastIndex = EH.size();
	for (uint16_t i = 0, indexInMap = 1; i < numberOfDifferentValues; i++, indexInMap *= 2)
	{
		lastIndex -= bucketHistogram[indexInMap];
		while(bucketHistogram[indexInMap] >= treshHold)
		{
			bucketHistogram[indexInMap] -= 2;
			if (i == numberOfDifferentValues - 1)
			{
				/* Add a bigger element then already exist */
				numberOfDifferentValues++;
				bucketHistogram[indexInMap*2] = 0;
			}
			bucketHistogram[indexInMap*2]++;
			EH[lastIndex + 1].first += EH[lastIndex].first;
			EH.erase(EH.begin() + lastIndex);
			lastIndex++;
		}
	}

	if (EH.empty())
	{
		lastSum = 0;
	}
	else
	{
		lastSum = EH.front().first;
	}
}

/*
 * Function name: BasicCounting::update
 *
 * Description:
 *  Update the sum of the sliding window.
 *
 * Parameters:
 *  arrivingItem - The size of the new bit
 *  bPromoteIndexes - should the indexes be promoted. (only at the first 1 in a
 *  number)
 *
 * Return values:
 *  None
*/
void BasicCounting::updateWith1()
{
	/* The element is 1 */
	if (EH.empty())
	{
		lastSum = 1;
	}

	EH.push_back(std::make_pair(1, lastArrivalTime));
	bucketHistogram[1]++;
	totalSum++;
}

/*
 * Function name: BasicCounting::update
 *
 * Description:
 *  Update the sum of the sliding window.
 *
 * Parameters:
 *  arrivingItem - The size of the new bit
 *  bPromoteIndexes - should the indexes be promoted. (only at the first 1 in a
 *  number)
 *
 * Return values:
 *  None
*/
void BasicCounting::updateTimeStamps()
{
	expiryTime = (expiryTime + 1) % (2*window);
	lastArrivalTime = (lastArrivalTime + 1) % (2*window);
	return;
}

/*
 * Function name: BasicCounting::query
 *
 * Description:
 *  Return the sum of the window
 *
 * Parameters:
 *  None
 *
 * Return values:
 *  The sum
*/
double BasicCounting::query() const
{
	return totalSum - (lastSum / 2);
}

/*****************************End of BasicCounting*****************************/

/*****************************MultiplicativeMistake****************************/

/* Constructors: */

MultiplicativeMistake::MultiplicativeMistake(
			const uint64_t& _range,
			const uint64_t& _window,
			const double& _epsilon) :
					basic(_window, _epsilon), range(_range)
{
}

/* Destructor: */

MultiplicativeMistake::~MultiplicativeMistake()
{
}

/* API: */

/*
 * Function name: BasicCounting::update
 *
 * Description:
 *  Update the sum of the sliding window. Add to the BasicCounting object
 *  packetSize ones and R - packetSize zeros
 *
 * Parameters:
 *  arrivingItem - The size of the new bit
 *
 * Return values:
 *  None
*/
void MultiplicativeMistake::update(const uint16_t& packetSize)
{
	if (range < packetSize)
	{
		std::cerr << "ERROR!! packetSize is bigger then range" << std::endl;
		throw std::out_of_range("ERROR!! packetSize is bigger then range");
	}

	basic.updateTimeStamps();

	for (uint16_t i = 0; i < packetSize; i++)
	{
		basic.updateWith1();
	}

	basic.updateEH();
}

/*
 * Function name: BasicCounting::query
 *
 * Description:
 *  Return the sum of the window
 *
 * Parameters:
 *  None
 *
 * Return values:
 *  The sum
*/
double MultiplicativeMistake::query() const
{
	return basic.query();
}

/**************************End of MultiplicativeMistake************************/


