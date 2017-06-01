/*
 * File description:
 *
*/

#ifndef ADDOMISTAKE_SLACKSUMMING
#define ADDOMISTAKE_SLACKSUMMING

/*
 * File description:
 *
*/

/* Includes: */
#include <queue>
#include <cstdint>

using namespace std;

class AdditiveSlackMistake
{
	/* The desired window size */
	const uint64_t window;

	/* The allowed percentage of mistake in the window size */
	const double tau;

	/* The Sum of the current block */
	double currentSum;

	/* A queue of sums of the blocks that are currently in the mean */
	queue<uint16_t> blockSums;

	/* The current mean - the sum of the elements in blockSums*/
	uint16_t mean;

	/* The difference the actual window size and the desired window size -
	 * The number of elements summed to currentSum
	 */
	uint16_t offset;

    /* The minimum between the number of elements
    that was already seen and "window" */
    uint64_t numberOfElementsSeen;
public:

	/* Constructors: */

	AdditiveSlackMistake(const uint64_t& w, const double& t);

	/* API: */

    /*
     * Function name: AdditiveSlackMistake::update
     *
     * Description:
     *  Update the mean of the sliding window.
     *
     * Parameters:
     *  packatSize - The size of the new element
     *
     * Return values:
     *  None
    */
    void update(
    		const uint16_t& packetSize);

    /*
     * Function name: AdditiveSlackMistake::query
     *
     * Description:
     *  Return the mean of the last "window" elements
     *
     * Parameters:
     *  windowSizeMistake - output. The difference between the size of the
     *  window that was summed and w.
     *
     * Return values:
     *  The mean of the last "window" + windowSizeMistake elements
    */
    uint64_t query(uint64_t& windowSizeMistake) const;
};

#endif
