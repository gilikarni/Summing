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
 *  powV - the resolution to round to
 *
 * Return values:
 *  None
*/
double roundV(
		const double& z,
		const uint64_t& powV,
		const double& v)
{
	if (0 == z)
	{
		return z;
	}

	double zz = 0;
	double roundZ = round(z);

	/* Found out if z is bigger than 1 */
	if (roundZ > 0)
	{
		/* z is bigger than 1 */
		double logRoundz = log(roundZ)/log(2);
		if (logRoundz > v)
		{
			double roundingPower = logRoundz - v;
			double powRound = pow(2, roundingPower);
			zz = z / powRound;
			zz = round(zz);
			zz *= powRound;
		}
		else if (0 == logRoundz)
		{
			zz = round(z);
		}
		else
		{
			double closestInteger = round(z*powV);
			zz = closestInteger / powV;
		}
	}
	else
	{
		double closestInteger = round(z*powV);
		zz = closestInteger / powV;
	}

	return zz;
}
