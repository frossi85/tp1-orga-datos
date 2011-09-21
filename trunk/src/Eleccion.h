#ifndef ELECCION_H_
#define ELECCION_H_

#include <string>
#include <vector>
#include "Cargo.h"
#include "Distrito.h"

using namespace std;

class Eleccion{
private:
	string fecha;
	Cargo *cargo;
	vector<Distrito> *distritos;

public:
	Eleccion();
};

#endif /* ELECCION_H_ */
