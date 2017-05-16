/* Includes: */
#include "parser.h"
#include <string>
#include <exception>

/* Namespace: */
using std::string;
using std::bad_alloc;

/* Makros: */
#define HOUR_START 0
#define HOUR_END 2
#define MINUTE_START 3
#define MINUTE_END 5
#define SECOND_START 6
#define SECOND_END 14

/* Constractors: */
Time::Time(const string& time) : 
    hour(atoi(time.substr(HOUR_START, HOUR_END).c_str)), 
    minute(atoi(time.substr(MINUTE_START, MINUTE_END).c_str)), 
    second(atof(time.substr(SECOND_START, SECOND_END).c_str)){}

/* Static functions: */

/* API: */
