/*
 * Utilidades.h
 *
 *  Created on: 21/09/2011
 *      Author: facundo
 */

#ifndef UTILIDADES_H_
#define UTILIDADES_H_

#include <string>
#include <sstream>

using namespace std;

class Utilidades {
public:
	Utilidades();
	virtual ~Utilidades();
	static string getFechaYHora();
	static string toString(int a);
};

#endif /* UTILIDADES_H_ */
