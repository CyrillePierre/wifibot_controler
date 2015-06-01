
#include "cmdparser.hpp"

/**
 * Cette méthode permet d'interpréter une commande écrit dans un langage 
 * compréhensible par un humain et d'exécuter l'action correspondante chez
 * le driver.
 * @param cmd : le buffer contenant le texte de la commande
 */
std::string && CmdParser::execute(std::string && cmd)
{
	std::istringstream iss(std::forward<std::string>(cmd));
	std::ostringstream oss;

	std::string first;
	iss >> first;
	if (first == "set") {
	}
	else if (first == "get") {
	}
	else throw BadCommand("Le premier mot clé de la commande est inconnu");

	return std::forward<std::string>(oss.str());
}

