
/* Includes: */

#include "utils.h"
#include <cmath>
#include "exact/exact.h"
#include "exact_slack_window/exact_slack_window.h"
#include "additive_mistake/additive_mistake.h"
#include "additive_mistake_slack_window/additive_mistake_slack_window.h"
#include "multiplative_mistake/multiplative_mistake.h"
#include "multiplative_mistake_slack_window/multiplative_mistake_slack_window.h"

/* Namespace: */

/* Macros: */

#define NUM_OF_ITER 50
#define INPUT_FILE_NAME "/home/compm/Summing/src/traces_by_size_only"

/* Globals: */

std::ofstream main_outputFile;

int main()
{
	uint64_t range = 1000;
	uint16_t window = 500;
	double tau = pow(10, -2);
	double epsilon = pow(10, -5);
	uint64_t windowSizeMistake = 0;
	string packetSizeInString = "";

	std::ifstream input;

	input.open(INPUT_FILE_NAME);
	if (!input || !input.good())
	{
		std::cout << "Could not open " << INPUT_FILE_NAME << " in "
				<< __FILE__ << std::endl;
		throw std::bad_alloc();
	}

	main_outputFile.open(
			OUTPUT_FILE_NAME,
			std::ofstream::out | std::ofstream::app);
	if (!main_outputFile || !main_outputFile.good())
	{
		std::cout << "Could not open " << OUTPUT_FILE_NAME << " in "
				<< __FILE__ << std::endl;
		throw std::bad_alloc();
	}

	ExactSumming exactSumming(range, window);
	ExactSlackSumming exactSlackSumming(range, window, tau);
	AdditiveSlackMistake additiveSlackMistake(window, range, tau, epsilon);

	while (getline(input, packetSizeInString))
	{
		uint16_t packetSize = 0;

		packetSize = atoi(packetSizeInString.c_str());

		printLogsToFile(main_outputFile,
				"Update with packet size: " << packetSize);

		exactSumming.update(packetSize);
		exactSlackSumming.update(packetSize);
		additiveSlackMistake.update(packetSize);

		exactSumming.query();
		exactSlackSumming.query(windowSizeMistake);
		additiveSlackMistake.query(windowSizeMistake);
	}
	return 0;
}


