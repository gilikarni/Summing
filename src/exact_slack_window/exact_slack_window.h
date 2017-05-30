
/*
 * File description:
 *
 *
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
    uint8_t tau;

    /* The sum of the last elements */
    uint64_t lastElements;

    /* 1/tau sums of window*tau elements from the elements delivered */
    queue<uint64_t> elements;

public:

    /* Contructors: */
    ExactSlackSumming(const uint64_t& r, const uint64_t& w) :
    	range(r), window(w) {}

    /* API: */
};

#endif
