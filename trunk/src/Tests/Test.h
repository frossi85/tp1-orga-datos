/*
 * Test.h
 *
 *  Created on: 12/10/2011
 *      Author: administrador
 */

#ifndef TEST_H_
#define TEST_H_
#include <string>
using namespace std;
class Test {
protected:
	string clase_en_testeo;
public:
	Test();
	/*
	 * Este metodo llama a todos les test de la clase
	 * que se esta testiando
	 */
	virtual void comenzar()=0;

	/*
	 * Este metodo incializa todos los atributos necesarios para
	 * ejecutar un test
	 */
	virtual void inicializar()=0;

	/*
	 * Si encuentra algun error en algun metodo de alguna clase
	 * se va invocar a este metodo e imprime el metodo en el que
	 * se produjo el error
	 */
	void informarError(string metodo);

	virtual void liberarMemoria()=0;
	virtual ~Test();
};

#endif /* TEST_H_ */
