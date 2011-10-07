#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <list>
#include "RegistroIndice.h"
#include "BloqueHash.h"

using namespace std;

#ifndef HASH_EXTENSIBLE_H_
#define HASH_EXTENSIBLE_H_

class hash_extensible {
	string nombre_arch_bloques;
	string nombre_arch_bloques_libres;
	string nombre_arch_tabla;
	/*fstream *arch_bloques;
	fstream *arch_bloques_libres;
	fstream *tabla_dispersion;*/

	//recibe una posicion (no un offset) en la tabla de dispersión y devuelve
	//el offset del bloque correspondiente en el archivo de hashing
	unsigned int obtener_offset_bloque(unsigned int posicion_en_tabla);

	//Pre: se produjo un desborde en un bloque con td = tt (posicion_en_tabla es la posición
	//del archivo "tabla dispersión" en el que está el nro. del bloque que se desbordó)
	//Post: se duplica el tamaño de la tabla, se agrega un nuevo bloque, y se redispersan
	//los registros del bloque desbordado.
	void duplicar_tabla(unsigned int posicion_en_tabla);

	//Pre: se produjo un desborde en un bloque con td < tt
	//Post: se agrega un nuevo bloque, se reestructura la tabla, y se redispersan
	//los registros del bloque desbordado.
	void incrementar_tabla(unsigned int posicion_en_tabla);

	//Pre: se produjo un desborde en un bloque
	//Post: se agrego un bloque, duplicando o no la tabla, según corresponda
	void expandir_hash(unsigned int posicion_en_tabla);

	//Pre: se vació un bloque (posicion_en_tabla es la posición del archivo "tabla dispersión"
	//en el que está el nro. del bloque que quedó vacío)
	//Post: se intenta liberar el bloque vacío y truncar la tabla.
	void reducir_hash(unsigned int posicion_en_tabla);

	//Pre: se necesita crear un nuevo bloque
	//Post: se obtiene el número del nuevo bloque (pero no lo inserta) y lo elimina del
	//archivo de bloques libres
	unsigned int extraer_nro_nuevo_bloque();

	unsigned int funcion_hashing(RegistroIndice *registro);

	void persistir_vector(vector<unsigned int> *vec, string nombre_archivo);

	unsigned int obtener_tamanio_tabla();

public:
	//Post: crea e inicializa los archivos de bloques, de bloques libres y de tabla de dispersión.
	hash_extensible(string nombre_arch_bloques, string nombre_arch_bloques_libres, string nombre_arch_tabla);

	//Pre: el hash fue creado
	//Post: se almacenó el registro de índice, si no existía previamente (si ya existía lo sobreescribe)
	void guardar(RegistroIndice *registro);

	//Pre: el hash fue creado
	//Post: se eliminó el registro de índice, y su información fue devuelta por parámetro
	bool borrar(RegistroIndice *registro);

	//Pre: el hash fue creado
	//Post: la información del registro de índice se devuelve por parámetro (no modifica los datos)
	//Si el elemento no está, lanza una excepción
	RegistroIndice* buscar(RegistroIndice *registro);

	//Crea un archivo de texto plano en el que se muestra la estructura del hash
	void imprimir(const string nombre_archivo);

	//carga en memoria la tabla de dispersión como un vector de unsigned int
	//(en la primera posición se almacena la cantidad de posiciones de la tabla)
	vector<unsigned int>* cargar_tabla_dispersion();

	//carga en memoria el archivo de bloques libres como un vector de unsigned int
	//(en la primera posición se almacena la cantidad de bloques libres)
	vector<unsigned int>* cargar_archivo_bloques_libres();
};

#endif /* HASH_EXTENSIBLE_H_ */
