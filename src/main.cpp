
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

template class std::list< pair<uint64_t,uint64_t> >;

/* Namespace: */

using std::setw;
using namespace std::chrono;
using std::clock;

/* Macros: */

#define INPUT_FILE_NAME "traces_by_size_only"
#define CONF_FILE_NAME "conf"

/* A table of the flags to be entered from the user and have a value.
 * First parameter is the flag's name.
 * Second parameter is the flag's descriptor.
 */
#define FLAGS_WITH_VALUE_TABLE \
X(window,		"The size of the window to sum of"											) \
X(range,		"The range of the packet sizes"												) \
X(epsilon,		"The allowed mistake in the sum"											) \
X(tau,			"The allowed mistake in the window size"									) \
X(iterations,	"The allowed number of iterations"											) \
X(print_times,	"Print the average times to do actions"										) \
X(print_query,	"Print the sum that was queried (works only if the input is not too large)"	)

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
X(exact_slack,	"Calculate the exact sum on a slack window"							)

/* A table of the flags to be entered from the user and leads to a callback to be called.
 * First parameter is the flag's name.
 * Second parameter is the flag's descriptor.
 * Third parameter is a callback
 */
#define FLAGS_WITH_CALLBACK_TABLE \
X(help,			"Print optional parameters",	printHelp	)

/* Globals: */

std::ofstream main_outputFile;
#define X(_paramName, ...) \
	double _paramName;
	FLAGS_WITH_VALUE_TABLE
