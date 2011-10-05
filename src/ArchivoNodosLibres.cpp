/*
 * ArchivoNodosLibres.cpp
 *
 *  Created on: 04/10/2011
 *      Author: martin
 */

#include "ArchivoNodosLibres.h"

ArchivoNodosLibres::ArchivoNodosLibres(string filename) {
	this->filename = filename.insert(filename.length()-4,"NodosLibres");
	int verificacion = abrirArchivo();
	if (verificacion != 0) verificacion = crearArchivo();
	if (verificacion != 0) cout << "Fallo\n";
	cerrarArchivo();
}

ArchivoNodosLibres::~ArchivoNodosLibres() {
	cerrarArchivo();
}

int ArchivoNodosLibres::abrirArchivo() {
	this->archivo = fopen(this->filename.c_str(),"r+b");
	return this->archivo ? 0 : -1;
}

int ArchivoNodosLibres::crearArchivo() {
	this->archivo = fopen(filename.c_str(),"w+b");
	if (this->archivo) {
		unsigned int contador = 0;									// Crea el archivo indicando que hay 0 nodos libres.
		fwrite(&contador,sizeof(unsigned int),1,this->archivo);
	}
	return this->archivo ? 0 : -1;
}

void ArchivoNodosLibres::cerrarArchivo() {
	if (this->archivo) {
		fclose(this->archivo);
		this->archivo = NULL;
	}
}

unsigned int ArchivoNodosLibres::getContadorNodosLibres() {
	unsigned int contador;

	abrirArchivo();
	fread(&contador,sizeof(unsigned int),1,this->archivo);
	cerrarArchivo();
	return contador;

}

int ArchivoNodosLibres::getNroNodoLibre() {
	unsigned int contador;
	unsigned int buffer;

	abrirArchivo();
	fread(&contador,sizeof(unsigned int),1,this->archivo);				// Lee la cantidad de nodos libres.
	if (contador == 0) return -1;										// No hay nodos libres.
	fseek(this->archivo,contador*sizeof(unsigned int),SEEK_SET);		// Se ubica para leer el ultimo nodo libre.
	fread(&buffer,sizeof(unsigned int),1,this->archivo);				// Lee el nro de nodo libre.
	contador--;
	rewind(this->archivo);
	fwrite(&contador,sizeof(unsigned int),1,this->archivo);				// Decrementa el contador de nodos libres.
	cerrarArchivo();
	return buffer;
}

void ArchivoNodosLibres::agregarNroNodoLibre(unsigned int nroNodo) {
	unsigned int contador;
	unsigned int buffer = nroNodo;

	abrirArchivo();
	fread(&contador,sizeof(unsigned int),1,this->archivo);			// Lee la cantidad de nodos libres.
	fseek(this->archivo,contador*sizeof(unsigned int),SEEK_CUR);	// Se ubica a continuacion del ultimo nodo libre.
	fwrite(&buffer,sizeof(unsigned int),1,this->archivo);			// Escribe el nro de nodo nuevo.
	contador++;
	rewind(this->archivo);
	fwrite(&contador,sizeof(unsigned int),1,this->archivo);			// Aumenta el contador de nodos libres.
	cerrarArchivo();
}
