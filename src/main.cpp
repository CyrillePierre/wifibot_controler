
#include <iostream>
#include "driver.hpp"
#include "cmdparser.hpp"

#define BUFFER_SIZE	128

int main()
{
	char buf[BUFFER_SIZE];
	Driver driver("192.168.0.112");
	CmdParser parser(driver);

	while (std::cin.getline(buf, BUFFER_SIZE))
		std::cout << parser.execute(buf) << std::endl;

	return 0;
}
