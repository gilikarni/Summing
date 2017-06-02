/*
 * packet.cpp
 *
 *  Created on: Jun 2, 2017
 *      Author: compm
 */

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

Packet::Packet(string trace)
{
	stringstream stream(trace);
	string t, s;
	stream >> t;
	time(t);
	stream >> ip;
	stream >> s;
	size(atoll(s));
}

/* Static functions: */

/* API: */


