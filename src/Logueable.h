/*
 * Logueable.h
 *
 *  Created on: 19/09/2011
 *      Author: facundo
 */

#ifndef LOGUEABLE_H_
#define LOGUEABLE_H_

class Logueable {
private:
	string className;
	int id;

public:
	Logueable();
	virtual ~Logueable();
};

#endif /* LOGUEABLE_H_ */
