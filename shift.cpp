/* shift.cpp */
#include <iostream>
#include <stdlib.h>
#include "cipher_tools.hpp"

int main(int argc, char *argv[])
{
	if (argc !=3)
	{
		std::cout << "USAGE: ./shift <FILENAME> <N>\n";
		exit(0);
	}

	shift(argv[1], atoi(argv[2]));  
}
