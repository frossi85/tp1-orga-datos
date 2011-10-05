/*
 * ArchivoNodosLibres.h
 *
 *  Created on: 04/10/2011
 *      Author: martin
 */

#ifndef ARCHIVONODOSLIBRES_H_
#define ARCHIVONODOSLIBRES_H_

#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

/*
 * Un archivo que contiene (estructura):

--------------------------------------------------------------------------
|  cantNodosLibres(unsigned int) | nroNodoLibre(int) | nroNodoLibre | etc|
--------------------------------------------------------------------------

 */

class ArchivoNodosLibres {
public:
	/*
	 * Se busca en la ruta donde estarian los archivos de nodos libres de los arboles, ej "../VotoElectronico/Arboles/filename.bin"
	 * Si el archivo no existe, se crea. Se inicializa contadorNodos en 0.
	 * Si el archivo ya existe, se abre.
	 */
	ArchivoNodosLibres(string filename);	// ej de filename: "ArbolVotante.bin"

	virtual ~ArchivoNodosLibres();

	unsigned int getContadorNodosLibres();
	int getNroNodoLibre();
	void agregarNroNodoLibre(unsigned int nroNodo);

private:
	FILE *archivo;
	string filename;						// se le agrega al filename del constructor "NodosLibres"
											// ej: "ArbolVotanteNodosLibres.bin"
											// Para facilidad de reconocimiento de archivos.
	int abrirArchivo();
	int crearArchivo();
	void cerrarArchivo();
};

#endif /* ARCHIVONODOSLIBRES_H_ */
