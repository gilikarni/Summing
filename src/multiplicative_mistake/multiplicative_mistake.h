
#ifndef MULOMISTAKE_ACCURATESUMMING
#define MULOMISTAKE_ACCURATESUMMING

/*
 * File description:
 *
*/

/* Includes: */

#include <stdint.h>
#include <list>
#include <bitset>
#include <cmath>

/* Namespace: */

using std::list;
using std::pair;
using std::bitset;

/* Types: */

typedef list< pair<uint64_t, uint64_t> > expHistogram;

class BasicCounting
{
    /* The size of the window to sum */
    const uint64_t window;

    /* A wraparound counter to calculate the time stamp */
    uint64_t lastArrivalTime;

    /* A wraparound counter to calculate the expiry time */
    uint64_t expiryTime;

    /* The total sum of the window */
    uint64_t totalSum;

    /* The sum of the last block */
    uint64_t lastSum;

    /* k = ceil(1/epsilon) */
    const uint64_t k;

    /* A list of blocks containing the size of the bucket and the time stamp -
     * the first element in the pair is the size and the second is the time
     * stamp*/
    expHistogram EH;

public:

    /* Constructors: */

    BasicCounting(
    		const uint64_t& _window,
			const double& epsilon);

    /* Destructors: */

    ~BasicCounting();

    /* API */

    void update(const bitset<1>& arrivingItem);

    double query() const;
};

class MultiplicativeMistake
{
	/* The BasicCounting object to calculate the sum */
	BasicCounting basic;

    /* The range of the sizes */
    const uint64_t range;

public:

/* Constructor: */
	MultiplicativeMistake(
			const uint64_t& _range,
			const uint64_t& _window,
			const double& _epsilon);

/* Destructor: */

	~MultiplicativeMistake();

/* API: */

    void update(const uint16_t& packetSize);

    double query() const;
};

#endif
