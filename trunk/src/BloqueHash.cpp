#include "BloqueHash.h"

BloqueHash::BloqueHash(unsigned int tamanioDispersion){

	this->tamanioDispersion = tamanioDispersion;
	this->tamanio = TAM_BLOQUE_HASH;
	this->espacioLibre = this->tamanio - sizeof(this->espacioLibre) - sizeof(this->tamanioDispersion);
}

/////////////////////////

int BloqueHash::getTamanioDispersion(){
	return this->tamanioDispersion;
}

/////////////////////////

int BloqueHash::getTamanioBloques(){
	return this->tamanio;
}

int BloqueHash::getCantidadRegistros(){
	return this->registros.size();
}

/////////////////////////

void BloqueHash::setTamanioDispersion(int tamanioDispersion){
	this->tamanioDispersion = tamanioDispersion;
}

///////////////////////////

RegistroIndice* BloqueHash::Buscar(RegistroIndice *registro){
	//- recorrer la lista de registros del bloque
	//- comparar la clave de "registro" con las claves de
	//los registros de la lista (sobrecarga de == para registros)
	//- si coinciden las claves, crear registro aux con clave y dato
	//correspondiente, devolver y salir
	//- devolver NULL si no se encuentra.
	return NULL;
}

//////////////////////////

bool BloqueHash::Insertar(RegistroIndice *registro){
	//- revisa cuál sería el tamaño del registro ya persistido y lo
	//compara con espacioLibre para ver que si la inserción es posible
	//- si entra, lo agrega a la lista de registros del bloque
	//- si no, devuelve false sin modificar el bloque (desborde)
	//NOTA: agregar validación para el caso de que el registro ya esté en
	//el bloque
	return false;
}

//////////////////////////

bool BloqueHash::Eliminar(RegistroIndice *registro){
	//- recorrer la lista de registros del bloque hasta
	//encontrar "registro".
	//- borrarlo de la lista, actualizar espacioLibre y devolver true
	//- si no estaba, devolver false
	return false;
}

///////////////////////

list<RegistroIndice *> BloqueHash::VaciarBloque(){
	//- devolver los registros del bloque
	//- actualizar el espacio libre del bloque
}
