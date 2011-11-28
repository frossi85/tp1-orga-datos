/* 
 * File:   Factorizacion.h
 * Author: facundo
 *
 * Created on 27 de noviembre de 2011, 22:50
 */

#ifndef FACTORIZACION_H
#define	FACTORIZACION_H

#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <fstream>
#include "./RSA/RSA.h"
#include <cmath>

class Factorizacion {
public:
    Factorizacion();
    Factorizacion(const Factorizacion& orig);
    virtual ~Factorizacion();

    static bool factorizar1(EnteroLargo N, EnteroLargo &p, EnteroLargo &q);
    static void factorizar2(EnteroLargo N, EnteroLargo &p, EnteroLargo &q);
    static void factorizar3(EnteroLargo &N, EnteroLargo &p, EnteroLargo &q);
    static void factorizar4(EnteroLargo &N, EnteroLargo &p, EnteroLargo &q);
    static bool esPrimo(EnteroLargo a);
    static bool esDivisiblePor(EnteroLargo a, EnteroLargo b);

    static bool esCuadradoPerfecto(EnteroLargo a);

private:

};

#endif	/* FACTORIZACION_H */

