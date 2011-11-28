/* 
 * File:   TestFactorizacion.cpp
 * Author: facundo
 * 
 * Created on 28 de noviembre de 2011, 02:04
 */

#include "TestFactorizacion.h"

TestFactorizacion::TestFactorizacion() {
}

TestFactorizacion::TestFactorizacion(const TestFactorizacion& orig) {
}

TestFactorizacion::~TestFactorizacion() {
}

void TestFactorizacion::ejecutar()
{
    EnteroLargo a = 10163;//198000000607;//5;//7;//11;
    EnteroLargo b = 1000000363;//198000000599;//16553;//53;//3;
    EnteroLargo axb = a*b;//33;
    EnteroLargo p, q;


    if(Factorizacion::esCuadradoPerfecto(25))
        cout<<endl<<"esCuadradoPerfecto: OK"<<endl;

    if(!Factorizacion::esCuadradoPerfecto(26))
        cout<<endl<<"esCuadradoPerfecto: OK"<<endl;

    cout<<"axb: "<<axb<<endl;

//    if(Factorizacion::esPrimo(a) && Factorizacion::esPrimo(b))
//            cout<<endl<<"Test de numero primo: OK"<<endl;
//    else
//            cout<<endl<<"Test de numero primo: ERROR"<<endl;
//
//    if(!Factorizacion::esPrimo(a))
//                    cout<<endl<<"a no es primo"<<endl;
//
//    if(!Factorizacion::esPrimo(b))
//                    cout<<endl<<"b no es primo"<<endl;
//
    Factorizacion::fermat(axb, p, q);

    //Factorizacion::divisionesSucesivas(481, p, q);
}
