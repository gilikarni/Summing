/*
 * packet.h
 *
 *  Created on: Jun 2, 2017
 *      Author: compm
 */

#ifndef PARSER_PACKET_H_
#define PARSER_PACKET_H_

/* Includes: */
#include "parser_time.h"

using std::string;

/*
 Class name: Packet

 Description:
 This class identifies a packet that was delivered
 */
class Packet
{
	/* The time of the deliver */
	ParserTime time_;
	/* The ip from whom the package (including port) */
	string ip;
	/* The size of the package */
	uint64_t size;

	/* Input string */
	const string input;

public:

	/* Constructor: */

	Packet(string trace);

	/* API: */

	uint8_t getHour() const;

	uint8_t getMinute() const;

	double getSecond() const;

	string getTimeAsString() const;

	string getIp() const;

	uint64_t getSize() const;
};

#endif /* PARSER_PACKET_H_ */
