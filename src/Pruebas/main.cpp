#include "PruebasRegistroIndice.h"
#include "PruebasHash.h"

int main(){

	//Pruebas de RegistroIndice:
	if(!PruebasRegistroIndice::Guardar()){
		cout << "REGISTROINDICE: fallo al persistir y/o leer" << endl;
	}else{
		cout << "REGISTROINDICE: persistir/leer OK" << endl;
	}

	//Pruebas del hash:

	if(!PruebasHash::GuardarYBuscar(50000)){
		cout << "HASH: fallo al guardar y/o buscar" << endl;
	}else{
		cout << "HASH: guardar/buscar OK" << endl;
	}

	if(!PruebasHash::GuardarYBorrar(50000)){
		cout << "HASH: fallo en borrar" << endl;
	}else{
		cout << "HASH: borrar OK" << endl;
	}

	if(!PruebasHash::GuardarBorrarYVolverAGuardar(20000)){
		cout << "HASH: fallo tras borrar y volver a guardar" << endl;
	}else{
		cout << "HASH: borrar y volver a guardar OK" << endl;
	}
}
