
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

    /* The minimum between the number of elements
    that was alredy seen and "window" */
    uint64_t numberOfElementsSeen;

    /* The temporal sum of the last elements - y */
    uint64_t subSum;

    /* The size of block to sum of the subSum - T */
    uint64_t blockSize;

public:

    /* Constructors: */

    AdditiveMistake(
    		const uint64_t& _range,
			const uint16_t& _window,
			const uint64_t& epsilon);

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
    void update(
    		const uint64_t& packatSize);

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
    uint64_t query() const;
};

#endif
