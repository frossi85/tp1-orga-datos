#include "hash_extensible.h"
#include <cstdlib>


hash_extensible::hash_extensible(string nombre_arch_bloques, string nombre_arch_bloques_libres, string nombre_arch_tabla) {

	this->nombre_arch_bloques = nombre_arch_bloques;
	this->nombre_arch_bloques_libres = nombre_arch_bloques_libres;
	this->nombre_arch_tabla = nombre_arch_tabla;

	this->arch_bloques = new fstream();
	this->arch_bloques_libres = new fstream();
	this->tabla_dispersion = new fstream();

	//escribe el tamaño y la primera dirección de la tabla de dispersión
	unsigned int tamanio_tabla = 1;
	tabla_dispersion->open(this->nombre_arch_tabla.c_str(), ios::binary | ios::out);
	tabla_dispersion->seekp(0);
	tabla_dispersion->write((char *)&tamanio_tabla, sizeof(unsigned int));
	unsigned int direccion = 0;
	tabla_dispersion->write((char *)&direccion, sizeof(unsigned int));
	tabla_dispersion->close();

	//escribe el primer bloque en el hash
	unsigned int tam = obtener_tamanio_tabla();
	BloqueHash *primer_bloque = new BloqueHash(tam);
	primer_bloque->Persistir(this->nombre_arch_bloques.c_str(), 0);
	delete primer_bloque;

	//inicializa el archivo de bloques libres con cantidad = 0
	arch_bloques_libres->open(this->nombre_arch_bloques_libres.c_str(), ios::binary | ios::out);
	unsigned int cantidad = 0;
	arch_bloques_libres->seekp(0);
	arch_bloques_libres->write((char *)&cantidad, sizeof(unsigned int));
	arch_bloques_libres->close();
}

////////////////////////////

unsigned int hash_extensible::funcion_hashing(RegistroIndice *registro){

	unsigned int suma = 0, i = 0;
	char caracter = registro->getClave()[0];
	while (caracter != '\0'){
		suma += caracter + '0';
		i++;
		caracter = registro->getClave()[i];
	}
	return suma%obtener_tamanio_tabla() + 1;
	/* suma uno para no tener en cuenta la primera posición de la tabla,
	 * donde se guarda la longitud de la misma */
}

///////////////////////////

unsigned int hash_extensible::obtener_offset_bloque(unsigned int posicion_en_tabla_dispersion){

	tabla_dispersion->open(this->nombre_arch_tabla.c_str(), ios::binary | ios::in);
	tabla_dispersion->seekg(posicion_en_tabla_dispersion*sizeof(unsigned int));
	unsigned int nro_de_bloque;
	tabla_dispersion->read((char *)&nro_de_bloque, sizeof(unsigned int));
	tabla_dispersion->close();

	int tamanio_bloque = BloqueHash::getTamanioBloques();
	return nro_de_bloque*tamanio_bloque;
}

////////////////////////////

void hash_extensible::persistir_vector(vector<unsigned int> *vec, fstream *archivo, string nombre_archivo){

	archivo->open(nombre_archivo.c_str(), ios::binary | ios::out);

	archivo->seekp(0);
	for(unsigned int i = 0; i <= (*vec)[0]; i++)
		archivo->write((char *)&(*vec)[i], sizeof(unsigned int));

	archivo->close();
}

////////////////////////////

unsigned int hash_extensible::extraer_nro_nuevo_bloque(){
	//- toma el menor numero de bloque del archivo de bloques libres y lo elimina del archivo
	//- si no hay bloques libres, devuelve el número de bloque en uso más alto + 1
	unsigned int num_bloque;
	unsigned int posicion_num_bloque;
	vector<unsigned int> *lista_bloques = cargar_archivo_bloques_libres();

	if ((*lista_bloques)[0] != 0){
		num_bloque = (*lista_bloques)[1];
		posicion_num_bloque = 1;
		for(unsigned int i = 2; i < lista_bloques->size(); i++){
			if ((*lista_bloques)[i] < num_bloque){
				num_bloque = (*lista_bloques)[i];
				posicion_num_bloque = i;
			}
		}
		(*lista_bloques)[posicion_num_bloque] = lista_bloques->back();
		lista_bloques->pop_back();
		persistir_vector(lista_bloques, arch_bloques_libres, this->nombre_arch_bloques_libres.c_str());
		delete lista_bloques;
		return num_bloque;
	}
	delete lista_bloques;

	vector<unsigned int> *tabla_disp = cargar_tabla_dispersion();
	int max = -1;
	for(unsigned int i = 1; i <= (*tabla_disp)[0]; i++)
		if((int)(*tabla_disp)[i] > max) max = (*tabla_disp)[i];

	return max + 1;
}

