#ifndef CARGO_H_
#define CARGO_H_

#include <string>
#include <vector>

#include "Grabable.h"
#include "Logueable.h"

using namespace std;

class Cargo{
private:
	string cargoPrincipal;
	vector<string> *cargosSecundarios;
public:
	Cargo(string cargoPrincipal);
};

#endif /* CARGO_H_ */
