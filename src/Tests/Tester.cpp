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
#include "TestLista.h"
#include "TestCargo.h"
#include <iostream>

using namespace std;
Tester::Tester() {
	// TODO Auto-generated constructor stub

}

void Tester::comenzarTests(){

	int cantidad_tests=6;

	cout<<"Se inician los test de las Clases"<<endl;

	Test **test=new Test*[cantidad_tests];

	test[0]=new TestVotante();
	test[1]=new TestEleccion();
	test[2]=new TestDataAccess();
	test[3]=new TestDistrito();
	test[4]=new TestLista();
	test[5]=new TestCargo();

	for (int i=0;i<cantidad_tests;i++){
		test[i]->comenzar();
		delete test[i];
	}

	delete[] test;

}

Tester::~Tester() {
	// TODO Auto-generated destructor stub
}
