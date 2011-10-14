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
	Distrito(const Distrito &distrito);
	virtual ~Distrito();
	long getId();
	string getNombre();
	void setId(long id) {this->_id=id;}

	unsigned long int Guardar(ofstream & ofs);
	void Leer(ifstream & ifs, unsigned long int offset);
	void Imprimir();

	inline string getURLArchivoDatos();

	//Metodos interfaz Logueable
	string getClassName();
};


#endif /* DISTRITO_H_ */
