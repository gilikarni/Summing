
/*
 * File description:
 *  This file describes the API of an algorithm of summing on a sliding window. The
 *  window size is the W, and the elements are in range [0,R].
 *  When a new element arrive we divide it by R and then add it to a sum - y.
 *  After adding T elements to the sum, check if it is bigger then T, if so turn on the
 *  bit b. assign y <- y - b*T, B <- B - b.
*/

#ifndef ADDOMISTAKE_ACCURATESUMMING
#define ADDOMISTAKE_ACCURATESUMMING

/* Includes: */
#include <bitset>

using std::bitset;

class AdditiveMistake
{
    /* The range of the sizes - R */
    const uint64_t range;

    /* The size of the window to sum -W */
    const uint64_t window;

    /* The average of the window */
    uint64_t sum;

    /* The last "window" summed T elemants */
    bitset<32> elements;

    /* The temporal sum of the last elements - y */
    double subSum;

    /* An internal use variable for calculating the sum */
    uint64_t v;

    /* The size of block to sum of the subSum - T */
    uint64_t blockSize;

	/* The allowed mistake in the sum */
	const double epsilon;

    /* The current index in the bitset - i */
    uint64_t bitSetIndex;

    /* The current index in the block - m */
    uint64_t blockIndex;

public:

    /* Constructors: */

    AdditiveMistake(
    		const uint64_t& _range,
			const uint16_t& _window,
			const uint64_t& _epsilon);

    /* API: */

    void update(const uint64_t& packatSize);

    double query() const;
};

#endif
