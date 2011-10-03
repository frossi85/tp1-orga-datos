#ifndef DISTRITO_H_
#define DISTRITO_H_

#include <iostream>
#include <fstream>
#include <string>
#include "Grabable.h"
#include "Logueable.h"
#include "Utilidades.h"
#include "VotoElectronicoExcepcion.h"

using namespace std;

class Distrito : public Grabable{//, public Logueable {
private:
	long id;
	string nombre;
	static string _dataBaseUrl;
	Distrito(long id, string nombre);
public:
	Distrito();
	Distrito(string nombre);
	string getNombre();

	void Crear(ofstream & ofs);
	void Guardar(long offsetEnArchivo);

	void Leer(ifstream & ifs);
	void Imprimir();

	//Metodo de prueba
	void setId(long id){
		this->id=id;
	}
};


#endif /* DISTRITO_H_ */
