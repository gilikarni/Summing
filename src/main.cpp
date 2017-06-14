
/* Includes: */

#include "utils.h"
#include <cmath>
#include <string>
#include "exact/exact.h"
#include "exact_slack_window/exact_slack_window.h"
#include "additive_mistake/additive_mistake.h"
#include "additive_mistake_slack_window/additive_mistake_slack_window.h"
#include "multiplicative_mistake/multiplicative_mistake.h"
#include "multiplicative_mistake_slack_window/multiplicative_mistake_slack_window.h"

/* Namespace: */

/* Macros: */

#define NUM_OF_ITER 500
#define INPUT_FILE_NAME "/home/compm/Summing/src/traces_by_size_only"

#define WINDOW_FLAG "--window"
#define RANGE_FLAG "--range"
#define EPSILON_FLAG "--epsilon"
#define TAU_FLAG "--tau"
#define ITER_FLAG "--Iterations"

/* A table of the flags to be entered from the user and have a value.
 * First parameter is the flag's name.
 * Second parameter is the flag's descriptor.
 */
#define FLAGS_WITH_VALUE_TABLE \
X(window,		"The size of the window to sum of"			) \
X(range,		"The range of the packet sizes"				) \
X(epsilon,		"The allowed mistake in the mean"			) \
X(tau,			"The allowed mistake in the window size"	) \
X(iterations,	"The allowed number of iterations"			)

/* A table of the flags to be entered from the user and does not have a value.
 * First parameter is the flag's name.
 * Second parameter is the flag's descriptor.
 */
#define FLAGS_WITHOUT_VALUE_TABLE \
X(mul,			"Calculate with a multiplicative mistake"							) \
X(add,			"Calculate with an additive mistake"								) \
X(mul_slack,	"Calculate with a multiplicative mistake and a slack window size"	) \
X(add_slack,	"Calculate with an additive mistake and a slack window size"		) \
X(exact,		"Calculate the exact mean"											) \
X(exact_slack,	"Calculate the exact mean on a slack window"						)

/* A table of the flags to be entered from the user and leads to a callback to be called.
 * First parameter is the flag's name.
 * Second parameter is the flag's descriptor.
 * Third parameter is a callback
 */
#define FLAGS_WITH_CALLBACK_TABLE \
X(help,			"Print optional parameters",	printHelp	)

/* Globals: */

std::ofstream main_outputFile;
uint64_t range;
uint64_t iterations;
uint16_t window;
double tau;
double epsilon;

#define X(_paramName, ...) \
	string _paramName##Flag;
	FLAGS_WITHOUT_VALUE_TABLE
#undef X

#define X(_paramName, ...) \
	string _paramName##Flag;
	FLAGS_WITH_CALLBACK_TABLE
#undef X

#define X(_paramName, ...) \
	string _paramName##Flag;
	FLAGS_WITH_VALUE_TABLE
#undef X

/* Static functions: */

/*
 * Function name: printHelp
 *
 * Description:
 *  Print all the optional parameters
 *
 * Parameters:
 *  None
 *
 * Return values:
 *  None
*/
void printHelp()
{
	std::cout << "The parameters are:" << std::endl << std::endl;
	#define X(_paramName, _paramDescription) \
		std::cout << "--" << #_paramName << " - " << _paramDescription << std::endl;
		FLAGS_WITHOUT_VALUE_TABLE;
	#undef X

	#define X(_paramName, _paramDescription, ...) \
		std::cout << "--" << #_paramName << " - " << _paramDescription << std::endl;
		FLAGS_WITH_CALLBACK_TABLE;
	#undef X

	#define X(_paramName, _paramDescription) \
		std::cout << "--" << #_paramName << " - " << _paramDescription << std::endl;
		FLAGS_WITH_VALUE_TABLE;
	#undef X
}

int main(int argc, char* argv[])
{
	range = 3000;
	window = 100;
	tau = pow(10, -1);
	epsilon = pow(10, -5);
	iterations = 500;
	uint64_t windowSizeMistake = 0;
	string packetSizeInString = "";
	unsigned counter = 0;

	#define X(_paramName, ...) \
		_paramName##Flag = string("--") + string(#_paramName);
		FLAGS_WITHOUT_VALUE_TABLE
	#undef X

	#define X(_paramName, ...) \
		_paramName##Flag = string("--") + string(#_paramName);
		FLAGS_WITH_CALLBACK_TABLE
	#undef X

	#define X(_paramName, ...) \
		_paramName##Flag = string("--") + string(#_paramName);
		FLAGS_WITH_VALUE_TABLE
	#undef X

#define X(_paramName, ...) \
	bool is_##_paramName = false;
	FLAGS_WITHOUT_VALUE_TABLE
#undef X

	for (int argIdx = 1; argIdx < argc - 1; argIdx++)
	{
		string arg(argv[argIdx]);

	#define X(_paramName, ...) 									\
		if (!arg.compare(string("--") + string(#_paramName))) 	\
		{ 														\
			is_##_paramName = true;								\
		}
		FLAGS_WITHOUT_VALUE_TABLE
	#undef X

	#define X(_paramName, _paramDescription, callback) 			\
		if (!arg.compare(string("--") + string(#_paramName))) 	\
		{ 														\
			callback();											\
		}
		FLAGS_WITH_CALLBACK_TABLE
	#undef X

	#define X(_paramName, ...) \
		if (!arg.compare(string("--") + string(#_paramName))) 	\
		{ 														\
			argIdx++;											\
			_paramName = atoll(argv[argIdx]);					\
		}
		FLAGS_WITH_VALUE_TABLE
	#undef X
	}

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
	AdditiveSlackMistake addSlackMistake(window, range, tau, epsilon);
	MultiplicativeMistakeSlackSumming mulSlack(range, window, tau, epsilon);

	while (getline(input, packetSizeInString) && counter++ < iterations)
	{
		uint16_t packetSize = 0;

		packetSize = atoi(packetSizeInString.c_str());

		printLogsToFile(main_outputFile,
				"Update with packet size: " << packetSize);

		exactSumming.update(packetSize);
		if (is_exact_slack)
		{
			exactSlackSumming.update(packetSize);
		}
		if (is_add_slack)
		{
			addSlackMistake.update(packetSize);
		}
		if (is_mul_slack)
		{
			mulSlack.update(packetSize);
		}

		if (is_add)
		{
			// Add a call to update function
		}

		if (is_mul)
		{
			// Add a call to update function
		}

		double mean = exactSumming.query();
		if (is_exact)
		{
			printLogsToFile(main_outputFile, "Exact mean = " << mean);
		}

		if (is_exact_slack)
		{
			mean = exactSlackSumming.query(windowSizeMistake);
			printLogsToFile(main_outputFile, "Exact mean with slack window = " << mean <<
					", window size slackiness = " << windowSizeMistake);
		}

		if(is_add_slack)
		{
			mean = addSlackMistake.query(windowSizeMistake);
			printLogsToFile(main_outputFile, "Mean with additive mistake slack window = " << mean <<
					", window size slackiness = " << windowSizeMistake);
		}

		if(is_mul_slack)
		{
			mean = mulSlack.query(windowSizeMistake);
			printLogsToFile(main_outputFile, "Mean with multiplicative slack window = " << mean <<
					", window size slackiness = " << windowSizeMistake);
		}

		if (is_add)
		{
			// Add a call to query function
		}

		if (is_mul)
		{
			// Add a call to query function
		}
	}
	return 0;
}


