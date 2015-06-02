
#include <iostream>
#include "driver.hpp"
#include "cmdparser.hpp"

#include <sstream>

#define BUFFER_SIZE	128

int main()
{
	char buf[BUFFER_SIZE];
	Driver driver("localhost");
	CmdParser parser(driver);

	std::ostringstream oss;
	oss << "cheval " << 23 << 'a' << true << std::endl;
	std::cout << oss.str() << std::endl;

	while (std::cin.getline(buf, BUFFER_SIZE)) {
		try { std::cout << parser.execute(buf) << std::endl; }
		catch (BadCommand & e) {
			std::cerr << "ERR: " << e.what() << std::endl;
		}
	}

	return 0;
}
