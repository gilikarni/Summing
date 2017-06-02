/*
 * packet.h
 *
 *  Created on: Jun 2, 2017
 *      Author: compm
 */

#ifndef PARSER_PACKET_H_
#define PARSER_PACKET_H_

/* Includes: */
#include <string>
#include "time.h"

using std::string;

/*
 Class name: Packet

 Description:
 This class identifies a packet that was delivered
 */
class Packet
{
	/* The time of the deliver */
	Time time;
	/* The ip from whom the package (including port) */
	string ip;
	/* The size of the package */
	uint64_t size;

public:

	/* Constructor: */

	Packet(string trace);

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
	uint8_t getHour() const;

	/*
	 Function name: Packet::getMinute

	 Description:
	 An API to get the minute of the deliver

	 Parameters:
	 None

	 Return values:
	 The minute of the deliver
	 */
	uint8_t getMinute() const;

	/*
	 Function name: Packet::getSecond

	 Description:
	 An API to get the second of the deliver

	 Parameters:
	 None

	 Return values:
	 The second of the deliver
	 */
	double getSecond() const;

	/*
	 Function name: Packet::getTimeAsString

	 Description:
	 An API to get a string describing the time of the deliver

	 Parameters:
	 None

	 Return values:
	 A string describing the time of the deliver
	 */
	string getTimeAsString() const;

	/*
	 Function name: Packet::getIp

	 Description:
	 An API to get a string describing the time of the deliver

	 Parameters:
	 None

	 Return values:
	 A string describing the ip address
	 */
	string getIp() const;

	/*
	 Function name: Packet::getSize

	 Description:
	 An API to get a string describing the time of the deliver

	 Parameters:
	 None

	 Return values:
	 The size of the package
	 */
	uint64_t getSize() const;
};

#endif /* PARSER_PACKET_H_ */
