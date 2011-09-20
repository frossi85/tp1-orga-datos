/*
 * Candidato.h
 *
 *  Created on: 19/09/2011
 *      Author: facundo
 */

#ifndef CANDIDATO_H_
#define CANDIDATO_H_

class Candidato : public Votante, public Grabable, public Logueable  {
private:
	Lista listaPropia;
	Cargo cargoAPresentarse;
public:
	Candidato();
	virtual ~Candidato();
};

#endif /* CANDIDATO_H_ */
