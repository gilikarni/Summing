/*
 * time.h
 *
 *  Created on: Jun 2, 2017
 *      Author: compm
 */

#ifndef PARSER_PARSER_TIME_H_
#define PARSER_PARSER_TIME_H_

/* Includes: */
#include <string>

using std::string;

/*
 Class name: Time

 Description:
 The class contains the time of a package
 that was delivered
 */
class ParserTime
{
	/* The hour that the package was received */
	uint8_t hour;
	/* The minute that the package was received */
	uint8_t minute;
	/* The second that the package was received */
	double second;
	/* A string describing the time of the deliver */
	string timeStr;

public:

	/* Constructor: */

	ParserTime(string time);

	/* API: */

	uint8_t getHour() const;

	uint8_t getMinute() const;

	double getSecond() const;

	string getTimeAsString() const;
};

#endif /* PARSER_PARSER_TIME_H_ */
