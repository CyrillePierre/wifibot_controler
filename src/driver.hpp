
#pragma once

#include <stdint.h>
#include "connection.hpp"

/**
 * Cette classe représente le driver du wifibot. Elle contient des méthodes
 * permettant de déplacer le wifibot ainsi que de traiter les messages du
 * robot.
 * @author Cyrille PIERRE
 */
struct Driver
{
	static uint8_t const DIR_BIT    = 0x40;
	static uint8_t const CTRL_BIT   = 0x80;
	static uint8_t const SPEED_BITS = 0x3f;
	static int8_t  const SPEED_MAX  = SPEED_BITS;
	
private:
	uint8_t    _buf[2];
	int8_t     _leftSpeed;
	int8_t     _rightSpeed;
	Connection _con;

public:
	/** @brief Constructeur */
	Driver(char const *, char const * = "15000");

	/** @brief Envoi de la commande au robot */
	void sendCmd();

	// setteurs
	void leftSpeed(int8_t);
	void rightSpeed(int8_t);

	// Getteurs
	inline int8_t leftSpeed()  const { return _leftSpeed;  }
	inline int8_t rightSpeed() const { return _rightSpeed; }
};
