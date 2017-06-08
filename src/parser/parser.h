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
	ParserType type;

	string parserFileName;

	ofstream outputFile;

	fstream parserFile;

	string findParserFileName();

public:
	/* Constructors: */
	Parser(const string& tracesFilename = "projects.dump",
			const ParserType& fileType = PARSER_FILE_TYPE__SIZE_ONLY);

	/* Destructor: */
	~Parser();

	/* API: */
	void erase();
};

#endif
