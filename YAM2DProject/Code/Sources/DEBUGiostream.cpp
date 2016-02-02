#include "DEBUGiostream.h"
#include <iostream>


void msgstream(std::string msg, bool endline)
{
	std::cout << msg;
	if (endline)
	{
		std::cout << std::endl;
	}
}
void msgstream(std::string msg, std::string msg2, bool endline)
{
	std::cout << msg << ", " << msg2;
	if (endline)
	{
		std::cout << std::endl;
	}
}
void msgstream(float value, bool endline)
{
	std::cout << value;
	if (endline)
	{
		std::cout << std::endl;
	}
}
void msgstream(float value, float value2, bool endline)
{
	std::cout << value << ", " << value2;
	if (endline)
	{
		std::cout << std::endl;
	}
}

void newline()
{
	std::cout << std::endl;
}