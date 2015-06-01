
#ifndef CMDPARSER_HPP
#define CMDPARSER_HPP

#include <sstream>
#include <exception>
#include "driver.hpp"

/**
 * Cette classe permet d'interpréter des commandes et des réponses entre le
 * driver du robot et l'interface texte.
 * @author Cyrille Pierre
 */
class CmdParser
{
	Driver const & _driver;

public:
	/** @param driver : le driver du robot qui recevra les commandes */
	CmdParser(Driver const & driver) : _driver(driver) {}

	/** @brief Exécution d'une commande pour le robot */
	std::string && execute(std::string &&);
};


/**
 * Cette classe correspond à une exception qui peut survenir lors du parsage
 * d'une commande.
 * @author Cyrille Pierre
 */
class BadCommand : public std::exception
{
	char const * _msg;

public:
	BadCommand(char const * msg) : _msg(msg) {}
	inline virtual char const * what() const noexcept { return _msg; }
};

#endif
