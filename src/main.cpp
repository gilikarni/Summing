
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
#include <list>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <thread>
#include <vector>

template class std::list< pair<uint64_t,uint64_t> >;

/* Namespace: */

using std::setw;
using namespace std::chrono;
using std::clock;
using std::string;
using std::right;
using std::ifstream;

/* Macros: */

#define INPUT_FILE_NAME "traces_by_size_only"
#define CONF_FILE_NAME "conf"
#define UNUSED(x) (void)(x)

/* A table of the flags to be entered from the user and have a value.
 * First parameter is the flag's name.
 * Second parameter is the flag's descriptor.
 */
#define FLAGS_WITH_VALUE_TABLE \
X(window,		"The size of the window to sum of"											) \
X(range,		"The range of the packet sizes"												) \
X(epsilon,		"The allowed mistake in the sum"											) \
X(tau,			"The allowed mistake in the window size"									) \
X(iterations,	"The allowed number of iterations"											)

/* A table of the flags to be entered from the user and does not have a value.
 * First parameter is the flag's name.
 * Second parameter is the flag's descriptor.
 */
#define FLAGS_WITHOUT_VALUE_TABLE \
X(calc_times,			"Calculate the average time, can calculate only for only one algorithm at a time."	) \
X(calc_times_update,	"Calculate the average time, can calculate only for only one algorithm at a time."	) \
X(print_query,			"Print the sum that was queried (works only if the input is not too large)"			) \
X(calc_size,			"Calculate the average size of each class"											)

#define FLAGS_SUMMING_OPTIONS \
X(mul,					"Calculate with a multiplicative mistake"											) \
X(add,					"Calculate with an additive mistake"												) \
X(mul_slack,			"Calculate with a multiplicative mistake and a slack window size"					) \
X(add_slack,			"Calculate with an additive mistake and a slack window size"						) \
X(exact,				"Calculate the exact sum"															) \
X(exact_slack,			"Calculate the exact sum on a slack window"											)

/* A table of the flags to be entered from the user and leads to a callback to be called.
 * First parameter is the flag's name.
 * Second parameter is the flag's descriptor.
 * Third parameter is a callback
 */
#define FLAGS_WITH_CALLBACK_TABLE \
X(help,			"Print optional parameters",	printHelp	)

/* Globals: */

std::ofstream main_outputFile;

/* Generate the size file objects */
#define X(_paramName, ...) \
	std::ofstream _paramName##SizeOutputFile;
	FLAGS_SUMMING_OPTIONS
#undef X

/* Generate the size file objects */
#define X(_paramName, ...) \
	std::ofstream _paramName##MistakeOutputFile;
	FLAGS_SUMMING_OPTIONS
#undef X

