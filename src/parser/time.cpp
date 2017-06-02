/*
 * time.cpp
 *
 *  Created on: Jun 2, 2017
 *      Author: compm
 */

/* Includes: */
#include <string>
#include "time.h"

/* Namespace: */
using std::string;
using std::bad_alloc;

/* Macros: */
#define HOUR_START 0
#define HOUR_END 2
#define MINUTE_START 3
#define MINUTE_END 5
#define SECOND_START 6
#define SECOND_END 14

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

/* Constructors: */

Time::Time(const string& time) :
		hour(atoi(time.substr(HOUR_START, HOUR_END).c_str())),
		minute(atoi(time.substr(MINUTE_START, MINUTE_END).c_str())),
		second(atof(time.substr(SECOND_START, SECOND_END).c_str())),
		timeStr(time.substr(HOUR_START, SECOND_END))
{
}

/* Static functions: */

/* API: */

/*
 Function name: Time::getHour

 Description:
 An API to get the hour of the deliver

 Parameters:
 None

 Return values:
 The hour of the deliver
 */
uint8_t Time::getHour() const
{
	return hour;
}

/*
 Function name: Time::getMinute

 Description:
 An API to get the minute of the deliver

 Parameters:
 None

 Return values:
 The minute of the deliver
 */
uint8_t Time::getMinute() const
{
	return minute;
}

/*
 Function name: Time::getSecond

 Description:
 An API to get the second of the deliver

 Parameters:
 None

 Return values:
 The second of the deliver
 */
double Time::getSecond() const
{
	return second;
}

/*
 Function name: Time::getTimeAsString

 Description:
 An API to get a string describing the time of the deliver

 Parameters:
 None

 Return values:
 A string describing the time of the deliver
 */
string Time::getTimeAsString() const
{
	return timeStr;
}
