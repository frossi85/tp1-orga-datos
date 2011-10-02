#include "BloqueHash.h"

BloqueHash::BloqueHash(unsigned int tamanioDispersion){

	this->tamanioDispersion = tamanioDispersion;
	this->tamanio = TAM_BLOQUE_HASH;
	this->espacioLibre = this->tamanio - sizeof(this->espacioLibre) - sizeof(this->tamanioDispersion);
}

///////////////////////

BloqueHash::~BloqueHash(){
	while(!this->registros.empty()){
		this->registros.pop_back();
	}
}
/////////////////////////

int BloqueHash::getTamanioDispersion(){
	return this->tamanioDispersion;
}

/////////////////////////

int BloqueHash::getTamanioBloques(){
	return this->tamanio;
}

//////////////////////////

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
	RegistroIndice *registroEnLista = NULL;
	list<RegistroIndice *>::iterator it;
	for (it = this->registros.begin(); it != this->registros.end(); it++){
		registroEnLista = *it;

		//- si coinciden las claves, crear registro aux con clave y dato
		//correspondiente, devolver y salir
		if(registroEnLista->getClave() == registro->getClave()){
			return registroEnLista;
		}
	}
	//- devolver NULL si no se encuentra.
	return NULL;
}

//////////////////////////

bool BloqueHash::Insertar(RegistroIndice *registro){
	/* Validación: si el registro ya estaba en la lista, lo sobreescribe
	 * (lo elimina, actualizando espacioLibre, para luego insertar el nuevo)
	 */
	this->Eliminar(registro);
	/* Fin de la validación
	 */

	//- revisa cuál sería el tamaño del registro ya persistido y lo
	//compara con espacioLibre para ver que si la inserción es posible
	if(registro->getTamanioEnDisco() <= this->espacioLibre){
	//- si entra, lo agrega a la lista de registros del bloque, actualiza el espacio libre y devuelve true
	//- si no, devuelve false sin modificar el bloque (desborde)
		this->registros.push_back(registro);
		this->espacioLibre -= registro->getTamanioEnDisco();
		return true;
	}
	return false;
}

//////////////////////////

bool BloqueHash::Eliminar(RegistroIndice *registro){
	//- recorrer la lista de registros del bloque hasta
	//encontrar "registro".
	//- borrarlo de la lista, actualizar espacioLibre y devolver true
	//- si no estaba, devolver false

	RegistroIndice *registroEnLista = NULL;
	list<RegistroIndice *>::iterator it;
	for (it = this->registros.begin(); it != this->registros.end(); it++){
		registroEnLista = *it;
		if(registroEnLista->getClave() == registro->getClave()){
			this->espacioLibre += registroEnLista->getTamanioEnDisco();
			this->registros.erase(it);
			return true;
		}
	}
	return false;
}

////////////////////////

bool BloqueHash::Persistir(string rutaArchivo, unsigned int offset){
	//graba el bloque en el archivo.
	//Si no pudo grabar, devuelve false
	return false;
}

////////////////////

Bloque* BloqueHash::Leer(string rutaArchivo, unsigned int offset){
	//levanta el bloque a memoria.
	//Si no pudo leer, devuelve NULL
	return NULL;
}

///////////////////////

list<RegistroIndice *> BloqueHash::VaciarBloque(){
	//- devolver los registros del bloque
	//- actualizar el espacio libre del bloque
}

