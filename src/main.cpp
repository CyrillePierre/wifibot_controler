
#include <iostream>
#include <string>
#include "driver.hpp"
#include "cmdparser.hpp"
#include "server.hpp"

#include <sstream>

#define BUFFER_SIZE	128

int main()
{
	char buf[BUFFER_SIZE];
	Driver driver("localhost");
	CmdParser parser(driver);
	net::Server server(1337);

	// Écoute des commandes envoyé par TCP
	server.connect();
	server.asyncAcceptLoop([&parser] (net::Client const & client) {
		char buf[BUFFER_SIZE];
		std::string result;

		while (client.read(buf, BUFFER_SIZE)) {
			try { result = parser.execute(buf) + "\n"; }
			catch (BadCommand & e) {
				result = (std::string) "ERR: " + e.what() + "\n";
			}
			client.write(result.c_str(), result.size());
		}
	});

	// Écoute des commandes sur l'entrée standard
	while (std::cin.getline(buf, BUFFER_SIZE)) {
		try { std::cout << parser.execute(buf) << std::endl; }
		catch (BadCommand & e) {
			std::cerr << "ERR: " << e.what() << std::endl;
		}
	}

	// On stoppe le moteur avant de quitter le programme
	driver.leftSpeed(0);
	driver.rightSpeed(0);
	driver.sendCmd();

	return 0;
}
