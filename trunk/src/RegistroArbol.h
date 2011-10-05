/*
 * RegistroArbol.h
 *
 *  Created on: 02/10/2011
 *      Author: martin
 */

#ifndef REGISTROARBOL_H_
#define REGISTROARBOL_H_

class RegistroArbol{
public:
	RegistroArbol(string clave, unsigned int offset);
	virtual ~RegistroArbol();
	string getClave();
	unsigned int getOffset();
	unsigned int getTamanioEnDisco();
	void Persistir(fstream *archivo);
	RegistroIndice* Leer(fstream *archivo);


private:
	string clave;
	unsigned int offset;
};


#endif /* REGISTROARBOL_H_ */
