/*
 * Grabable.cpp
 *
 *  Created on: 19/09/2011
 *      Author: facundo
 */

#include "Grabable.h"

Grabable::Grabable() {
	// TODO Auto-generated constructor stub

}

Grabable::~Grabable() {
	// TODO Auto-generated destructor stub
}

bool Grabable::operator ==(const Grabable &obj) const
{
    return (this->_stringId == obj._stringId);
}
