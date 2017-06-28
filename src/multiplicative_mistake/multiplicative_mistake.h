
#ifndef MULOMISTAKE_ACCURATESUMMING
#define MULOMISTAKE_ACCURATESUMMING

/*
 * File description:
 *
*/

/* Includes: */

#include <stdint.h>
#include <vector>
#include <bitset>
#include <cmath>
#include <unordered_map>
#include <list>

/* Namespace: */

using std::vector;
using std::pair;
using std::bitset;
using std::unordered_map;
using std::list;

/* Types: */

typedef vector< pair<uint64_t, uint64_t> > expHistogram;

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

    /* A vector of blocks containing the size of the bucket and the time stamp -
     * the first element in the pair is the size and the second is the time
     * stamp*/
    expHistogram EH;

    /* A histogram of the block sizes, in order to merge blocks effectively */
    std::unordered_map<uint64_t, uint64_t> bucketHistogram;

public:

    /* Constructors: */

    BasicCounting(
    		const uint64_t& _window,
			const double& epsilon);

    /* Destructors: */

    ~BasicCounting();

    /* API */

    void updateWith1();

    void updateEH();

    void updateTimeStamps();

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
