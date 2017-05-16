#pragma once

/* 
 * File description:
 *  This file describes the API of an algorithm of summing on a sliding window in
 *  size W of elements with size smaller then R and larger than 0.
 *  This is a naive algorithm which saves the last W elements and the mean of those
 *  elements. Every time that we need to update the sum we subtract the oldest element
 *  from the sum and add a new one.
 *
 * All the function in this API perform:
 *  O(1) - time complicity
 *  O(W*R) - memory complicity
*/

#ifndef NOMISTAKE_ACCURATESUMMING
#define NOMISTAKE_ACCURATESUMMING

/* Includes: */
#include <queue>

using std::queue;

class ExactSumming
{
    /* The range of the sizes */
    const uint64_t range;

    /* The size of the window to sum */
    const uint64_t window;

    /* The average of the window */
    uint16_t mean;

    /* The last "window" elemants */
    queue<uint64_t> elements;

    /* The minimum between the number of elements 
    that was alredy seen and "window" */
    uint64_t numberOfElementsSeen;

public:

    /* Constructors: */

    ExactSumming(
    		const uint64_t& _range,
			const uint16_t& _window);

    /* API: */
    
    /*
     * Function name: ExactSumming::update
     *
     * Description:
     *  Update the mean of the sliding window, i.e, Adding the new
     *  element to the sum and omit the oldest element.
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
     * Function name: ExactSumming::query
     *
     * Description:
     *  Return the mean of the last "window" elements
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
