#ifndef PRUEBASREGISTROINDICE_H_
#define PRUEBASREGISTROINDICE_H_

#include <fstream>
#include "../RegistroIndice.h"

class PruebasRegistroIndice{
public:
	static bool Guardar();
};

bool PruebasRegistroIndice::Guardar(){

	//crea 3 registros
	string clave1 = "156";
	RegistroIndice registro1(clave1, 98765);

	string clave2 = "26";
	RegistroIndice registro2(clave2, 3456);

	string clave3 = "8";
	RegistroIndice registro3(clave3, 128);

	//guarda
	fstream archivo("archPruebaRegistroIndice", ios_base::out | ios_base::in | ios::binary);
	archivo.seekp(0);
	registro1.Persistir(&archivo);
	registro2.Persistir(&archivo);
	archivo.close();

	archivo.open ("archPruebaRegistroIndice", ios_base::out | ios_base::in | ios::binary);
	archivo.seekp(200);
	registro3.Persistir(&archivo);
	archivo.close();

	//recupera
	fstream arch("archPruebaRegistroIndice", ios_base::in |ios_base::binary);
	arch.seekg(0);
	RegistroIndice *aux1 = aux1->Leer(&arch);
	RegistroIndice *aux2 = aux2->Leer(&arch);
	arch.seekg(200);
	RegistroIndice *aux3 = aux3->Leer(&arch);
	arch.close();

	if( (registro1.getClave() == aux1->getClave()) && (registro1.getOffset() == aux1->getOffset()) )
		if( (registro2.getClave() == aux2->getClave()) && (registro2.getOffset() == aux2->getOffset()) )
			if( (registro3.getClave() == aux3->getClave()) && (registro3.getOffset() == aux3->getOffset()) )
				return true;

	return false;
}


#endif /* PRUEBASREGISTROINDICE_H_ */
