
/*
 * File description:
 *  Each time a new packet arrives we add it's size to a sum y.
 *  Every c = tau * w (w is the size of the window, tau is the percentage of
 *  the change in the window size), we add y to a queue. then subtract the oldest
 *  element from the mean and y to the mean.
 *  If we need to answer a query, we return the sum of the mean and y, and c, how
 *  many elements were added to y.
*/

#ifndef NOMISTAKE_SLACKSUMMING
#define NOMISTAKE_SLACKSUMMING

/* Includes: */
#include<queue>
#include <cstdint>

using std::queue;

class ExactSlackSumming
{
    /* The range of the sizes */
    const uint64_t range;

    /* The size of the window to sum */
    const uint64_t window;

    /* The average of the window */
    uint64_t mean;

    /* The minimum between the number of elements
    that was alredy seen and "window" */
    uint64_t numberOfElementsSeen;

    /* The percentege of the window size which is 
    aloud to add*/
    const double tau;

    /* The sum of the last elements */
    uint64_t lastElements;

    /* 1/tau sums of window*tau elements from the elements delivered */
    queue<uint64_t> elements;

    /* The number of elements that was summed at the last iteration */
    uint64_t diff;

public:

    /* Contructors: */

    ExactSlackSumming(
    		const uint64_t& r,
			const uint64_t& w,
			const double& t) :
    	range(r), window(w), tau(t) {}

    /* API: */

    /*
     * Function name: ExactSlackSumming::update
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
     * Function name: ExactSlackSumming::query
     *
     * Description:
     *  Return the mean of the last "window" elements
     *
     * Parameters:
     *  windowSizeMistake - output. The difference between the size of the
     *  window that was summed and w.
     *
     * Return values:
     *  The mean of the last "window" elements
    */
    uint64_t query(uint64_t& windowSizeMistake) const;
};

#endif
