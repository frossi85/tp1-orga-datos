#ifndef BLOQUEHASH_H_
#define BLOQUEHASH_H_

#include <iostream>
#include <list>
#include "Bloque.h"
#include "RegistroIndice.h"

#define TAM_BLOQUE_HASH 512 //Kb

using namespace std;

class BloqueHash: public Bloque{
private:
	unsigned int tamanioDispersion;
	list<RegistroIndice *> registros;

public:
	BloqueHash(unsigned int tamanioDispersion);
	int getTamanioBloques();
	int getTamanioDispersion();
	int getCantidadRegistros();
	void setTamanioDispersion(int tamanioDispersion);
	RegistroIndice* Buscar(RegistroIndice *registro);
	bool Insertar(RegistroIndice *registro);
	bool Eliminar(RegistroIndice *registro);
	list<RegistroIndice *> VaciarBloque();
};

#endif /* BLOQUEHASH_H_ */
