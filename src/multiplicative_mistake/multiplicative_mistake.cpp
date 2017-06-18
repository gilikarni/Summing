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
 * Function name: BasicCounting::update
 *
 * Description:
 *  Update the sum of the sliding window.
 *
 * Parameters:
 *  arrivingItem - The size of the new bit
 *
 * Return values:
 *  None
*/
void BasicCounting::update(const bitset<1>& arrivingItem)
{
	expiryTime = (expiryTime + 1) % window;
	lastArrivalTime = (lastArrivalTime + 1) % window;

	if (!EH.empty() && EH.back().second > expiryTime)
	{
		totalSum -= EH.back().first;
		EH.remove(EH.back());
		if (EH.empty())
		{
			lastSum = 0;
		}
		else
		{
			lastSum = EH.back().first;
		}
	}

	if (0 == arrivingItem[0])
	{
		return;
	}

	/* The element is 1 */
	EH.push_front(std::make_pair(1, lastArrivalTime));

	bool reachedEnd = false;

	/* Update list */

	while (!reachedEnd)
	{
		uint64_t counter = 0, sizeTocountOf = 0, indexToStartCounting = 0;
		for (auto& i : EH)
		{
			if (sizeTocountOf < i.first)
			{
				if (counter > (k + 1)/2)
				{
					break;
				}
				else
				{
					indexToStartCounting += counter;
				}
			}
		}

		if (counter >= (k + 1)/2)
		{
			reachedEnd = true;
			break;
		}

		expHistogram::iterator iter1 = EH.begin();
		expHistogram::iterator iter2 = EH.begin();

		std::advance(iter1, indexToStartCounting);
		std::advance(iter2, indexToStartCounting + 1);

		(*iter1).first += (*iter2).first;

		EH.remove(*iter2);
	}
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
					basic(_range * _window, _epsilon), range(_range)
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
	for (uint16_t i = 0; i < packetSize; i++)
	{
		basic.update(bitset<1>("1"));
	}

	if (range < packetSize)
	{
		std::cerr << "ERROR!! packetSize is bigger then range" << std::endl;
		throw std::out_of_range("ERROR!! packetSize is bigger then range");
	}

	for (uint16_t i = 0; i < (range - packetSize); i++)
	{
		basic.update(bitset<1>("0"));
	}
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


