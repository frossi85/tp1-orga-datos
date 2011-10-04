#ifndef CARGO_H_
#define CARGO_H_

#include <string>
#include <vector>

#include "Grabable.h"
#include "Logueable.h"
#include "Utilidades.h"
#include "Configuracion.h"

using namespace std;

class Cargo : public Grabable {
private:
	long id;
	string cargoPrincipal;
	vector<string> cargosSecundarios;
public:
	Cargo();
	Cargo(string cargoPrincipal);
	virtual ~Cargo();

	//Getters
	string getCargoPrincipal(); //TODO: Verificar q tiene cargo principal sino lanzar excepcion
	vector<string> getCargosSecundarios();

	//Setters
	void setCargoPrincipal(string cargoPrincipal);
	void agregarCargoSecundario(string cargo);

	//Metodos de la interfaz Guardable
	void Guardar(ofstream & ofs);
	void Leer(ifstream & ifs);
	void Imprimir();

	inline string getURLArchivoDatos();

	//Metodo de prueba
	void setId(long id){
		this->id=id;
	}

	//Metodos interfaz Logueable
	string getClassName();
};

#endif /* CARGO_H_ */
