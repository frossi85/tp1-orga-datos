/*
 * Tester.cpp
 *
 *  Created on: 12/10/2011
 *      Author: administrador
 */

#include "Tester.h"
#include "Test.h"
#include "TestVotante.h"
#include "TestEleccion.h"
#include "TestDataAccess.h"
#include "TestDistrito.h"
#include <iostream>

using namespace std;
Tester::Tester() {
	// TODO Auto-generated constructor stub

}

void Tester::comenzarTests(){

	cout<<"Se inician los test de las Clases"<<endl;

	Test *test;

	test=new TestVotante();
	test->comenzar(); delete test;

	test=new TestEleccion();
	test->comenzar(); delete test;

	test=new TestDataAccess();
	test->comenzar(); delete test;

	test=new TestDistrito();
	test->comenzar(); delete test;


}

Tester::~Tester() {
	// TODO Auto-generated destructor stub
}
