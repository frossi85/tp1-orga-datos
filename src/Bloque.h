#ifndef BLOQUE_H_
#define BLOQUE_H_

using namespace std;

class Bloque{
protected:
	unsigned int tamanio;
	unsigned int espacioLibre;

public:
	virtual int getTamanioBloques()=0;
	virtual int getCantidadRegistros()=0;
	virtual ~Bloque(){};
};

#endif /* BLOQUE_H_ */
