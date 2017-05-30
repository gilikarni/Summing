
/*
 * File description:
 *  This file describes the API of an algorithm of summing on a sliding window. The
 *  window size is the W, and the elements are in range [0,R].
 *  This algorithm sums every T elements divided by R at a precision of v digits in
 *  a variable y. After the arriving of T elements, after summing T elements, y is added
 *  to the total mean and compressed to a single bit, if entered to queue of k elements. The last element
 *  in the queue is popped out and subtracted from the mean. - TODO - fix, this is not correct
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
    uint64_t mean;

    /* The last "window" summed T elemants */
    bitset<32> elements;

    /* The minimum between the number of elements
    that was alredy seen and "window" */
    uint64_t numberOfElementsSeen;

    /* The temporal mean of the last elements - y */
    uint64_t subMean;

    /* The number of elements in every sub mean - T */
    const uint64_t numberOfElementsInSubMean;

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
     *  Update the mean of the sliding window, i.e, Adding the new
     *  element to the sub sum, If needed add the sub sum to the queue
     *  and to the mean and pop out the last element in the queue and
     *  Subtract from the mean.
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
     *  Return the mean of the last "window" elements
     *  (maybe with a mistake)
     *
     * Parameters:
     *  None
     *
     * Return values:
     *  The mean of the last "window" elements
    */
    uint64_t query() const;
};

#endif
