/* Includes: */
#include "parser.h"
#include <exception>

/* Namespace: */
using std::string;
using std::bad_alloc;

/* Macros: */
#define SIZE_ONLY_FILE_NAME "traces_by_size_only"
#define OUTPUT_FILE_NAME "output"

/*
 * Traces example:
 *
 * 16:00:00.000001 99.158.44.6.42754 202
 * 16:00:00.000003 202.211.86.181.59103 1440
 * 16:00:00.000004 161.69.48.219.13782 1448
 * 16:00:00.000006 147.73.59.126.443 1430
 * 16:00:00.000017 147.73.59.126.443 1430
 * 16:00:00.000019 161.69.48.219.13782 1448
 * 16:00:00.000025 137.32.168.228.49213 85
 * 16:00:00.000027 147.73.59.126.443 1430
 * 16:00:00.000029 161.69.48.219.13782 1448
 * 16:00:00.000031 137.227.47.182.80 1448
 */

/* Static functions: */

void Parser::printLogs(const string& output){
	outputFile << "parser :: " << output << std::endl;
}

/* Constructors: */
Parser::Parser(const string& tracesFilename, const ParserType& fileType) :
		type(fileType), outputFile(
		OUTPUT_FILE_NAME)
{
	string parserFileName("");

	switch(fileType)
	{
	case PARSER_FILE_TYPE__SIZE_ONLY:
		parserFileName = SIZE_ONLY_FILE_NAME;
		break;
	default:
		printLogs("Wrong parsre file name");
		throw bad_alloc();
	}

	parserFile(parserFileName.c_str());

	if (parserFile.good())
	{
		printLogs(string(SIZE_ONLY_FILE_NAME) + string(" already exist"));

		/* The file already exist */
		parserFile.open(SIZE_ONLY_FILE_NAME,
				fstream::in | fstream::out | fstream::binary);

		if (parserFile.good())
		{
			printLogs(string("Successfully opened ") + parserFileName +
					string(" for reading and writing"));
		}
		else
		{
			printLogs("Failed to open " parserFileName);
			throw bad_alloc();
		}
		return;
	}

	/* The file doesn't exist ==> create it */
	ifstream inputFile(tracesFilename.c_str());
	if (inputFile.good())
	{
		printLogs(string("Failed to open ") + tracesFilename);
		throw bad_alloc();
	}

	printLogs(string("Successfully opened ") + tracesFilename + string(" for reading and writing"));

	parserFile.open(SIZE_ONLY_FILE_NAME,
			fstream::in | fstream::out | fstream::binary);

	if (parserFile.good())
	{
		printLogs("Successfully opened " parserFileName " for reading and writing");
	}
	else
	{
		printLogs("Failed to open " parserFileName);
		throw bad_alloc();
	}
}



/* API: */

void Parser::erase()
{
	string parserFileName("");

	switch(fileType)
	{
	case PARSER_FILE_TYPE__SIZE_ONLY:
		parserFileName = SIZE_ONLY_FILE_NAME;
		break;
	default:
		printLogs("Wrong parser file name");
		throw bad_alloc();
	}

	parserFile(parserFileName);

	if (!fstream(parserFileName))
	{
		printLogs("ERROR: parser file doesn't exist");
		return;
	}

	std::remove(parserFileName);

	if (fstream(parserFileName))
	{
		printLogs(string("failed to remove ") + parserFileName);
	}
	else
	{
		printLogs(string("Succefuly removed ") + parserFileName);
	}
}
