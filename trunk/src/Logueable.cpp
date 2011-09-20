/*
 * Logueable.cpp
 *
 *  Created on: 19/09/2011
 *      Author: facundo
 */

#include "Logueable.h"

Logueable::Logueable() {
	// TODO Auto-generated constructor stub
	this->className = "";//new std::string(); //ver por q no funciona el new
}

Logueable::~Logueable() {
	// TODO Auto-generated destructor stub
}

string Logueable::getClassName()
{
	return this->className;
}


