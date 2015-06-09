
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
				_oss << "Nouvelles vitesses : " 
					 << static_cast<int>(_driver.leftSpeed()) << " " 
					 << static_cast<int>(_driver.rightSpeed());
			}
			else throw BadCommand(
				"Syntaxe : set speed <moteurGauche> <moteurDroit>");
		}
		else throw BadCommand("Le deuxième mot clé est inconnu");
	}
	else if (first == "get") {
		iss >> second;
		if (second == "speed") {
			_oss << "Vitesses : "
				 << static_cast<int>(_driver.leftSpeed()) << " " 
				 << static_cast<int>(_driver.rightSpeed());
		}
		else throw BadCommand("Le deuxième mot clé est inconnu");
	}
	else throw BadCommand("Le premier mot clé de la commande est inconnu");

	return _oss.str();
}

