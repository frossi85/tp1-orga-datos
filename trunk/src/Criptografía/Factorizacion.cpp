/* 
 * File:   Factorizacion.cpp
 * Author: facundo
 * 
 * Created on 27 de noviembre de 2011, 22:50
 */

#include "Factorizacion.h"

Factorizacion::Factorizacion() {
}

Factorizacion::~Factorizacion() {
}


bool Factorizacion::divisionesSucesivas(EnteroLargo N, EnteroLargo &p, EnteroLargo &q)
{
    vector<EnteroLargo> Ps;

    //Si N = 1, entonces el número no es factorizable (es 1).
    if(N == 1)
        return false;

//    Si no es 1:
//
//    i = 2
    EnteroLargo i = 2;

    //    mientras i < (N+1) y N no sea 1
    while(i< (N+1) && N != 1)
    {
        //si i es primo, y N es divisible por i
        if(esPrimo(i) && esDivisiblePor(N, i))
        {
//            agregamos i a Ps
//            Hacemos N = N/i
            Ps.push_back(i);
            N = N/i;
        }
        else
        {
//            incrementamos i
            i++;
        }
    }
//    devolvemos P
    
    cout<<endl;
    for(unsigned int j = 0; j < Ps.size(); j++)
    {
        cout<<"Factor "<<j<<": "<<Ps[j]<<endl;
    }

    p = Ps[0];
    q = Ps[0];

    return true;
}

bool Factorizacion::esCuadradoPerfecto(EnteroLargo a)
{
    EnteroLargo b = sqrt(a);
    EnteroLargo c = b*b;

    if(c==a)
        return true;
    else
        return false;
}

void Factorizacion::fermat(EnteroLargo N, EnteroLargo &p, EnteroLargo &q)
{
    //Metodo de Fermat

    EnteroLargo a = sqrt(N);
    a +=1;
    
    EnteroLargo b2 = a*a - N;

    while(!esCuadradoPerfecto(b2))
    {
        //b2 = b2 + 2*a + 1;
        //a = a + 1;

        a = a + 1;    // equivalently: b2 ← b2 + 2*a + 1
        b2 = a*a - N; //               a ← a + 1
    }
    
    cout<<endl;
    q =  a + sqrt(b2);
    p = a - sqrt(b2);

    cout<<"Factor 1: "<<p<<endl;
    cout<<"Factor 2: "<<q<<endl;
}

bool Factorizacion::esPrimo(EnteroLargo a)
{
    int contador=0;

    for(unsigned int i=1; i<=a; i++)
    {
        if(a%i==0)
            contador++;
        if(contador>2)
            return false;
    }
    if(contador==2)
        return true;
    else
        return false;
}

bool Factorizacion::esDivisiblePor(EnteroLargo a, EnteroLargo b)
{
    if(b == 0)
        return false;

    if((a%b) == 0)
        return true;

    return false;
}
