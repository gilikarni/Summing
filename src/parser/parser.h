/*
 File description:
 This file contain the API for parsing the input traces
 */

#ifndef PARSER_H
#define PARSER_H

/* Includes: */
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <ostream>
#include <fstream>

using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;

typedef enum
{
	PARSER_FILE_TYPE__SIZE_ONLY

} ParserType;

class Parser
{
	fstream parserFile;

	ParserType type;

	ofstream outputFile;

	void printLogs(const string& output);

	string findParserFileName();

public:
	/* Constructors: */
	Parser(const string& tracesFilename = "projects.dump",
			const ParserType& fileType = PARSER_FILE_TYPE__SIZE_ONLY);

	/* API: */
	void erase();
};

#endif
