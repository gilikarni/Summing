
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
		parser.erase();
	}
	catch (bad_alloc ex)
	{
		std::cout << ex.what() <<std::endl;
	}

	std::cout << "Done" <<std::endl;
	return 0;
}


