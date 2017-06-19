/*
 * utils.cpp
 *
 *  Created on: Jun 13, 2017
 *      Author: compm
 */

#include "utils.h"
#include <cmath>

/*
 * Function name: roundV
 *
 * Description:
 *  Return zz, the closest number to z such that zz * 2^z is an integer
 *
 * Parameters:
 *  z - the number to round
 *  v - the resolution to round to
 *
 * Return values:
 *  None
*/
double roundV(
		const double& z,
		const uint64_t& v)
{
	double powV = pow(2,v);
	double closestInteger = round(z*powV);
	double zz = closestInteger / powV;

	return zz;
}
