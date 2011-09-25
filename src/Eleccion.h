#ifndef ELECCION_H_
#define ELECCION_H_

#include <string>
#include <vector>
#include "Cargo.h"
#include "Distrito.h"

using namespace std;

class Eleccion : public Grabable, public Logueable {
private:
	string _fecha;
	Cargo& _cargo;
	//TODO: Esta bien lo de abajo, para usar referencias en vectores
	vector<Distrito *> _distritos;

public:
	//Al poner el un distrito en el constructor no aseguramos q este asociado a por lo menos
	//uno como pide el enunciado
	Eleccion(string fecha, Cargo& cargo, Distrito primerDistrito);
	virtual ~Eleccion();

	void agregarDistrito(Distrito distrito);
};

#endif /* ELECCION_H_ */
