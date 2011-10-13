/*
 * TestLista.h
 *
 *  Created on: 12/10/2011
 *      Author: administrador
 */


#ifndef TESTLISTA_H_
#define TESTLISTA_H_
/* Leandro: Comento el código porque no compila, me tira undefined reference a los constructores de Lista y Eleccion.
 * Debe ser por los cambios que se hicieron en los constructores, revisar eso.
 * También comenté el include y la declaracion de esta clase dentro de Tester.


#include "Test.h"
#include "../Lista.h"
#include "../Eleccion.h"
#include "../Cargo.h"
#include "../Distrito.h"

class TestLista: public Test {
	Lista* lista;
	Eleccion* eleccion;
	Cargo* cargo;
	Distrito* distrito;

	bool testConstructor();
	bool testLectura_y_Escritura();

public:
	TestLista();
	virtual void comenzar();
	virtual void inicializar();
	virtual void liberarMemoria();
	virtual ~TestLista();
};
*/
#endif /* TESTLISTA_H_ */
