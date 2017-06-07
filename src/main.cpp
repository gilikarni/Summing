
/* Includes: */

#include <cstdio>
#include <iostream>
#include "parser/parser.h"
#include <exception>
#include <stdexcept>
#include <execinfo.h>


using std::bad_alloc;

int main()
{
	try
	{
		Parser parser;
		std::cout << "Working" <<std::endl;
		parser.erase();
	}
	catch (bad_alloc ex)
	{
		std::cout << ex.what() <<std::endl;
	}
	return 0;
}


