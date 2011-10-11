#ifndef ELECCION_H_
#define ELECCION_H_

#include <string>
#include <vector>
#include "Cargo.h"
#include "Distrito.h"

using namespace std;

class Eleccion : public Grabable {
private:
	long _id;
	string _fecha;
	Cargo * _cargo;
	//TODO: Esta bien lo de abajo, para usar referencias en vectores
	vector<Distrito *> _distritos;

public:
	//Al poner el un distrito en el constructor nos aseguramos q este asociado a por lo menos
	//uno como pide el enunciado
	Eleccion();

	Eleccion(string fecha, Cargo & cargo, Distrito & primerDistrito);

	Eleccion(const Eleccion &eleccion);			// Constructor copia. agregado por martin.
	virtual ~Eleccion();

	long getId();
	string getDescripcion();
	void agregarDistrito(Distrito & distrito);
	vector<Distrito *> getDistritos();

	//Interface de Guardable
	void Guardar(ofstream & ofs);
	void Leer(ifstream & ifs);
	void Imprimir();

	inline string getURLArchivoDatos();

	//Metodo de prueba
	void setId(long id){
		this->_id=id;
	}

	//Metodos interfaz Logueable
	string getClassName();
};

#endif /* ELECCION_H_ */