/////////////////////////////

vector<unsigned int>* hash_extensible::cargar_archivo_bloques_libres(){

	arch_bloques_libres->open(this->nombre_arch_bloques_libres.c_str(), ios::binary | ios::in);
	arch_bloques_libres->seekg(0);
	vector<unsigned int> *vector_aux = new vector<unsigned int>;
	unsigned int aux;
	arch_bloques_libres->read((char *)&aux, sizeof(unsigned int));
	vector_aux->reserve(sizeof(unsigned int)*(aux + 1));
	(*vector_aux)[0] = aux;

	for(unsigned int i = 1; i <= (*vector_aux)[0]; i++){
		arch_bloques_libres->read((char *)&aux, sizeof(unsigned int));
		(*vector_aux)[i] = aux;
	}

	arch_bloques_libres->close();
	return vector_aux;
}

////////////////////////////

vector<unsigned int>* hash_extensible::cargar_tabla_dispersion(){

	tabla_dispersion->open(this->nombre_arch_tabla.c_str(), ios::binary | ios::in);
	tabla_dispersion->seekg(0);
	vector<unsigned int> *vector_aux = new vector<unsigned int>;
	unsigned int aux;
	tabla_dispersion->read((char *)&aux, sizeof(unsigned int));
	vector_aux->reserve(sizeof(unsigned int)*(aux + 1));
	(*vector_aux)[0] = aux;

	for(unsigned int i = 1; i <= (*vector_aux)[0]; i++){
		tabla_dispersion->read((char *)&aux, sizeof(unsigned int));
		(*vector_aux)[i] = aux;
	}

	tabla_dispersion->close();
	return vector_aux;
}

///////////////////////

unsigned int hash_extensible::obtener_tamanio_tabla(){

	tabla_dispersion->open(this->nombre_arch_tabla.c_str(), ios::binary | ios::in);
	tabla_dispersion->seekg(0);
	unsigned int aux;
	tabla_dispersion->read((char *)&aux, sizeof(unsigned int));
	tabla_dispersion->close();
	return aux;
}

//////////////////////

RegistroIndice* hash_extensible::buscar(RegistroIndice *registro){
	//obtiene la posicion del bloque donde está el registro
	unsigned int offset_bloque = obtener_offset_bloque(funcion_hashing(registro));

	//lee el bloque a memoria para buscar el registro.
	//Si no está lanza excepción, si está lo devuelve por parámetro
	BloqueHash *bloque_aux = new BloqueHash(0);
	bloque_aux = (BloqueHash*)bloque_aux->Leer(this->nombre_arch_bloques.c_str(), offset_bloque);

	RegistroIndice *reg_aux;
	reg_aux = bloque_aux->Buscar(registro);
	delete bloque_aux;
	return reg_aux;
}

////////////////////////

void hash_extensible::duplicar_tabla(unsigned int posicion_en_tabla){

	vector<unsigned int> *tabla_en_memoria = cargar_tabla_dispersion();
	unsigned int tamanio_tabla = (*tabla_en_memoria)[0];
	tabla_en_memoria->reserve(tamanio_tabla*2 + 1);

	//duplica la tabla en memoria
	for(unsigned int i = 1; i <= tamanio_tabla; i++)
		(*tabla_en_memoria)[i + tamanio_tabla] = (*tabla_en_memoria)[i];

	//lee el nro. de bloque desbordado, y en la primera mitad de la
	//tabla lo reemplaza por el nuevo número de bloque
	unsigned int nro_bloque_desbordado = (*tabla_en_memoria)[posicion_en_tabla];
	unsigned int num_nuevo_bloque = extraer_nro_nuevo_bloque();
	(*tabla_en_memoria)[posicion_en_tabla] = num_nuevo_bloque;

	//duplica el tamaño de la tabla y guarda la tabla duplicada en disco
	(*tabla_en_memoria)[0] *= 2;
	persistir_vector(tabla_en_memoria, tabla_dispersion, this->nombre_arch_tabla.c_str());

	//en el archivo de bloques inserta uno nuevo, y al nuevo bloque y al
	//desbordado les asigna tamanio dispersion = tamanio tabla
	BloqueHash *nuevo_bloque = new BloqueHash(obtener_tamanio_tabla());
	nuevo_bloque->Persistir(this->nombre_arch_bloques.c_str(), num_nuevo_bloque*BloqueHash::getTamanioBloques());
	delete nuevo_bloque;

	unsigned int offset_bloque = nro_bloque_desbordado * BloqueHash::getTamanioBloques();
	BloqueHash *bloque_desbordado = new BloqueHash(0);
	bloque_desbordado = (BloqueHash*) bloque_desbordado->Leer(this->nombre_arch_bloques.c_str(), offset_bloque);
	bloque_desbordado->setTamanioDispersion(obtener_tamanio_tabla());
	// Borra todos los registros del bloque y los guarda en memoria
	list<RegistroIndice *> *registros_a_redispersar = bloque_desbordado->VaciarBloque();

	//vuelve a guardar el bloque, ahora sin registros y con su nuevo tamaño de dispersión:
	bloque_desbordado->Persistir(this->nombre_arch_bloques.c_str(), offset_bloque);
	delete bloque_desbordado;

	//redispersa los registros del bloque desbordado
	RegistroIndice *registroEnLista = NULL;
	list<RegistroIndice *>::iterator it;
	for (it = registros_a_redispersar->begin(); it != registros_a_redispersar->end(); it++){
		registroEnLista = *it;
		guardar(registroEnLista);
	}
}

