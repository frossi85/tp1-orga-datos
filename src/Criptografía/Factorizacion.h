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
#include <cmath>

using namespace std;

typedef long long unsigned EnteroLargo;
typedef long long int EnteroLargoSignado;

class Factorizacion {
	friend class TestFactorizacion;
public:
    static bool divisionesSucesivas(EnteroLargo N, EnteroLargo &p, EnteroLargo &q);
    static void fermat(EnteroLargo N, EnteroLargo &p, EnteroLargo &q);

private:
    static bool esPrimo(EnteroLargo a);
    static bool esDivisiblePor(EnteroLargo a, EnteroLargo b);

    static bool esCuadradoPerfecto(EnteroLargo a);

    Factorizacion();
    virtual ~Factorizacion();
};

#endif	/* FACTORIZACION_H */

