/*
 * Informe.h
 *
 *  Created on: 19/09/2011
 *      Author: facundo
 */

#ifndef INFORME_H_
#define INFORME_H_

class Informe {
public:
	Informe(Eleccion& eleccion);
	Informe(Distrito& distrito);


	virtual ~Informe();
};

#endif /* INFORME_H_ */
