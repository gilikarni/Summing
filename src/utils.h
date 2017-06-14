/*
 * utils.h
 *
 *  Created on: Jun 13, 2017
 *      Author: compm
 */

#ifndef UTILS_H_
#define UTILS_H_

/* Includes: */

#include <cstdio>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <execinfo.h>
#include <fstream>

using std::bad_alloc;

/* Definitions: */

#define OUTPUT_FILE_NAME "output"

#define printLogsToFile(file, output) \
file << "(" << __FILE__ << ", line " << __LINE__ << "): " << output << std::endl;

/* Function Declarations */

#endif /* UTILS_H_ */