/////////////////////////

void hash_extensible::incrementar_tabla(unsigned int posicion_en_tabla){
	//lee y duplica el tamaño de dispersión del bloque desbordado
	unsigned int offset_bloque = obtener_offset_bloque(posicion_en_tabla);
	BloqueHash *bloque_desbordado = new BloqueHash(0);
	bloque_desbordado = (BloqueHash*)bloque_desbordado->Leer(this->nombre_arch_bloques.c_str(), offset_bloque);
	unsigned int nuevo_tamanio_dispersion = bloque_desbordado->getTamanioDispersion()*2;
	bloque_desbordado->setTamanioDispersion(nuevo_tamanio_dispersion);

	//Borra todos los registros del bloque y los guarda en memoria
	list<RegistroIndice *> *registros_a_redispersar = bloque_desbordado->VaciarBloque();
	//vuelve a guardar el bloque, ahora sin registros y con su nuevo tamaño de dispersión:
	bloque_desbordado->Persistir(this->nombre_arch_bloques.c_str(), offset_bloque);
	delete bloque_desbordado;

	//inserta un nuevo bloque con el nuevo tamaño de dispersión
	BloqueHash *nuevo_bloque = new BloqueHash(nuevo_tamanio_dispersion);
	unsigned int num_nuevo_bloque = extraer_nro_nuevo_bloque();
	nuevo_bloque->Persistir(this->nombre_arch_bloques.c_str(), num_nuevo_bloque*BloqueHash::getTamanioBloques());
	delete nuevo_bloque;

	//y asigna su referencia a todas las posiciones de la tabla
	//que estén a distancia n*nuevo_tamanio_dispersion
	vector<unsigned int> *tabla_disp = cargar_tabla_dispersion();
	unsigned int posicion = posicion_en_tabla;
	unsigned int distancia = 0;
	unsigned int tamanio_tabla = (*tabla_disp)[0];
	do{
		if(distancia%nuevo_tamanio_dispersion == 0) (*tabla_disp)[posicion] = num_nuevo_bloque;

		if(posicion + 1 > tamanio_tabla) posicion = 1;
		else posicion++;
		distancia++;
	}while(posicion != posicion_en_tabla);
	persistir_vector(tabla_disp, tabla_dispersion, this->nombre_arch_tabla.c_str());

	//redispersa los registros del bloque desbordado
	RegistroIndice *registroEnLista = NULL;
	list<RegistroIndice *>::iterator it;
	for (it = registros_a_redispersar->begin(); it != registros_a_redispersar->end(); it++){
		registroEnLista = *it;
		guardar(registroEnLista);
	}
}

////////////////////////

void hash_extensible::expandir_hash(unsigned int posicion_en_tabla){

	unsigned int offset_bloque = obtener_offset_bloque(posicion_en_tabla);
	BloqueHash *bloque_aux = new BloqueHash(0);
	bloque_aux = (BloqueHash*)bloque_aux->Leer(this->nombre_arch_bloques.c_str(), offset_bloque);
	unsigned int tamanio_dispersion = bloque_aux->getTamanioDispersion();
	delete bloque_aux;
	unsigned int tamanio_tabla = obtener_tamanio_tabla();

	if (tamanio_dispersion == tamanio_tabla) duplicar_tabla(posicion_en_tabla);
	else if (tamanio_dispersion < tamanio_tabla) incrementar_tabla(posicion_en_tabla);
}

