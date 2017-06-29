
/* 
 * File description:
 *  This file describes the API of an algorithm of summing on a sliding window in
 *  size W of elements with size smaller then R and larger than 0.
 *  This is a naive algorithm which saves the last W elements and the sum of those
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
#include <vector>
#include <cstdint>
#include <fstream>
#include <iostream>


using std::vector;

extern std::ofstream outputFile;

class ExactSumming
{
    /* The range of the sizes */
    const uint64_t range;

    /* The size of the window to sum */
    const uint64_t window;

    /* The average of the window */
    double sum;

    /* The last "window" elemants */
    vector<uint16_t> elements;

public:

    /* Constructors: */

    ExactSumming(
    		const uint64_t& _range,
			const uint16_t& _window);

    ~ExactSumming();

    /* API: */

    void update(const uint16_t& packatSize);

    double query() const;
};

#endif
