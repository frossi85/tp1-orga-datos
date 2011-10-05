#ifndef BLOQUEHASH_H_
#define BLOQUEHASH_H_

#include <iostream>
#include <fstream>
#include <list>
#include "Bloque.h"
#include "RegistroIndice.h"

#define TAM_BLOQUE_HASH 512 //Bytes

using namespace std;

class BloqueHash: public Bloque{
private:
	unsigned int tamanioDispersion;
	list<RegistroIndice *> registros;

public:
	BloqueHash(unsigned int tamanioDispersion);
	~BloqueHash();
	int getTamanioBloques();
	int getTamanioDispersion();
	int getCantidadRegistros();
	void setTamanioDispersion(int tamanioDispersion);
	RegistroIndice* Buscar(RegistroIndice *registro);
	bool Insertar(RegistroIndice *registro);
	bool Eliminar(RegistroIndice *registro);
	list<RegistroIndice *>* VaciarBloque();
	bool Persistir(string rutaArchivo, unsigned int offset);
	Bloque* Leer(string rutaArchivo, unsigned int offset);
	void Imprimir(fstream *archImpresion);
};

#endif /* BLOQUEHASH_H_ */
