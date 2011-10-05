/*
 * ArbolBmas.h
 *
 *  Created on: 02/10/2011
 *      Author: martin
 */

#ifndef ARBOLBMAS_H_
#define ARBOLBMAS_H_

class ArbolBmas {
public:
	/*
	 * Se le pasa un valor aproximado de longitud de la clave que el usuario piense que es suficiente.
	 * Luego se calcula y define la longitud final que va a tener la clave y la maxima cantidad de registros
	 * en el nodo para que el tamaño de los nodos en disco sea multiplo de 512*2^n bytes.
	 * Se crea el archivo donde se va a guardar el arbol.
	 * Se crea una raiz vacia.
	 *
	 */
	ArbolBmas(unsigned int longitudClave, string filename);

	/* Para cargar un arbol desde archivo. Levanta la raiz a memoria.*/
	ArbolBmas(string filename);
	virtual ~ArbolBmas();

	int abrirArchivo(string filename); 		// privada, se llama desde contructor 1
	void cerrarArchivo();					// guarda la raiz y metadata del arbol en archivo
	int crearArchivo(string filename);				// privada, se llama desde contructor 0

	void agregarAListaDeNodosLibres(unsigned int nroNodo);
	void insertar(string clave);		// cuando se hace un alta de votante por ejemplo, en el arbol se verifica unicidad de clave, luego si todo ok
										// se fija en el archivo de datos de votante el offset de donde se va a guardar. se crea un RegitroArbol con
										// la clave y el offset y se inserta en el nodo correspondiente.
	void eliminar(string clave);
	void mostrar();						// mostrar in order?
	Clave *getSiguiente();
	//borrar
	Nodo *getRaiz();			// hacer clase clave
	//private:
	Nodo *fetch(unsigned int dirReg, unsigned int nivel);
	void fetchRaiz();
	void storeRaiz();
	void partirRaizHoja(Clave *clave);
	Clave *balanceoHojaADerecha(Nodo *nodoIzq, Nodo *nodoDer, Clave *claveAInsertar);
	Clave *balanceoHojaAIzquierda(Nodo *nodoIzq, Nodo *nodoDer);
	Clave *balanceoInternoAIzquierda(Nodo *nodoIzq, Nodo *nodoDer);
	Clave *balanceoInternoADerecha(Nodo *nodoIzq, Nodo *nodoDer, Clave *claveAInsertar);

private:
	unsigned int longitudID;
	unsigned int maxCantidadRegistrosNodo;
	string nombreArchivo;
	unsigned int tamanioNodo;

	unsigned int calcularMaxCantidadRegistrosEnNodo();
};


#endif /* ARBOLBMAS_H_ */