#undef X

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

	int numberOfElements = 0;

	double devExactSlack = 0, devAddSlack = 0, devMulSlack = 0, devAdd = 0,
			devMul = 0, windowDevExact = 0, windowDevAdd = 0, windowDevMul = 0;

	std::chrono::duration<double, std::milli> durExactUpdate, durExactQuery,
	durExactSlackUpdate, durExactSlackQuery, durMulUpdate, durMulQuery,
	durMulSlackUpdate, durMulSlackQuery, durAddUpdate, durAddQuery,
	durAddSlackUpdate, durAddSlackQuery;

	while (getline(input, packetSizeInString) && counter++ < iterations)
	{
		uint16_t packetSize = 0;
		numberOfElements++;

		packetSize = atoi(packetSizeInString.c_str());

		if (print_query)
		{
			printLogsToFile(main_outputFile,
					"Update with packet size: " << packetSize);
		}

		auto t_start = std::chrono::high_resolution_clock::now();

		exactSumming.update(packetSize);

		auto t_end = std::chrono::high_resolution_clock::now();

		durExactUpdate *= numberOfElements - 1;
		durExactUpdate += t_end - t_start;
		durExactUpdate /= numberOfElements;

		if (is_exact_slack)
		{
			t_start = std::chrono::high_resolution_clock::now();

			exactSlackSumming.update(packetSize);

			t_end = std::chrono::high_resolution_clock::now();
		}

		durExactSlackUpdate *= numberOfElements - 1;
		durExactSlackUpdate += t_end - t_start;
		durExactSlackUpdate /= numberOfElements;

		if (is_add_slack)
		{
			t_start = std::chrono::high_resolution_clock::now();

			addSlackMistake.update(packetSize);

			t_end = std::chrono::high_resolution_clock::now();
		}

		durAddSlackUpdate *= numberOfElements - 1;
		durAddSlackUpdate += t_end - t_start;
		durAddSlackUpdate /= numberOfElements;

		if (is_mul_slack)
		{
			t_start = std::chrono::high_resolution_clock::now();

			mulSlack.update(packetSize);

			t_end = std::chrono::high_resolution_clock::now();
		}

		durMulSlackUpdate *= numberOfElements - 1;
		durMulSlackUpdate += t_end - t_start;
		durMulSlackUpdate /= numberOfElements;

		if (is_add)
		{
			t_start = std::chrono::high_resolution_clock::now();

			addMistake.update(packetSize);

			t_end = std::chrono::high_resolution_clock::now();
		}

		durAddUpdate *= numberOfElements - 1;
		durAddUpdate += t_end - t_start;
		durAddUpdate /= numberOfElements;

		if (is_mul)
		{
			t_start = std::chrono::high_resolution_clock::now();

			mulMistake.update(packetSize);

			t_end = std::chrono::high_resolution_clock::now();
		}

		durMulUpdate *= numberOfElements - 1;
		durMulUpdate += t_end - t_start;
		durMulUpdate /= numberOfElements;

		t_start = std::chrono::high_resolution_clock::now();

		double exactSum = exactSumming.query();

		t_end = std::chrono::high_resolution_clock::now();

		durExactQuery *= numberOfElements - 1;
		durExactQuery += t_end - t_start;
		durExactQuery /= numberOfElements;

		if (is_exact)
		{
			if (print_query)
			{
				printLogsToFile(main_outputFile, "Exact sum = " << exactSum);
			}
		}

		t_start = std::chrono::high_resolution_clock::now();

		double exactSlackSum = exactSlackSumming.query(windowSizeMistake);

		t_end = std::chrono::high_resolution_clock::now();

		durExactSlackQuery *= numberOfElements - 1;
		durExactSlackQuery += t_end - t_start;
		durExactSlackQuery /= numberOfElements;

		if (is_exact_slack)
		{
			devExactSlack *= (numberOfElements - 1);
			devExactSlack += abs(exactSlackSum - exactSum);
			devExactSlack /= numberOfElements;

			windowDevExact *= numberOfElements - 1;
			windowDevExact += windowSizeMistake;
			windowDevExact /= numberOfElements;
			if (print_query)
			{
				printLogsToFile(main_outputFile,
						"Exact sum with slack window = " << exactSlackSum <<
						", window size slackiness = " << windowSizeMistake);
			}
		}

		if(is_add_slack)
		{
			t_start = std::chrono::high_resolution_clock::now();

			double addSalckSum = addSlackMistake.query(windowSizeMistake);

			t_end = std::chrono::high_resolution_clock::now();

			durAddSlackQuery *= numberOfElements - 1;
			durAddSlackQuery += t_end - t_start;
			durAddSlackQuery /= numberOfElements;

			devAddSlack *= (numberOfElements - 1);
			devAddSlack += abs(addSalckSum - exactSlackSum);
			devAddSlack /= numberOfElements;

			windowDevAdd *= numberOfElements - 1;
			windowDevAdd += windowSizeMistake;
			windowDevAdd /= numberOfElements;
			if (print_query)
			{
				printLogsToFile(main_outputFile,
						"Sum with additive mistake slack window = " << addSalckSum <<
						", window size slackiness = " << windowSizeMistake);
			}
		}

		if(is_mul_slack)
		{
			t_start = std::chrono::high_resolution_clock::now();

			double mulSlackSum = mulSlack.query(windowSizeMistake);

			t_end = std::chrono::high_resolution_clock::now();

			durMulSlackQuery *= numberOfElements - 1;
			durMulSlackQuery += t_end - t_start;
			durMulSlackQuery /= numberOfElements;

			devMulSlack *= (numberOfElements - 1);
			devMulSlack += abs(mulSlackSum - exactSlackSum);
			devMulSlack /= numberOfElements;

			windowDevMul *= numberOfElements - 1;
			windowDevMul += windowSizeMistake;
			windowDevMul /= numberOfElements;
			if (print_query)
			{
				printLogsToFile(main_outputFile,
						"Sum with multiplicative slack window = " << mulSlackSum <<
						", window size slackiness = " << windowSizeMistake);
			}
		}

		if (is_add)
		{
			t_start = std::chrono::high_resolution_clock::now();

			double addSum = addMistake.query();

			t_end = std::chrono::high_resolution_clock::now();

			durAddQuery *= numberOfElements - 1;
			durAddQuery += t_end - t_start;
			durAddQuery /= numberOfElements;

			devAdd *= (numberOfElements - 1);
			devAdd += abs(addSum - exactSum);
			devAdd /= numberOfElements;
			if (print_query)
			{
				printLogsToFile(main_outputFile, "Sum with additive mistake = "
						<< addSum << ", window size slackiness = " << windowSizeMistake);
			}
		}

		if (is_mul)
		{
			t_start = std::chrono::high_resolution_clock::now();

			double mulSum = mulMistake.query();

			t_end = std::chrono::high_resolution_clock::now();

			durMulQuery *= numberOfElements - 1;
			durMulQuery += t_end - t_start;
			durMulQuery /= numberOfElements;

			devMul *= (numberOfElements - 1);
			devMul += abs(mulSum - exactSum);
			devMul /= numberOfElements;
			if (print_query)
			{
				printLogsToFile(main_outputFile,
						"Sum with multiplicative mistake = " << mulSum <<
						", window size slackiness = " << windowSizeMistake);
			}
		}
	}

	main_outputFile << "R*W*epsilon = " << range * window * epsilon <<
			std::endl << std::endl <<
			"The average mistakes were:" << std::endl <<
			"Exact summing over a slacky window - "
			<< devExactSlack << std::endl <<
			"Summing over a slacky window with an additive mistake - "
			<< devAddSlack << std::endl <<
			"Summing over a slacky window with a multiplicative mistake - "
			<< devMulSlack << std::endl <<
			"Summing over an exact window with an additive mistake - "
			<< devAdd << std::endl <<
			"Summing over an exact window with a multiplicative mistake - "
			<< devMul << std::endl << std::endl;

	if (print_times)
	{
		main_outputFile << "Average times was: (in milliseconds)" << std::endl <<
			"Exact summing - update: " <<
			durExactUpdate.count() << " query: " << durExactQuery.count() << std::endl <<
			"Exact summing over a slacky window - update :"
			<< durExactSlackUpdate.count() << " query: " << durExactSlackQuery.count() << std::endl <<
			"Summing over a slacky window with an additive mistake - update: "
			<< durAddSlackUpdate.count() << " query: " << durAddSlackQuery.count() << std::endl <<
			"Summing over a slacky window with a multiplicative mistake - update: "
			<< durMulSlackUpdate.count() << " query: " << durMulSlackQuery.count() << std::endl <<
			"Summing over an exact window with an additive mistake - update: "
			<< durAddUpdate.count() << " query: " << durAddQuery.count() << std::endl <<
			"Summing over an exact window with a multiplicative mistake - update: "
			<< durMulUpdate.count() << " query: " << durMulQuery.count() << std::endl << std::endl;
	}
	return 0;
}


