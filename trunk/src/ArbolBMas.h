/*
 * ArbolBMas.h
 *
 *  Created on: 08/10/2011
 *      Author: facundo
 */

#ifndef ArbolBMas_H_
#define ArbolBMas_H_

#include "RegistroArbol.h"
#include "Nodo.h"
#include <string>

using namespace std;

////////////////////////////////////////////////////////////////////////
///Ejemplo de uso del arbol:
/// PRECONDICION: El archivo de datos debe ser creado a mano antes de usar
///               por primera vez el arbol
///
/// 1.- ArbolBMas * arbol = new ArbolBMas();
/// 2.- arbol->open(url);
/// 3.- arbol->agregar(clave, offset);     //Devuelve bool diciendo si se agrego o no
/// 4.- arbol->buscar(clave, offsetEcontrado);  //Si lo encontr devuelve true, sino false.
///                                             //Guarda en offsetEcontrado el valor del offset de la buscada
/// 5.- arbol->close();

class ArbolBMas {
public:
	//La raiz siempre la tengo q mandener en memoria

	ArbolBMas();
	virtual ~ArbolBMas();

        ///
	/// Open stream-based BTree storage
	bool open(string url); //( JStream *stor, guint maxCacheSize, JStream *journal = 0 );

	///
	/// Returns true if tree is opened
	bool isOpen();

	///
	/// Agrega un par clave:offset si no existia en el arbol
        //  Devuelve true si lo pudo agregar y false si no lo pudo agregar
	bool agregar( const string &clave, const long &offset );

	///
	/// Remove pair by clave
	bool remove( const string &clave );

	///
	/// Remove pair by clave and return associated data
	bool remove( const string &clave, long &data );

	///
	/// Find data by clave, or return false if clave was not found
	bool buscar( const string &clave, long &data );

	///
	/// Find all specified data
//	bool search( TContainer &retList, const string &startclave,
//		bool preciseSearch, TChecker &condition );
//
//	///
//	/// Get all specified in container data
//	bool getAll( TContainer &retList );

	///
	/// Change data which belongs to the clave is specified
	//void changeData( const string &clave, const long &newData );

	///
	/// Close BTree and release all occupied resources
	void close();

private:

	int getMedian( Nodo *nodo, RegistroArbol &elem );

	//void splitnodoByclave( Nodo **fullnodo, string &clave );
	bool splitnodo( Nodo *nodo, RegistroArbol &median, Nodo **nodoRight );

	Nodo* findnodo( Nodo *nodo, const string &clave, int &retIndex, int &parentIndex, bool &found );

        //Para manejo de nodos libres
        bool hayEspacioLibre();

	//bool rebalance( Nodo *nodo, int parentIndex );
	//bool combine( Nodo *leftnodo, Nodo *rightnodo );
	//bool pullOut( Nodo *nodo, int itemIndex );

	//Nodo* rightMost( Nodo *subtree, string &largestclave, long &largestData );
	//Nodo* leftMost( Nodo *subtree, string &smallestclave, long &smallestData );

	// Internal search methods
//	bool allclaves( Nodo *nodo, TContainer &retList, int elemIndex,
//		const string &startclave, TChecker &condition );
//	bool allclaves( Nodo *nodo, TContainer &retList, TChecker &condition );
//	bool allclaves( Nodo *nodo, TContainer &retList );

	////////////////////////////////////////////////////////////////////
	//Seccion stream controler
	/////////////////////////////////////////////////////////////////

	///
	/// Release only one nodo
	void releasenodo( int addr );

	///
	/// Clear tree fully
	//bool clear();

	///
	/// Get root pointer
	//Nodo* root();

	///
	/// Load nodo is specified
	bool loadnodo( Nodo **nodo, int addr );

	// Storage related operations
	Nodo* newnodo();
	//bool allocFreeSpace();
	//bool readAllOffsets( Nodo *nodo );
	void deletenodo( Nodo *nodo );
	void savenodo( Nodo *nodo );
	int rootAddr();
	void rootAddr( int addr );

	Nodo * getRaiz();

	// Data
	Nodo *root_;
	fstream storage;
	//ios::pos_type storageSize;

	long maxCacheSize_; //son cantidad de nodos en RAM
	long rootAddr_;
	
	const static int finCamposControl = 512;
	
	int storageSize();
	//vector<Nodo *> freeChunks;
	vector<Nodo *> cache_;
	
	Nodo * buscarEnCache(int addr);
	Nodo * buscarEnCache(int addr, int &pos);
	
	bool nodoInCache( int addr );
	void borrarDeCache(int indice);
	
	void flushChanges();
	void closeController();
	void clearCache();
	void releaseCache();
	
	void ImprimirCache();
};

#endif /* ArbolBMas_H_ */