///////////////////////////

void hash_extensible::guardar(RegistroIndice *registro){

	unsigned int offset_bloque = obtener_offset_bloque(funcion_hashing(registro));
	BloqueHash *bloque_aux = new BloqueHash(0);
	bloque_aux = (BloqueHash*) bloque_aux->Leer(this->nombre_arch_bloques.c_str(), offset_bloque);

	/* trata de insertar el registro y salir */
	if(bloque_aux->Insertar(registro)){
		bloque_aux->Persistir(this->nombre_arch_bloques.c_str(), offset_bloque);
		delete bloque_aux;
		return;
	}

	delete bloque_aux;

	/* si el bloque estaba lleno y no se pudo insertar el registro,
	 * agrega otro bloque, modifica la tabla, redispersa, guarda y termina */
	expandir_hash(funcion_hashing(registro));
	guardar(registro);

	/* NOTA: bloque::insertar(registro) debe estár implementado de forma tal que si
	 * el registro ya estaba en el bloque, el viejo es reemplazado por el nuevo */
}

//////////////////////////

bool hash_extensible::borrar(RegistroIndice *registro){

	unsigned int offset_bloque = obtener_offset_bloque(funcion_hashing(registro));
	BloqueHash *bloque_aux = new BloqueHash(0);
	bloque_aux = (BloqueHash*)bloque_aux->Leer(this->nombre_arch_bloques.c_str(), offset_bloque);
	if(bloque_aux != NULL){
		if(bloque_aux->Eliminar(registro)){
			bloque_aux->Persistir(this->nombre_arch_bloques.c_str(), offset_bloque);

			/* revisa si el bloque quedó vacío para tratar de liberarlo*/
			if(bloque_aux->getCantidadRegistros() == 0)
				reducir_hash(funcion_hashing(registro));

			delete bloque_aux;
			return true;
		}
		delete bloque_aux;
	}
	return false;
}

//////////////////////////

void hash_extensible::reducir_hash(unsigned int posicion_en_tabla){

	vector<unsigned int> *tabla = cargar_tabla_dispersion();
	unsigned int tamanio_tabla = (*tabla)[0];
	unsigned int nro_bloque_vacio = (*tabla)[posicion_en_tabla];

	/* calcula la distancia que hay que moverse a derecha e izquierda de
	 * posicion_en_tabla para ver si los números de bloque consignados en esas
	 * posiciones coinciden y determinar si el bloque puede o no ser liberado*/
	long offset_bloque = obtener_offset_bloque(posicion_en_tabla);
	BloqueHash *bloque_vacio = new BloqueHash(0);
	bloque_vacio = (BloqueHash*)bloque_vacio->Leer(this->nombre_arch_bloques.c_str(), offset_bloque);

	unsigned int distancia_final = bloque_vacio->getTamanioDispersion()/2;
	delete bloque_vacio;
	unsigned int posicion_adelante = posicion_en_tabla;
	unsigned int posicion_atras = posicion_en_tabla;
	unsigned int distancia_actual = 0;

	do{
		if(posicion_adelante + 1 > tamanio_tabla) posicion_adelante = 1;
		else posicion_adelante++;
		distancia_actual++;
	}while(distancia_actual < distancia_final);

	distancia_actual = 0;
	do{
		if(posicion_atras - 1 < 1) posicion_atras = tamanio_tabla;
		else posicion_atras--;
		distancia_actual++;
	}while(distancia_actual < distancia_final);

	/* si coinciden recorre la tabla de dispersión y en cada posición a distancia
	 * n*distancia_final del bloque vacío asigna el número de bloque que lo reemplaza */
	if((*tabla)[posicion_atras] == (*tabla)[posicion_adelante]){
		unsigned int bloque_a_asignar = (*tabla)[posicion_atras];
		unsigned int distancia = 0;
		unsigned int posicion = posicion_en_tabla;
		do{
			if(distancia%distancia_final == 0) (*tabla)[posicion] = bloque_a_asignar;

			if(posicion + 1 > tamanio_tabla) posicion = 1;
			else posicion++;
			distancia++;
		}while(posicion != posicion_en_tabla);
		
		persistir_vector(tabla, tabla_dispersion, this->nombre_arch_tabla.c_str());
		 
		//libera el bloque vacío (agrega al archivo de bloques libres)
		vector<unsigned int> *lista_bloques_libres = cargar_archivo_bloques_libres();
		((*lista_bloques_libres)[0])++;
		lista_bloques_libres->reserve((*lista_bloques_libres)[0] + 1);
		(*lista_bloques_libres)[(*lista_bloques_libres)[0]] = nro_bloque_vacio;
		persistir_vector(lista_bloques_libres, arch_bloques_libres, this->nombre_arch_bloques_libres.c_str());

		//al bloque reemplazante le divide por 2 el tamaño de dispersion
		unsigned int offset_reemplazante = obtener_offset_bloque(posicion_en_tabla);
		BloqueHash *bloque_reemplazante = new BloqueHash(0);
		bloque_reemplazante = (BloqueHash*)bloque_reemplazante->Leer(this->nombre_arch_bloques.c_str(), offset_reemplazante);
		unsigned int nuevo_tam_dispersion = bloque_reemplazante->getTamanioDispersion()/2;
		bloque_reemplazante->setTamanioDispersion(nuevo_tam_dispersion);
		bloque_reemplazante->Persistir(this->nombre_arch_bloques.c_str(), offset_reemplazante);
		delete bloque_reemplazante;

		//si las dos mitades son iguales trunca la tabla
		bool distintas = false;
		for(unsigned int i = 1; i <= tamanio_tabla/2; i++){
			if((*tabla)[i + tamanio_tabla] != (*tabla)[i])
				distintas = true;
		}
		if (!distintas){
			vector<unsigned int> *aux = new vector<unsigned int>;
			aux->reserve(tamanio_tabla/2 +1);
			(*aux)[0] = tamanio_tabla/2;
			for(unsigned int i = 1; i <= tamanio_tabla/2; i++)
				(*aux)[i] = (*tabla)[i];

			persistir_vector(aux, tabla_dispersion, this->nombre_arch_tabla.c_str());
		}
	}
}

