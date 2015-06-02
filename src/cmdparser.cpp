
#include <iostream>
#include "cmdparser.hpp"

/**
 * Cette méthode permet d'interpréter une commande écrit dans un langage 
 * compréhensible par un humain et d'exécuter l'action correspondante chez
 * le driver.
 * @param cmd : le buffer contenant le texte de la commande
 */
std::string CmdParser::execute(std::string && cmd)
{
	std::istringstream iss(std::forward<std::string>(cmd));
	std::string first;
	std::string second;

	// On vide le buffer de sortie
	_oss.str("");

	// Début du parsage
	iss >> first;
	if (first == "set") {
		iss >> second;
		if (second == "speed") {
			int left, right;
			if (iss >> left && iss >> right) {
				_driver.leftSpeed(left);
				_driver.rightSpeed(right);
				_driver.sendCmd();
				_oss << "done";
			}
			else throw BadCommand(
				"Syntaxe : set speed <moteurGauche> <moteurDroit>");
		}
		else throw BadCommand("Le deuxième mot clé est inconnu");
	}
	else if (first == "get") {
		throw BadCommand("Commande non implémentée");
	}
	else throw BadCommand("Le premier mot clé de la commande est inconnu");

	return _oss.str();
}

