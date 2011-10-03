#include "BloqueHash.h"

BloqueHash::BloqueHash(unsigned int tamanioDispersion){
	//crea un bloque sin registros
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

	fstream archBloques(rutaArchivo.c_str(), ios::out | ios::binary);
	archBloques.seekp(offset);
	archBloques.write((char*)&(this->tamanioDispersion), sizeof(this->tamanioDispersion));
	archBloques.write((char*)&(this->espacioLibre), sizeof(this->espacioLibre));

	RegistroIndice *registro = NULL;
	list<RegistroIndice *>::iterator it;
	for (it = this->registros.begin(); it != this->registros.end(); it++){
		registro = *it;
		registro->Persistir(&archBloques);
	}

	archBloques.close();
	return true;
}

////////////////////

Bloque* BloqueHash::Leer(string rutaArchivo, unsigned int offset){

	//levanta los datos a memoria
	BloqueHash *BloqueAux = new BloqueHash(0);

	fstream archBloques(rutaArchivo.c_str(), ios::in | ios::binary);
	archBloques.seekg(offset);
	archBloques.read((char*)&(BloqueAux->tamanioDispersion), sizeof(BloqueAux->tamanioDispersion));
	archBloques.read((char*)&(BloqueAux->espacioLibre), sizeof(BloqueAux->espacioLibre));

	//mientras no llegue al final del chorizo de bytes, lee los registros
	RegistroIndice *registro = NULL;
	while(archBloques.tellg() != BloqueAux->tamanio - BloqueAux->espacioLibre){
		registro = registro->Leer(&archBloques);
		BloqueAux->registros.push_back(registro);
	}
	archBloques.close();
	return BloqueAux;

	//Si no pudo leer, devuelve NULL
	return NULL;
}

///////////////////////

list<RegistroIndice *>* BloqueHash::VaciarBloque(){

	//- devolver los registros del bloque y vaciar
	// la lista original
	//- actualizar el espacio libre del bloque (siempre en memoria)

	list<RegistroIndice *> *aux = new list<RegistroIndice *>;
	RegistroIndice *registroEnLista = NULL;
	list<RegistroIndice *>::iterator it;

	for (it = this->registros.begin(); it != this->registros.end(); it++){
		registroEnLista = *it;
		aux->push_back(registroEnLista);
		this->espacioLibre += registroEnLista->getTamanioEnDisco();
	}
	this->registros.clear();

	return aux;
}
