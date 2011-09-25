#ifndef CARGO_H_
#define CARGO_H_

#include <string>
#include <vector>

#include "Grabable.h"
#include "Logueable.h"

using namespace std;

class Cargo : public Grabable, public Logueable {
private:
	string cargoPrincipal;
	vector<string> cargosSecundarios;
public:
	Cargo(string cargoPrincipal);
	virtual ~Cargo();

	//Getters
	string getCargoPrincipal();
	vector<string> getCargosSecundarios();

	//Setters
	void agregarCargoSecundario(string cargo);
};

#endif /* CARGO_H_ */
