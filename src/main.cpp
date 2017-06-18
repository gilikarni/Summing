
/* Includes: */

#include "utils.h"
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>
#include "exact/exact.h"
#include "exact_slack_window/exact_slack_window.h"
#include "additive_mistake/additive_mistake.h"
#include "additive_mistake_slack_window/additive_mistake_slack_window.h"
#include "multiplicative_mistake/multiplicative_mistake.h"
#include "multiplicative_mistake_slack_window/multiplicative_mistake_slack_window.h"

/* Namespace: */

using std::setw;

/* Macros: */

#define NUM_OF_ITER 500
#define INPUT_FILE_NAME "/home/compm/Summing/src/traces_by_size_only"
#define CONF_FILE_NAME "conf"

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
X(epsilon,		"The allowed mistake in the sum"			) \
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
X(exact,		"Calculate the exact sum"											) \
X(exact_slack,	"Calculate the exact sum on a slack window"						)

/* A table of the flags to be entered from the user and leads to a callback to be called.
 * First parameter is the flag's name.
 * Second parameter is the flag's descriptor.
 * Third parameter is a callback
 */
#define FLAGS_WITH_CALLBACK_TABLE \
X(help,			"Print optional parameters",	printHelp	)

/* Globals: */

std::ofstream main_outputFile;
double range;
double iterations;
double window;
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
	std::cout << "The parameters are:" << std::endl << "(Defult parameters configurable in "
			<< CONF_FILE_NAME << ")" << std::endl << std::endl;
	std::cout << std::setfill( ' ' );
	#define X(_paramName, _paramDescription) \
		std::cout << std::setw(2) << right << "--" << #_paramName << \
		std::setw(20 - 1 - string(#_paramName).size()) << \
		" " << std::setw(20) << _paramDescription << std::endl;
		FLAGS_WITHOUT_VALUE_TABLE;
	#undef X

	#define X(_paramName, _paramDescription) \
		std::cout << std::setw(2) << right << "--" << #_paramName << \
		std::setw(20 - 1 - string(#_paramName).size()) << \
		" " << std::setw(20) << _paramDescription << std::endl;
		FLAGS_WITH_VALUE_TABLE;
	#undef X

	#define X(_paramName, _paramDescription, ...) \
		std::cout << std::setw(2) << right << "--" << #_paramName << \
		std::setw(20 - 1 - string(#_paramName).size()) << \
		" " << std::setw(20) << _paramDescription << std::endl;
		FLAGS_WITH_CALLBACK_TABLE;
	#undef X

	std::cout << std::endl;
	exit(0);
}

int main(int argc, char* argv[])
{
	uint64_t windowSizeMistake = 0;
	string packetSizeInString = "";
	unsigned counter = 0;
	ifstream confFile(CONF_FILE_NAME);

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

	while (!confFile.eof())
	{
		string param("");
		string value("");
		confFile >> param;
		#define X(_paramName, ...) \
			if (!param.compare(#_paramName))	 					\
			{ 														\
				confFile >> value;									\
				confFile >> value;									\
				_paramName = stod(value);							\
			}
			FLAGS_WITH_VALUE_TABLE
		#undef X
	}

	bool bAlgoDefined = false;

	for (int argIdx = 1; argIdx < argc; argIdx++)
	{
		string arg(argv[argIdx]);

		#define X(_paramName, ...) 									\
			if (!arg.compare(string("--") + string(#_paramName))) 	\
			{ 														\
				is_##_paramName = true;								\
				bAlgoDefined = true;								\
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
				_paramName = atof(argv[argIdx]);					\
			}
			FLAGS_WITH_VALUE_TABLE
		#undef X
	}

	if (!bAlgoDefined)
	{
		confFile.clear();
		confFile.seekg(0, confFile.beg);
		while (!confFile.eof())
		{
			string param("");
			string value("");
			confFile >> param;

			#define X(_paramName, ...) 									\
				if (!param.compare(#_paramName)) 						\
				{ 														\
					is_##_paramName = true;								\
				}
				FLAGS_WITHOUT_VALUE_TABLE
			#undef X
		}
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

	std::stringstream ss;

	ss << "Starting to sum, with parameters:" << std::endl;

	#define X(_paramName, _paramDescription) \
		 ss << #_paramName << " = " << _paramName << std::endl;
		FLAGS_WITH_VALUE_TABLE;
	#undef X

	#define X(_paramName, _paramDescription) \
		 ss << #_paramName << " = " << ((is_##_paramName) ? "true" : "false") << std::endl;
		FLAGS_WITHOUT_VALUE_TABLE;
	#undef X

	printLogsToFile(std::cout, ss.str());

	ExactSumming exactSumming(range, window);
	ExactSlackSumming exactSlackSumming(range, window, tau);
	AdditiveSlackMistake addSlackMistake(window, range, tau, epsilon);
	AdditiveMistake addMistake(range, window, epsilon);
	MultiplicativeMistakeSlackSumming mulSlack(range, window, tau, epsilon);
	MultiplicativeMistake mulMistake(range, window, epsilon);

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
			addMistake.update(packetSize);
		}

		if (is_mul)
		{
			mulMistake.update(packetSize);
		}

		double sum = exactSumming.query();
		if (is_exact)
		{
			printLogsToFile(main_outputFile, "Exact sum = " << sum);
		}

		if (is_exact_slack)
		{
			sum = exactSlackSumming.query(windowSizeMistake);
			printLogsToFile(main_outputFile, "Exact sum with slack window = " << sum <<
					", window size slackiness = " << windowSizeMistake);
		}

		if(is_add_slack)
		{
			sum = addSlackMistake.query(windowSizeMistake);
			printLogsToFile(main_outputFile, "Sum with additive mistake slack window = " << sum <<
					", window size slackiness = " << windowSizeMistake);
		}

		if(is_mul_slack)
		{
			sum = mulSlack.query(windowSizeMistake);
			printLogsToFile(main_outputFile, "Sum with multiplicative slack window = " << sum <<
					", window size slackiness = " << windowSizeMistake);
		}

		if (is_add)
		{
			sum = addMistake.query();
			printLogsToFile(main_outputFile, "Sum with additive mistake = " << sum <<
								", window size slackiness = " << windowSizeMistake);
		}

		if (is_mul)
		{
			sum = mulMistake.query();
		}
	}
	return 0;
}


