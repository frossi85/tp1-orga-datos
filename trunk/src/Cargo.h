#ifndef CARGO_H_
#define CARGO_H_

#include <string>
#include <vector>

using namespace std;

class Cargo : public Grabable, public Logueable {
private:
	string cargoPrincipal;
	vector<string> *cargos;
public:
	Cargo(string cargoPrincipal);
};

#endif /* CARGO_H_ */
