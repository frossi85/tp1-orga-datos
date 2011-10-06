#ifndef BLOQUE_H_
#define BLOQUE_H_

using namespace std;

class Bloque{
protected:
	unsigned int tamanio;
	unsigned int espacioLibre;

public:
	virtual int getCantidadRegistros()=0;
	virtual bool Persistir(string rutaArchivo, unsigned int offset)=0;
	virtual Bloque* Leer(string rutaArchivo, unsigned int offset)=0;
};

#endif /* BLOQUE_H_ */
