#ifndef DISTRITO_H_
#define DISTRITO_H_

#include <string>
#include "Grabable.h"
#include "Logueable.h"

using namespace std;

class Distrito : public Grabable, public Logueable {
private:
	string nombre;

public:
	Distrito(string nombre);
};


#endif /* DISTRITO_H_ */
