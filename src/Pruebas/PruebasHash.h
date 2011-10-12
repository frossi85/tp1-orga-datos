#ifndef PRUEBASHASH_H_
#define PRUEBASHASH_H_

#include "../hash_extensible.h"

/* Una función para convertir enteros a strings.
 * La uso para prbar el hash.
 */
string itos(int number)
{
    if (number == 0)
        return "0";
    string temp="";
    string returnvalue="";
    while (number>0)
    {
        temp+=number%10+48;
        number/=10;
    }
    for (int i=0;i<temp.length();i++)
        returnvalue+=temp[temp.length()-i-1];
    return returnvalue;
}

class PruebasHash{
public:
	static bool GuardarYBuscar(unsigned int cantidadRegistros);
	static bool GuardarYBorrar(unsigned int cantidadRegistros);
	static bool GuardarBorrarYVolverAGuardar(unsigned int cantidadRegistros);
};

/////////////////////

bool PruebasHash::GuardarYBuscar(unsigned int cantidadRegistros){

	hash_extensible hash("bloquesGuardarBuscar", "blibresGuardarBuscar", "tablaGuardarBuscar");

	string clave;
	RegistroIndice *registro;

	for(int i = 0; i <= cantidadRegistros; i++){
	    clave = itos( i );
	    registro = new RegistroIndice(clave, i);
	    hash.guardar(registro);
	}

	//busca lo que guardó
	for(int i = 0; i <= cantidadRegistros; i++){
	    clave = itos( i );
	    registro = new RegistroIndice(clave, i);
	    if(hash.buscar(registro) == NULL) return false;
	}

	return true;
}

bool PruebasHash::GuardarYBorrar(unsigned int cantidadRegistros){

	hash_extensible hash("bloquesGuardarBorrar", "blibresGuardarBorrar", "tablaGuardarBorrar");

	string clave;
	RegistroIndice *registro;

	for(int i = 0; i <= cantidadRegistros; i++){
	    clave = itos( i );
	    registro = new RegistroIndice(clave, i);
	    hash.guardar(registro);
	}

	//borra lo que guardó
	for(int i = 0; i <= cantidadRegistros; i++){
	    clave = itos( i );
	    registro = new RegistroIndice(clave, i);
	    if(!hash.borrar(registro)) return false;
	}

	return true;
}

bool PruebasHash::GuardarBorrarYVolverAGuardar(unsigned int cantidadRegistros){

	hash_extensible hash("bloquesGuardarBorrar", "blibresGuardarBorrar", "tablaGuardarBorrar");

	string clave;
	RegistroIndice *registro;

	for(int i = 0; i <= cantidadRegistros; i++){
	    clave = itos( i );
	    registro = new RegistroIndice(clave, i);
	    hash.guardar(registro);
	}

	//borra lo que guardó
	for(int i = 0; i <= cantidadRegistros; i++){
	    clave = itos( i );
	    registro = new RegistroIndice(clave, i);
	    if(!hash.borrar(registro)) return false;
	}

	//vuelve a guardar
	for(int i = 0; i <= cantidadRegistros; i++){
		clave = itos( i );
		registro = new RegistroIndice(clave, i);
		hash.guardar(registro);
	}

	return true;
}
#endif /* PRUEBASHASH_H_ */
