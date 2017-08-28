
#ifndef MULOMISTAKE_SLACKSUMMING
#define MULOMISTAKE_SLACKSUMMING

/*
 * File description:
 *  Each time a new packet arrives we it's value to y. Every w * tau packets
 *  we add a rounded variation of y to the total sum and subtract the oldest
 *  addition.
*/

/* Includes: */
#include <vector>
#include <cstdint>

using std::vector;

class MultiplicativeMistakeSlackSumming
{
    /* The range of the sizes */
    const uint64_t range;

    /* The size of the window to sum */
    const uint64_t window;

    /* The average of the window */
    uint64_t sum;

    /* The percentage of the window size which is
    aloud to add*/
    const double tau;

    /* The allowed mistake in the sum */
	const double epsilon;

    /* The sum of the last elements */
    uint64_t lastElements;

    /* 1/tau sums of window*tau elements from the elements delivered */
    vector<double> elements;

    /* The number of elements that was summed at the last iteration */
    uint64_t diff;

    /* The size of the summing blocks */
    uint64_t blockSize;

public:

    /* Constructors: */

    MultiplicativeMistakeSlackSumming(
    		const uint64_t& _range,
			const uint64_t& _window,
			const double& _tau,
			const double& _epsilon);

    /* Destructors */

    ~MultiplicativeMistakeSlackSumming();

    /* API: */

    void update(const uint16_t& packetSize);

    double query(uint64_t& windowSizeMistake) const;

    uint64_t getSize() const;
};

#endif
