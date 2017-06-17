/*
 * File description:
 *
*/

#ifndef ADDOMISTAKE_SLACKSUMMING
#define ADDOMISTAKE_SLACKSUMMING

/*
 * File description:
 *  TODO
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

    /* The range of the sizes */
    const uint64_t range;

	/* The allowed percentage of mistake in the window size */
	const double tau;

	/* The allowed mistake in the sum */
	const double epsilon;

	/* The Sum of the current block */
	double currentSum;

	/* A queue of sums of the blocks that are currently in the sum */
	queue<uint16_t> blockSums;

	/* The current sum - the sum of the elements in blockSums*/
	uint16_t sum;

	/* The difference the actual window size and the desired window size -
	 * The number of elements summed to currentSum
	 */
	uint16_t diff;

    /* An internal use variables for calculating the sum */
    uint64_t v1, v2;

    /* The size of the summing blocks */
    uint64_t blockSize;

public:

	/* Constructors: */

	AdditiveSlackMistake(
			const uint64_t& _window,
			const uint64_t& _range,
			const double& _tau,
			const double& epsilon);

	/* Destrucrors */

	~AdditiveSlackMistake();

	/* API: */

    void update(const uint16_t& packetSize);

    double query(uint64_t& windowSizeMistake) const;
};

#endif
