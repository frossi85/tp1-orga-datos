#ifndef BLOQUE_H_
#define BLOQUE_H_

#include <iostream>
#include <list>

using namespace std;

#define TAM_BLOQUE 512 //Kb

template <class tipoRegistro >
class Bloque{
private:
	const int tamanio;
	int tamanioDispersion;
	int espacioLibre;
	list<tipoRegistro *> registros;

public:
	Bloque(int tamanioDispersion);
	int getTamanioBloques();
	int getTamanioDispersion();
	int getCantidadRegistros();
	void setTamanioDispersion(int tamanioDispersion);
	tipoRegistro* Buscar(tipoRegistro *registro);
	bool Insertar(tipoRegistro *registro);
	bool Eliminar(tipoRegistro *registro);
	list<tipoRegistro *> VaciarBloque();
};

template <class tipoRegistro>
Bloque<tipoRegistro>::Bloque(int tamanioDispersion){
	this->tamanio = TAM_BLOQUE;
	this->tamanioDispersion = tamanioDispersion;
}

template <class tipoRegistro>
int Bloque<tipoRegistro>::getTamanioBloques(){
	return this->tamanio;
}

template <class tipoRegistro>
int Bloque<tipoRegistro>::getTamanioDispersion(){
	return this->tamanioDispersion;
}

template <class tipoRegistro>
int Bloque<tipoRegistro>::getCantidadRegistros(){
	return this->registros.size();
}

template <class tipoRegistro>
void Bloque<tipoRegistro>::setTamanioDispersion(int tamanioDispersion){
	this->tamanioDispersion = tamanioDispersion;
}

template <class tipoRegistro>
tipoRegistro* Bloque<tipoRegistro>::Buscar(tipoRegistro *registro){
	//- recorrer la lista de registros del bloque
	//- comparar la clave de "registro" con las claves de
	//los registros de la lista (sobrecarga de == para registros)
	//- si coinciden las claves, crear registro aux con clave y dato
	//correspondiente, devolver y salir
	//- devolver NULL si no se encuentra.
	return NULL;
}

template <class tipoRegistro>
bool Bloque<tipoRegistro>::Insertar(tipoRegistro *registro){
	//- revisa cuál sería el tamaño del registro ya persistido y lo
	//compara con espacioLibre para ver que si la inserción es posible
	//- si entra, lo agrega a la lista de registros del bloque
	//- si no, devuelve false sin modificar el bloque (desborde)
	//NOTA: agregar validación para el caso de que el registro ya esté en
	//el bloque
	return false;
}

template <class tipoRegistro>
bool Bloque<tipoRegistro>::Eliminar(tipoRegistro *registro){
	//- recorrer la lista de registros del bloque hasta
	//encontrar "registro".
	//- borrarlo de la lista, actualizar espacioLibre y devolver true
	//- si no estaba, devolver false
	return false;
}

template <class tipoRegistro>
list<tipoRegistro *> Bloque<tipoRegistro>::VaciarBloque(){
	//- devolver los registros del bloque
	//- actualizar el espacio libre del bloque
}

#endif /* BLOQUE_H_ */