/* Generate variable to contain the value */
#define X(_paramName, ...) \
	double _paramName;
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
		FLAGS_SUMMING_OPTIONS;
	#undef X

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
		bool is_##_paramName = false;
		FLAGS_WITHOUT_VALUE_TABLE;
	#undef X

	#define X(_paramName, ...) \
		bool is_##_paramName = false;
		FLAGS_SUMMING_OPTIONS;
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
		int numberOfMatches = 0;

		#define X(_paramName, ...) 									\
			if (!arg.compare(string("--") + string(#_paramName))) 	\
			{ 														\
				is_##_paramName = true;								\
				bAlgoDefined = true;								\
				numberOfMatches++;									\
			}
			FLAGS_SUMMING_OPTIONS;
		#undef X

		#define X(_paramName, ...) 									\
			if (!arg.compare(string("--") + string(#_paramName))) 	\
			{ 														\
				is_##_paramName = true;								\
				numberOfMatches++;									\
			}
			FLAGS_WITHOUT_VALUE_TABLE;
		#undef X

		#define X(_paramName, _paramDescription, callback) 			\
			if (!arg.compare(string("--") + string(#_paramName))) 	\
			{ 														\
				callback();											\
				numberOfMatches++;									\
			}
			FLAGS_WITH_CALLBACK_TABLE;
		#undef X

		#define X(_paramName, ...) \
			if (!arg.compare(string("--") + string(#_paramName))) 	\
			{ 														\
				argIdx++;											\
				_paramName = atof(argv[argIdx]);					\
				numberOfMatches++;									\
			}
			FLAGS_WITH_VALUE_TABLE;
		#undef X

		if (numberOfMatches == 0)
		{
			std::cout << "No such parameter " << arg << std::endl;
			return 1;
		}

	}

	/* If no summing algorithm was defined all the algorithms should run */
	if (!bAlgoDefined)
	{
		confFile.clear();
		confFile.seekg(0, confFile.beg);
		while (!confFile.eof())
		{
			string param("");
			string value("");
			int numberOfAlgorithms = 0;
			confFile >> param;

			#define X(_paramName, ...) 									\
				if (!param.compare(#_paramName)) 						\
				{ 														\
					numberOfAlgorithms++;								\
					is_##_paramName = true;								\
				}
				FLAGS_SUMMING_OPTIONS;
			#undef X
		}
	}

	/* Only one algorithm can run while calculating times */
	if (is_calc_times || is_calc_times_update)
	{
		int numberOfAlgorithms = 0;

		#define X(_paramName, ...) 									\
			if (is_##_paramName)				 					\
			{ 														\
				numberOfAlgorithms++;								\
			}
			FLAGS_SUMMING_OPTIONS;
		#undef X

		if (numberOfAlgorithms > 1)
		{
			std::cout << "More then one algorithm was specified for speed check."
					<< std::endl;
			return 1;
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

	#define X(_paramName, ...) 														\
		_paramName##SizeOutputFile.open( 											\
				#_paramName"SizeOutput.txt", 										\
				std::ofstream::out | std::ofstream::app); 							\
		if (!_paramName##SizeOutputFile || !_paramName##SizeOutputFile.good()) 		\
		{ 																			\
			std::cout << "Could not open " << #_paramName << "SizeOutput.txt in " 	\
					<< __FILE__ << std::endl; 										\
			throw std::bad_alloc(); 												\
		}																			\
		_paramName##MistakeOutputFile.open( 										\
				#_paramName"MistakeOutput.txt",										\
				std::ofstream::out | std::ofstream::app); 							\
		if (!_paramName##MistakeOutputFile ||										\
			!_paramName##MistakeOutputFile.good()) 									\
		{ 																			\
			std::cout << "Could not open " << #_paramName << "MistakeOutput.txt in "\
					<< __FILE__ << std::endl; 										\
			throw std::bad_alloc(); 												\
		}
		FLAGS_SUMMING_OPTIONS
	#undef X

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

	#define X(_paramName, _paramDescription) \
		 ss << #_paramName << " = " << ((is_##_paramName) ? "true" : "false") << std::endl;
		FLAGS_SUMMING_OPTIONS;
	#undef X

	printLogsToFile(std::cout, ss.str());

	ExactSumming exact_summing(range, window);
	ExactSlackSumming exact_slack_summing(range, window, tau);
	AdditiveSlackMistake add_slack_summing(window, range, tau, epsilon);
	AdditiveMistake add_summing(range, window, epsilon);
	MultiplicativeMistakeSlackSumming mul_slack_summing(range, window, tau, epsilon);
	MultiplicativeMistake mul_summing(range, window, epsilon);

	int numberOfElements = 0;



	double windowDevExact = 0, windowDevAdd = 0, windowDevMul = 0;

	#define X(_paramName, _paramDescription)  \
		uint64_t _paramName##_total_size = 0; \
		double dev_##_paramName = 0;
		FLAGS_SUMMING_OPTIONS;
	#undef X

	UNUSED(dev_exact);

	std::vector<uint64_t> sizes;

	bool fileNotEnded = false;
	std::chrono::duration<double, std::milli> runtime(0);

	do
	{
		fileNotEnded = false;

		while (getline(input, packetSizeInString) && counter++ < iterations)
		{

			uint16_t packetSize = 0;
			packetSize = atoi(packetSizeInString.c_str());
			sizes.push_back(packetSize);
			if (sizes.size() == sizes.max_size()/2)
			{
				fileNotEnded = true;
				break;
			}
		}

		auto t_start = std::chrono::high_resolution_clock::now();

		for (auto packetSize : sizes)
		{
			numberOfElements++;

			if (is_print_query)
			{
				printLogsToFile(main_outputFile,
						"Update with packet size: " << packetSize);
			}

			/* Update all the running algorithms with the new packet. */
			#define X(_paramName, _paramDescription) 			\
				if (is_##_paramName) 							\
				{ 												\
					_paramName##_summing.update(packetSize); 	\
				}
				FLAGS_SUMMING_OPTIONS;
			#undef X

			/* If there is no time calculation this values should be
			 * calculated in order to calculate the mistake.
			 */
			if (!is_calc_times && !is_calc_times_update && !is_exact)
			{
				exact_summing.update(packetSize);
			}

			if (!is_calc_times && !is_calc_times_update && !is_exact_slack)
			{
				exact_slack_summing.update(packetSize);
			}

			/* Only when calculating only the update time we wouldn't want to
			 * query the status.
			 */
			if (!is_calc_times_update)
			{
				double exactSum = 0;
				if (!is_calc_times || is_exact)
				{
					exactSum = exact_summing.query();
				}

				if (is_exact && is_print_query)
				{
					printLogsToFile(main_outputFile, "Exact sum = " << exactSum);
				}

				double exactSlackSum = 0;
				if (!is_calc_times  || is_exact_slack)
				{
					exactSlackSum = exact_slack_summing.query(windowSizeMistake);
				}

				if (is_exact_slack)
				{
					dev_exact_slack += abs(exactSlackSum - exactSum);

					windowDevExact += windowSizeMistake;
					if (is_print_query)
					{
						printLogsToFile(main_outputFile,
								"Exact sum with slack window = " << exactSlackSum <<
								", window size slackiness = " << windowSizeMistake);
					}
				}

				if(is_add_slack)
				{
					double addSalckSum = add_slack_summing.query(windowSizeMistake);

					dev_add_slack += abs(addSalckSum - exactSlackSum);

					windowDevAdd += windowSizeMistake;
					if (is_print_query)
					{
						printLogsToFile(main_outputFile,
								"Sum with additive mistake slack window = " << addSalckSum <<
								", window size slackiness = " << windowSizeMistake);
					}
				}

				if(is_mul_slack)
				{
					double mulSlackSum = mul_slack_summing.query(windowSizeMistake);

					dev_mul_slack += abs(mulSlackSum - exactSlackSum) / exactSlackSum;

					windowDevMul += windowSizeMistake;

					if (is_print_query)
					{
						printLogsToFile(main_outputFile,
								"Sum with multiplicative slack window = " << mulSlackSum <<
								", window size slackiness = " << windowSizeMistake);
					}
				}

				if (is_add)
				{
					double addSum = add_summing.query();

					dev_add += abs(addSum - exactSum);

					if (is_print_query)
					{
						printLogsToFile(main_outputFile, "Sum with additive mistake = "
								<< addSum << ", window size slackiness = " << windowSizeMistake);
					}
				}

				if (is_mul)
				{
					double mulSum = mul_summing.query();
					dev_mul += abs(mulSum - exactSum) / exactSum;
					if (is_print_query)
					{
						printLogsToFile(main_outputFile,
								"Sum with multiplicative mistake = " << mulSum <<
								", window size slackiness = " << windowSizeMistake);
					}
				}
			}

			if (is_calc_size)
			{
				#define X(_paramName, ...) \
					_paramName##_total_size += _paramName##_summing.getSize();
					FLAGS_SUMMING_OPTIONS;
				#undef X
			}
		}

		auto t_end = std::chrono::high_resolution_clock::now();
		runtime += t_end - t_start;
	} while(fileNotEnded);

	if (!is_calc_times && !is_calc_times_update)
	{
		/* Print average mistakes to screen and file */

		#define X(_paramName, ...) 																\
			if (is_##_paramName)																\
			{																					\
				_paramName##MistakeOutputFile <<												\
						(double)dev_##_paramName / numberOfElements << std::endl;		\
			}
			FLAGS_SUMMING_OPTIONS;
		#undef X

		std::cout << std::endl;
	}


	if (is_calc_times || is_calc_times_update)
	{
		main_outputFile << "Average time (in milliseconds) = " <<
				(double)(runtime.count()) / (double)numberOfElements << std::endl;
	}

	/* Print average sizes to screen and file */

	if (is_calc_size)
	{
		#define X(_paramName, ...) 																\
			if (is_##_paramName)																\
			{																					\
				_paramName##SizeOutputFile <<													\
						(double)_paramName##_total_size / numberOfElements << std::endl;		\
			}
			FLAGS_SUMMING_OPTIONS;
		#undef X
	}

	return 0;
}