////////////////////////////

void hash_extensible::imprimir(const string nombre_archivo){

	if(!arch_bloques->is_open()) arch_bloques->open(nombre_arch_bloques.c_str(), ios::binary | ios::in);
	vector<unsigned int> *tabla = cargar_tabla_dispersion();
	vector<unsigned int> *lista_bloqlib = cargar_archivo_bloques_libres();
	unsigned int tamanio_tabla = (*tabla)[0];
	unsigned int tamanio_lista_libres = (*lista_bloqlib)[0];

	fstream archivo_texto;
	archivo_texto.open(nombre_archivo.c_str(), ios::out | ios::trunc);
	archivo_texto << "TD: tamaño de dispersion. EL: espacio libre" << endl << endl << endl;
	archivo_texto << "Tabla:" << endl;
	for(unsigned int i = 1; i <= tamanio_tabla; i++)
		archivo_texto << "  " << (*tabla)[i];
	archivo_texto << endl;
	archivo_texto << "Bloques libres:" << endl;
	for(unsigned int i = 1; i <= tamanio_lista_libres; i++)
		archivo_texto << "  " << (*lista_bloqlib)[i];
	archivo_texto << endl << endl;

	archivo_texto << "Bloques:" << endl;
	int max = -1;
	for(unsigned int i = 1; i <= (*tabla)[0]; i++)
		if((int)(*tabla)[i] > max) max = (*tabla)[i];

	/*arch_bloques->seekg(0, ios::end);
	long fin = arch_bloques->tellg();*/
	unsigned int offset_bloque = 0;
	BloqueHash *aux = new BloqueHash(0);
	unsigned int num_bloque;
	bool liberado = false;
	while(offset_bloque <= max*BloqueHash::getTamanioBloques()){
		aux = (BloqueHash*) aux->Leer(this->nombre_arch_bloques.c_str(), offset_bloque);
		num_bloque = offset_bloque/BloqueHash::getTamanioBloques();
		//antes de imprimir revisa que el bloque no esté liberado
		unsigned int i = 1;
		while((i <= tamanio_lista_libres) && (!liberado)){
			if((*lista_bloqlib)[i] == num_bloque) liberado = true;
			i++;
		}
		if(liberado){
			offset_bloque += BloqueHash::getTamanioBloques();
			liberado = false;
			delete aux;
			continue;
		}
		//imprime el contenido del bloque
		archivo_texto << num_bloque << ": ";
		aux->Imprimir(&archivo_texto);
		archivo_texto << endl;

		offset_bloque += BloqueHash::getTamanioBloques();
		delete aux;
	}
	archivo_texto.close();
	delete tabla;
	delete lista_bloqlib;
}
