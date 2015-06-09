
#include <cstdio>
#include <iostream>
#include <string>
#include <thread>
#include <sstream>

#include "driver.hpp"
#include "cmdparser.hpp"
#include "server.hpp"


std::size_t const BUFFER_SIZE = 128;
int const         CMD_PERIOD  = 50;		// en millisecondes


int main(int argc, char **argv)
{
	int port;

	if (argc != 3 || !sscanf(argv[2], "%d", &port)) {
		std::cerr << "Syntaxe :\n\n    \e[01m" << argv[0]
		          << " <adresseRobot> <portRasPi>\e[00m\n\n"
				  << "<adresseRobot> : adresse IP du robot "
				  << "(ex: 192.168.0.112)\n"
				  << "<portRasPi>    : port TCP d'accès à l'application "
				  << "(ex: 1337)" << std::endl;
		return 1;
	}

	Driver driver(argv[1]);
	CmdParser parser(driver);

	// Écoute des commandes envoyé par TCP
	net::Server server(port);
	server.connect();
	server.asyncAcceptLoop([&parser] (net::Client const & client) {
		char buf[BUFFER_SIZE];
		std::string result;

		while (client.read(buf, BUFFER_SIZE)) {
			try { result = parser.execute(buf) + "\n"; }
			catch (BadCommand & e) {
				result = std::string("ERR: ") + e.what() + "\n";
			}
			client.write(result.c_str(), result.size());
		}
	});

	// Thread d'envoi des commandes au robot
	bool isRunning = true;
	std::thread thread([&driver, &isRunning] () {
		while (isRunning) {
			usleep(CMD_PERIOD * 1000);
			driver.sendCmd();
		}
	});

	// Écoute des commandes sur l'entrée standard
	char buf[BUFFER_SIZE];
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

	// On attend la fin du thread d'envoi des commandes
	isRunning = false;
	thread.join();

	return 0;
}
