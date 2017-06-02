
#ifndef MULOMISTAKE_SLACKSUMMING
#define MULOMISTAKE_SLACKSUMMING

/*
 * File description:
 *  Each time a new packet arrives we it's value to y. Every w * tau packets
 *  we add a rounded variation of y to the total mean and subtract the oldest
 *  addition.
*/

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

    /* The percentage of the window size which is
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
			const double& t);

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
     *  The mean of the last "window" + windowSizeMistake elements
    */
    uint64_t query(uint64_t& windowSizeMistake) const;
};

#endif
