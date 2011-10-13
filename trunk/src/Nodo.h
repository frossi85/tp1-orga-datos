/*
 * Nodo.h
 *
 *  Created on: 02/10/2011
 *      Author: martin
 */

#ifndef NODO_H_
#define NODO_H_

#include "RegistroArbol.h"
#include <string>
#include <vector>

using namespace std;

class Nodo {
public:
	Nodo();
	virtual ~Nodo();
	unsigned int getCantidadRegistros();

	void Guardar(fstream &ofs);
	static Nodo * Leer(fstream &ifs);


	////Agregados Facundo
	int agregarRegistro( const string & clave, const long & offset);
	int agregarRegistro(RegistroArbol & registro);
	int agregarRegistroAlFinal( RegistroArbol & elem );

	void removerEnPosicion(int indice);
	void removerEnPosicion(int indice, RegistroArbol & removido );

	void clear();

	bool find( const string &clave, int &index ) const;

	bool tieneHijos() const;
	bool estaVacio() const;
	bool estaLleno() const;

	int count() const;

	enum Flags
	{
		NodoCambiado = 1
	};


	const static unsigned int maxKeys = 3;

	// Data
	int addr_;
	int less_;
	int size_; //Es cantidadRegistros
	int padre_;
	char flags_;

	const static unsigned int NodeSize = 500;
	const static unsigned int capacidadEnBytes = 500;

	//vector<RegistroArbol *> elems_; 
	vector<RegistroArbol *> elems_; //Settear el NodeSize de acuerdo a la cantidad de red
	
	void Imprimir();
};


#endif /* NODO_H_ */
