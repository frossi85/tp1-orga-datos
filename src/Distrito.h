#ifndef DISTRITO_H_
#define DISTRITO_H_

#include <iostream>
#include <fstream>
#include <string>
#include "Grabable.h"
#include "Logueable.h"
#include "Utilidades.h"
#include "VotoElectronicoExcepcion.h"
#include "Configuracion.h"

using namespace std;

class Distrito : public Grabable {
private:
	long _id;
	string _nombre;
public:
	Distrito();
	Distrito(string nombre);
	Distrito(const Distrito &distrito); 		// Agregado por martin
	virtual ~Distrito();
	long getId();
	string getNombre();

	unsigned long int Guardar(ofstream & ofs);
	void Leer(ifstream & ifs, unsigned long int offset);
	void Imprimir();

	inline string getURLArchivoDatos();

	//Metodo de prueba
	void setId(long id){
		this->_id=id;
	}

	//Metodos interfaz Logueable
	string getClassName();
};


#endif /* DISTRITO_H_ */
