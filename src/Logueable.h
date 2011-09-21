/*
 * Logueable.h
 *
 *  Created on: 19/09/2011
 *      Author: facundo
 */

#ifndef LOGUEABLE_H_
#define LOGUEABLE_H_
#include <string.h>

#include <string>

using namespace std;

class Logueable {
private:
	std::string className;
	int id;
	std::string description;

public:
	Logueable();
	virtual ~Logueable();
	string getClassName();

};

#endif /* LOGUEABLE_H_ */
