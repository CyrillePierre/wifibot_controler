
#include <cstdlib>
#include <cstdio>
#include "driver.hpp"

/**
 * @param addr : l'adresse du wifibot
 * @param port : le port de l'application de contrôle du robot
 */
Driver::Driver(char const * addr, char const * port) 
	: _leftSpeed(0), 
	  _rightSpeed(0),
	  _con(addr, port)
{
}

/**
 * Cette fonction permet d'envoyer les vitesses des moteurs
 * au robot.
 */
void Driver::sendCmd()
{
	_buf[0]  = (_leftSpeed < 0 ? 0 : DIR_BIT);
	_buf[0] |= std::abs(_leftSpeed) & SPEED_BITS;
	_buf[1]  = (_rightSpeed < 0 ? 0 : DIR_BIT);
	_buf[1] |= std::abs(_rightSpeed) & SPEED_BITS;

	_con.write(_buf, 2);

//	std::printf("%02x %02x\n", _buf[0], _buf[1]);
}

/**
 * Modification de la valeur des moteurs de gauche.
 * @param val : la nouvelle valeur à affecter.
 */
void Driver::leftSpeed(int8_t val)
{
	if      (val >  SPEED_MAX) _leftSpeed =  SPEED_MAX;
	else if (val < -SPEED_MAX) _leftSpeed = -SPEED_MAX;
	else					   _leftSpeed = val;
}

/**
 * Modification de la valeur des moteurs de droite.
 * @param val : la nouvelle valeur à affecter.
 */
void Driver::rightSpeed(int8_t val)
{
	if      (val >  SPEED_MAX) _rightSpeed =  SPEED_MAX;
	else if (val < -SPEED_MAX) _rightSpeed = -SPEED_MAX;
	else					   _rightSpeed = val;
}

