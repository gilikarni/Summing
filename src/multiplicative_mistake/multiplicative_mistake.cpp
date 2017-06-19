/* Includes: */
#include "multiplicative_mistake.h"
#include "../utils.h"
#include <stdexcept>

/* Macros: */

/****************************** BasicCounting: ********************************/

/* Constructors: */

BasicCounting::BasicCounting(
		const uint64_t& _window,
		const double& epsilon) :
				window(_window), lastArrivalTime(0), expiryTime(_window),
				totalSum(0), lastSum(0), k((uint64_t)ceil(1/epsilon))
{
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
	while (!EH.empty() && EH.front().second > expiryTime)
	{
		totalSum -= EH.front().first;
		EH.erase(EH.begin());
		if (EH.empty())
		{
			lastSum = 0;
		}
		else
		{
			lastSum = EH.front().first;
		}
	}

	/* Merge buckets */

	bool reachedEnd = false;

	while (!reachedEnd)
	{
		uint64_t counter = 0, sizeTocountOf = 0, index = EH.size() - 1;
		expHistogram::reverse_iterator i = EH.rbegin();
		for (; EH.rend() != i; i++)
		{
			if (sizeTocountOf < i->first)
			{
				if (counter > (k + 1)/2)
				{
					break;
				}
				index--;
				sizeTocountOf = i->first;
				counter = 0;
			}
			counter++;
		}

		if (counter <= (k + 1)/2)
		{
			reachedEnd = true;
			break;
		}

		EH[index - 1].first += EH[index].first;
		EH.erase(EH.begin() + index);
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
void BasicCounting::update(bool bPromoteIndexes)
{
	if (bPromoteIndexes)
	{
		expiryTime = (expiryTime + 1) % window;
		lastArrivalTime = (lastArrivalTime + 1) % window;
	}

	/* The element is 1 */
	EH.push_back(std::make_pair(1, lastArrivalTime));
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
	bool bFirst = true;

	if (range < packetSize)
	{
		std::cerr << "ERROR!! packetSize is bigger then range" << std::endl;
		throw std::out_of_range("ERROR!! packetSize is bigger then range");
	}

	for (uint16_t i = 0; i < packetSize; i++)
	{
		basic.update(bFirst);
		bFirst = false;
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


