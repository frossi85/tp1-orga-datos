/* 
 * File:   TestFactorizacion.h
 * Author: facundo
 *
 * Created on 28 de noviembre de 2011, 02:04
 */

#ifndef TESTFACTORIZACION_H
#define	TESTFACTORIZACION_H

#include "./Factorizacion.h"
#include "./RSA/RSA.h"

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <cstdlib>

#include <cctype>

using namespace std;

class TestFactorizacion {
public:
    TestFactorizacion();
    TestFactorizacion(const TestFactorizacion& orig);
    virtual ~TestFactorizacion();

    static void ejecutar();
private:

};

#endif	/* TESTFACTORIZACION_H */

