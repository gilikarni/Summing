/*
 * packet.cpp
 *
 *  Created on: Jun 2, 2017
 *      Author: compm
 */

#define _GLIBCXX_USE_CXX11_ABI 0

/* Includes: */
#include "packet.h"
#include <string>
#include <exception>

/* Namespace: */
using std::string;
using std::bad_alloc;
using std::stringstream;

/* Macros: */

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

Packet::Packet(const string& trace) :
		input(trace)
{
	stringstream stream(input);
	string t, s;
	stream >> t;
	time(t);
	stream >> ip;
	stream >> s;
	size(atoll(s));
}

/* Static functions: */

/* API: */

/*
 Function name: Packet::getHour

 Description:
 An API to get the hour of the deliver

 Parameters:
 None

 Return values:
 The hour of the deliver
 */
uint8_t Packet::getHour() const
{
	return time.getHour();
}

/*
 Function name: Packet::getMinute

 Description:
 An API to get the minute of the deliver

 Parameters:
 None

 Return values:
 The minute of the deliver
 */
uint8_t Packet::getMinute() const
{
	return time.getMinute();
}

/*
 Function name: Packet::getSecond

 Description:
 An API to get the second of the deliver

 Parameters:
 None

 Return values:
 The second of the deliver
 */
double Packet::getSecond() const
{
	return time.getMinute();
}

/*
 Function name: Packet::getTimeAsString

 Description:
 An API to get a string describing the time of the deliver

 Parameters:
 None

 Return values:
 A string describing the time of the deliver
 */
string Packet::getTimeAsString() const
{
	return time.getTimeAsString();
}

/*
 Function name: Packet::getIp

 Description:
 An API to get a string describing the time of the deliver

 Parameters:
 None

 Return values:
 A string describing the ip address
 */
string Packet::getIp() const
{
	return ip;
}

/*
 Function name: Packet::getSize

 Description:
 An API to get a string describing the time of the deliver

 Parameters:
 None

 Return values:
 The size of the package
 */
uint64_t Packet::getSize() const
{
	return size;
}

