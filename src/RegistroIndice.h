#ifndef REGISTROINDICE_H_
#define REGISTROINDICE_H_

#include <iostream>
#include <fstream>

using namespace std;

class RegistroIndice{
private:
	string clave;
	unsigned int offset;

public:
	RegistroIndice(string clave, unsigned int offset);
	string getClave();
	unsigned int getOffset();
	void setOffset(unsigned int offset);
	//Devuelve el tamaño que tenfría el registro
	//una vez persistido
	unsigned int getTamanioEnDisco();
	void Persistir(fstream *archivo);
	RegistroIndice* Leer(fstream *archivo);
	void Imprimir(fstream *archImpresion);
};

#endif /* REGISTROINDICE_H_ */
