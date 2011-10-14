#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <cstdlib>

#include "menu.h"
#include "Distrito.h"
#include "Cargo.h"
#include "DataAccess.h"
#include "Tests/Tester.h"
#include "RegistroArbol.h"
#include "Nodo.h"
#include "ArbolBMas.h"

using namespace std;

void testRegistroArbol();
void testNodoArbol();
void testArbolBMas();
void testArbolBMas1();
void testArbolBMas2();
void testArbolBMasGetTodos();
void testArbolBMasClavesDuplicadas();
void testArbolBMasCambiarOffsetRegistro();
void testArbolBMasBusquedaAproximada();
void testArbolBMasEliminar();

int main(int argc, char *argv[]){

 /*       Tester *tester=new Tester();
        tester->comenzarTests();
        delete tester;
*/
	// TODAVIA NO ANDAN LOS TESTS DE TESTABMentidades Y TESTPERSISTENCIA..SI QUIEREN PROBAR LOS OTROS
	// SAQUENLOS DEL TESTER.CPP (MARTIN)

 /*       Menu *menu = Menu::getMenu();
        if (argc != 2){
                // Numero incorrecto de parametros
                cout << "Uso: voto_electronico -h\n";
                return 0;
        }

        if ( !(strcmp(argv[1],"-h")) || !(strcmp(argv[1],"--help")) ) {
                // La funcionalidad deseada es acceder a la ayuda del programa.
                menu->mostrar_ayuda();
                return 0;
        }

        if ( !(strcmp(argv[1],"-a")) || !(strcmp(argv[1],"--admin")) ) {

                cout << "Ingreso como administrador. \n(para salir ingrese \"salir\" en alguno de los campos) \n";
                // La funcionalidad deseada es acceder como administrador
                // Se pide y verifica usuario y contraseña
                do {
                        menu->pedir_usuario();
                        menu->pedir_contrasena();
                } while (!menu->acceder_admin());

                return 0;
        }
        if ( !(strcmp(argv[1],"-u")) || !(strcmp(argv[1],"--user")) ) {

                cout << "Ingreso como usuario. \n(para salir ingrese \"salir\" en alguno de los campos) \n";
                // La funcionalidad deseada es acceder como usuario
                // Se pide y verifica usuario y contraseña
                do {
                        menu->pedir_usuario();
                        menu->pedir_contrasena();
                } while (!menu->acceder_usuario());

                return 0;
        }

        cout << "Uso: voto_electronico -h\n";   // Mal uso de las opciones
	*/
        return 0;
}

void testRegistroArbol()
{
	fstream f;
	//string url = "./test_registro.db";
	string url = "./test_registro.txt";
	//f.open(url.c_str(), ios::in | ios::out | ios::binary);
	f.open(url.c_str(), ios::in | ios::out);
	RegistroArbol * r1;
	RegistroArbol * r2;
	RegistroArbol * r3;

	if(f.is_open())
	{
		r1 = new RegistroArbol("r1", 1);
		r2 = new RegistroArbol("re2", 2);
		r3 = new RegistroArbol("reg3", 3);

		r1->Guardar(f);
		r2->Guardar(f);
		r3->Guardar(f);

		delete r1;
		delete r2;
		delete r3;

		f.close();
	}
	else
		cout<<"no se pudo abrir el archivo "+url+" para escribir";


	//f.open(url.c_str(), ios::in | ios::out | ios::binary);
	f.open(url.c_str(), ios::in | ios::out);

	if(f.is_open())
	{
		r3 = RegistroArbol::Leer(f);
		r2 = RegistroArbol::Leer(f);
		r1 = RegistroArbol::Leer(f);
		r3->Imprimir();
		//cout << r3->getTamanioEnDisco();
		cout << endl;
		r2->Imprimir();
		//cout << r2->getTamanioEnDisco();
		cout << endl;
		r1->Imprimir();
		//cout << r1->getTamanioEnDisco();
		cout << endl;
	}
	else
		cout<<"no se pudo abrir el archivo "+url+" para leer";
}

void testNodoArbol()
{
	Nodo * n1 = new Nodo();
	Nodo * n2;

	fstream f;
	//string url = "./test_nodo.db";
	//f.open(url.c_str(), ios::in | ios::out | ios::binary);

	string url = "./test_nodo.txt";
	f.open(url.c_str(), ios::in | ios::out);

	RegistroArbol * r1;
	RegistroArbol * r2;
	RegistroArbol * r3;
	RegistroArbol * r4;
	bool statusOK = false;

	int primeraPosicionNodo = 30;

	//Tengo q generar espacio en e; archivo si esta vacio para poder
	//hacer seekp sobre una posicion q no existe
	for(int i = 0; i < primeraPosicionNodo; i++)
		f<<" ";

	f.seekp(0);

	if(f.is_open())
	{
		//Settear tamanio de nodo a 100bytes
		r1 = new RegistroArbol("r1", 1);
		r2 = new RegistroArbol("re2", 2);
		r3 = new RegistroArbol("reg3", 3);
		r4 = new RegistroArbol("reg4", 4);
		/////////Pruebas/////////////
		n1->addr_ = primeraPosicionNodo;
		n1->agregarRegistro(r1->getClave(), r1->getOffset());
		n1->agregarRegistro(*r2);
		n1->agregarRegistro(r3->getClave(), r3->getOffset());
		n1->agregarRegistro(*r4);

		if(n1->flags_==Nodo::NodoCambiado)
			cout<< "flag_ se esta setteando bien en el agregarRegistro()"<<endl;

		if(n1->estaLleno())
			cout << "estaLleno() OK"<<endl;
		else
			cout << "estaLleno() ERROR"<<endl;

		n1->Imprimir();
		n1->Guardar(f);

		cout<<"Se limpio el nodo"<<endl;
		n1->clear();

		if(n1->estaVacio())
			cout<<"Si no se imprimio nada clear() y estaVacio() OK"<<endl;
		else
			cout<<"Si no se imprimio nada clear() o estaVacio() ERROR"<<endl;
		n1->Imprimir();
		cout<<"Se termino impresion de nodo limpio"<<endl;

		delete r1;
		delete r2;
		delete r3;
		delete r4;

		f.close();
	}
	else
		cout<<"no se pudo abrir el archivo "+url;

	//f.open(url.c_str(), ios::in | ios::out | ios::binary);
	f.open(url.c_str(), ios::in | ios::out);

	if(f.is_open())
	{
		//Settear tamanio de nodo a 100bytes
		/////////Pruebas/////////////
		f.seekp(0);
		f.seekg(primeraPosicionNodo);
		n1 = Nodo::Leer(f);

		n1->addr_ = primeraPosicionNodo; //Si asi funciona el leer creo q no funca bien

		if(n1->estaLleno())
			cout << "estaLleno() OK"<<endl;
		else
			cout<<"estaLleno() ERROR"<<endl;

		cout<<"Se imprime nodo leido del archivo"<<endl;
		n1->Imprimir();

		int posicionRegistroBuscado = -1;
		statusOK = false;
		if(n1->find("reg3", posicionRegistroBuscado))
			if(posicionRegistroBuscado == 2)
				if(!(n1->find("rerer", posicionRegistroBuscado)))
					statusOK = true;

		if(statusOK)
			cout<<"find() OK"<<endl;
		else
			cout<<"find() ERROR"<<endl;

		posicionRegistroBuscado = -1;
		statusOK = false;
		n1->removerEnPosicion(1); //Remueve el segundo registro
		if(n1->count() == 3)
			if(!(n1->find("re2", posicionRegistroBuscado)))
				statusOK = true;

		if(statusOK)
			cout<<"removerEnPosicion(indice) OK"<<endl;
		else
			cout<<"removerEnPosicion(indice) ERROR"<<endl;

		cout<<"Solo se debe mostrar los registros r1, r3 y r4"<<endl;
		n1->Imprimir();

		posicionRegistroBuscado = -1;
		statusOK = false;
		r4 = new RegistroArbol();
		n1->removerEnPosicion(0, *r4); //Remueve el primer registro
		if(n1->count() == 2)
			if(!(n1->find("r1", posicionRegistroBuscado)))
				if(r4->getClave() == "r1" && r4->getOffset() == 1)
					statusOK = true;

		if(statusOK)
			cout<<"removerEnPosicion(indice, registro) OK"<<endl;
		else
			cout<<"removerEnPosicion(indice, registro) ERROR"<<endl;

		delete r4;

		cout<<"Solo se debe mostrar los registros r3 y r4"<<endl;
		n1->Imprimir();

		n1->Guardar(f);
		cout<<"Se guarda nodo con registros r3 y r4"<<endl;

		f.seekg(primeraPosicionNodo);
		n2 = Nodo::Leer(f);

		cout<<"Se imprime nodo en su estado final, solo se debe ver r3 y r4"<<endl;
		n2->Imprimir();
		/////////////////////////////
		delete n2;

		f.close();

		cout<<"SE TERMINARON LOS TEST DEL NODO ARBOL"<<endl;
	}
	else
		cout<<"no se pudo abrir el archivo "+url;


	delete n1;
}

void testArbolBMas()
{
    //testArbolBMas1();
    //testArbolBMasClavesDuplicadas();
    //testArbolBMas2();
    //testArbolBMasCambiarOffsetRegistro();
    //testArbolBMasGetTodos();
    //testArbolBMasBusquedaAproximada();
    testArbolBMasEliminar();
}

void testArbolBMasClavesDuplicadas()
{
    ArbolBMas * arbol = new ArbolBMas();
    //string urlArbol = "./test_arbol.db";
    string url = "/home/facundo/workspace2/TP1Voto Electronico/test_arbol1.txt";
    bool seEncontroTodo = true;

    //RegeneroArchivo de Prueba
    fstream f;
    f.open(url.c_str(), ios::out|ios::trunc);
    f.close();

    string clave1 = "reg1";
    string clave2 = "reg2";
    string clave3 = "reg3";
    string clave4 = "reg4";
    string clave5 = "reg5";
    string clave6 = "reg6";
    string clave7 = "reg7";
    string clave8 = "reg8";
    string clave9 = "reg9";
    string clave10 = "reg99";

    arbol->open(url);

    arbol->agregar(clave1, 1);

    arbol->agregar(clave2, 2);

    for(int i = 0; i <  100; i++)
        arbol->agregar(clave3, 3);
    arbol->agregar(clave4, 4);
    arbol->agregar(clave5, 5);
    arbol->agregar(clave6, 6);
    arbol->agregar(clave7, 7);
    arbol->agregar(clave8, 8);
    arbol->agregar(clave9, 9);

    for(int i = 0; i <  100; i++)
        arbol->agregar(clave10, 10);

    long d = -1;

    seEncontroTodo &= arbol->buscar(clave1, d);
    seEncontroTodo &= arbol->buscar(clave2, d);
    seEncontroTodo &= arbol->buscar(clave3, d);
    seEncontroTodo &= arbol->buscar(clave4, d);
    seEncontroTodo &= arbol->buscar(clave5, d);
    seEncontroTodo &= arbol->buscar(clave6, d);
    seEncontroTodo &= arbol->buscar(clave7, d);
    seEncontroTodo &= arbol->buscar(clave8, d);
    seEncontroTodo &= arbol->buscar(clave9, d);
    seEncontroTodo &= arbol->buscar(clave10, d);

    if(seEncontroTodo)
        cout<<"OK: Se econtraron todos los registros"<<endl;
    else
        cout<<"ERROR: No se econtro algun registro"<<endl;

    cout<<"Toque una tecla para terminar TestArbol1"<<endl;
    getchar();

}

void testArbolBMas2()
{
    ArbolBMas * arbol = new ArbolBMas();
    //string urlArbol = "./test_arbol.db";
    string url = "/home/facundo/workspace2/TP1Voto Electronico/test_arbol2.txt";

    long random_integer;
    int lowest=1, highest=10000000;
    int cantidadRegistros = 1000;
    int range=(highest-lowest)+1;
    string clave;
    vector<long> registros;
    long dato;
    bool busquedaFunciona = true;

    srand(time(NULL));

    fstream f;
    f.open(url.c_str(), ios::out|ios::trunc);
    f.close();

    arbol->open(url);

    for(int i = 0; i < cantidadRegistros; i++){
            random_integer = lowest + rand() % (highest +1 - lowest);

            clave = "reg" + Utilidades::toString(random_integer);

            registros.push_back(random_integer);
            arbol->agregar(clave, random_integer);

            Utilidades::sleep(10000);
    }

    for(int i = 0; i < cantidadRegistros; i++){

            clave = "reg" + Utilidades::toString(registros[i]);

            //Pongo a dato en -1 por q si no se modifica se q hubo un error
            dato = -1;

            arbol->buscar(clave, dato);

            if(dato != registros[i])
            {
                    busquedaFunciona = false;
                    break;
            }
    }

    if(busquedaFunciona)
            cout<<"find() OK"<<endl;
    else
            cout<<"find() Error"<<endl;

    cout<<"Toque una tecla para terminar TestArbol2"<<endl;
    getchar();
}

void testArbolBMasEliminar()
{
    ArbolBMas * arbol = new ArbolBMas();
    //string urlArbol = "./test_arbol.db";
    string url = "/home/facundo/workspace2/TP1Voto Electronico/test_arbol_eliminar.txt";

    long random_integer;
    int lowest=1, highest=10000000;
    int cantidadRegistros = 1000;
    int range=(highest-lowest)+1;
    string clave;
    vector<long> registros;
    long dato;
    bool busquedaFunciona = true;

    srand(time(NULL));

    fstream f;
    f.open(url.c_str(), ios::out|ios::trunc);
    f.close();

    arbol->open(url);

    for(int i = 0; i < cantidadRegistros; i++){
        //random_integer = lowest + rand() % (highest +1 - lowest);
        random_integer = i;

        clave = "reg" + Utilidades::toString(random_integer);

        registros.push_back(random_integer);
        arbol->agregar(clave, random_integer);

        //Utilidades::sleep(10000);
    }

    for(int i = 0; i < 700; i++)
    {
        clave = "reg" + Utilidades::toString(registros[i]);
        arbol->remove(clave);
    }


    list<RegistroArbol *> registros2;
    arbol->getTodosLosRegistros(registros2);

    for(int i = 700; i < cantidadRegistros; i++)
    {
        clave = "reg" + Utilidades::toString(registros[i]);

        //Pongo a dato en -1 por q si no se modifica se q hubo un error
        dato = -1;

        arbol->buscar(clave, dato);

        if(dato != registros[i])
        {
            busquedaFunciona = false;
            break;
        }
    }


    for(int i = 0; i < 700; i++)
    {
        clave = "reg" + Utilidades::toString(registros[i]);

        //Pongo a dato en -1 por q si no se modifica se q hubo un error
        dato = -1;

        if(arbol->buscar(clave, dato))
        {
            busquedaFunciona = false;
            break;
        }
    }

    if(busquedaFunciona)
            cout<<"remover() OK"<<endl;
    else
            cout<<"remover() Error"<<endl;

    cout<<"Toque una tecla para terminar Test"<<endl;
    getchar();
}

void testArbolBMasCambiarOffsetRegistro()
{
    ArbolBMas * arbol = new ArbolBMas();
    //string urlArbol = "./test_arbol.db";
    string url = "/home/facundo/workspace2/TP1Voto Electronico/test_arbol_cambiar_offset.txt";

    long random_integer;
    int lowest=1, highest=10000000;
    int cantidadRegistros = 1000;
    int range=(highest-lowest)+1;
    string clave;
    vector<long> registros;
    long dato;
    bool modficarOffsetFunciona = true;

    srand(time(NULL));

    fstream f;
    f.open(url.c_str(), ios::out|ios::trunc);
    f.close();

    arbol->open(url);

    for(int i = 0; i < cantidadRegistros; i++){
            random_integer = lowest + rand() % (highest +1 - lowest);

            clave = "reg" + Utilidades::toString(random_integer);

            registros.push_back(random_integer);
            arbol->agregar(clave, random_integer);

            Utilidades::sleep(10000);
    }

   int indiceRegistroAModifica = (2*cantidadRegistros) / 3;


    string claveModificacion1 = "reg" + Utilidades::toString(registros[((2*cantidadRegistros) / 3)]);
    string claveModificacion2 = "reg" + Utilidades::toString(registros[((cantidadRegistros) / 3)]);
    long offsetModificacion1 = 55;
    long offsetModificacion2 = 8555555;

    arbol->cambiarOffset(claveModificacion1, offsetModificacion1);
    arbol->cambiarOffset(claveModificacion2, offsetModificacion2);

    dato = -1;
    arbol->buscar(claveModificacion1, dato);
    if(dato != offsetModificacion1)
        modficarOffsetFunciona =  false;

    dato = -1;
    arbol->buscar(claveModificacion2, dato);
    if(dato != offsetModificacion2)
        modficarOffsetFunciona =  false;

    if(modficarOffsetFunciona)
            cout<<"cambiarOffset() OK"<<endl;
    else
            cout<<"cambiarOffset() Error"<<endl;

    cout<<"Toque una tecla para terminar Test"<<endl;
    getchar();
}

void testArbolBMasGetTodos()
{
    ArbolBMas * arbol = new ArbolBMas();
    //string urlArbol = "./test_arbol.db";
    string url = "/home/facundo/workspace2/TP1Voto Electronico/test_arbol_getTodos.txt";
    bool seEncontroTodo = true;
    list<RegistroArbol *> registros;

    //RegeneroArchivo de Prueba
    fstream f;
    f.open(url.c_str(), ios::out|ios::trunc);
    f.close();

    string clave1 = "reg1";
    string clave2 = "reg2";
    string clave3 = "reg";
    string clave4 = "reg4";
    string clave5 = "reg5";
    string clave6 = "reg6";
    string clave7 = "reg7";
    string clave8 = "reg8";
    string clave9 = "reg9";
    string clave10 = "reg99";

    arbol->open(url);

    arbol->agregar(clave1, 1);
    arbol->agregar(clave2, 2);
    arbol->agregar(clave3, 3);
    arbol->agregar(clave4, 4);
    arbol->agregar(clave5, 5);
    arbol->agregar(clave6, 6);
    arbol->agregar(clave7, 7);
    arbol->agregar(clave8, 8);
    arbol->agregar(clave9, 9);
    arbol->agregar(clave10, 10);

    arbol->getTodosLosRegistros(registros);

    list<RegistroArbol *>::iterator pos;
    pos = registros.begin();
    while( pos != registros.end())
    {
        cout << (*pos)->clave << endl;
        pos++;
    }

//    if(seEncontroTodo)
//        cout<<"getTodos() OK"<<endl;
//    else
//        cout<<"getTodos() ERROR"<<endl;

    cout<<"Toque una tecla para terminar Test"<<endl;
    getchar();
}

void testArbolBMasBusquedaAproximada()
{
    ArbolBMas * arbol = new ArbolBMas();
    //string urlArbol = "./test_arbol.db";
    string url = "/home/facundo/workspace2/TP1Voto Electronico/test_arbol_busquedaAprox.txt";
    bool seEncontroTodo = true;
    list<RegistroArbol *> registros;

    //RegeneroArchivo de Prueba
    fstream f;
    f.open(url.c_str(), ios::out|ios::trunc);
    f.close();

    string clave1 = "reg1";
    string clave2 = "reg2";
    string clave3 = "reg3";
    string clave4 = "reg4";
    string clave5 = "reg5";
    string clave6 = "reg6";
    string clave7 = "reg7";
    string clave8 = "reg8";
    string clave9 = "reg9";
    string clave10 = "reg99";

    arbol->open(url);

    arbol->agregar(clave1, 1);
    arbol->agregar(clave2, 2);
    arbol->agregar(clave3, 3);
    arbol->agregar(clave4, 4);
    arbol->agregar(clave6, 6);
    arbol->agregar(clave7, 7);
    arbol->agregar(clave8, 8);
    arbol->agregar(clave9, 9);
    arbol->agregar(clave10, 10);

    arbol->search(registros,clave2,true);

    list<RegistroArbol *>::iterator pos;
    pos = registros.begin();
    cout<<"Impresion busqueda precisa: "<<endl;
    while( pos != registros.end())
    {
        cout << (*pos)->clave << endl;
        pos++;
    }

    registros.clear();
    arbol->search(registros,clave5, clave9);//clave9);
    //lo de abajo compila pero toma la cadena reg9 como si fuera un booleano y se llama a la a qno debe
    //arbol->search(registros,clave5, "reg9");

    pos = registros.begin();
    cout<<"Impresion busqueda no precisa: "<<endl;
    while( pos != registros.end())
    {
        cout << (*pos)->clave << endl;
        pos++;
    }

    registros.clear();
    arbol->search(registros,clave5,true);

    if(registros.size() == 0)
        cout<<"Busqueda precisa de un nodo no existente OK"<<endl;
    else
        cout<<"Busqueda precisa de un nodo no existente ERROR"<<endl;

//    if(seEncontroTodo)
//        cout<<"getTodos() OK"<<endl;
//    else
//        cout<<"getTodos() ERROR"<<endl;

    cout<<"Toque una tecla para terminar Test"<<endl;
    getchar();
}


void testArbolBMas1()
{
    //Cosas probadas y q funcionan bien:
    //open(), close(), destructor

    ArbolBMas * arbol = new ArbolBMas();
    //string urlArbol = "./test_arbol.db";
    string url = "/home/facundo/workspace2/TP1Voto Electronico/test_arbol1.txt";

    //RegeneroArchivo de Prueba
    fstream f;
    f.open(url.c_str(), ios::out|ios::trunc);
    f.close();

    string clave1 = "reg1";
    string clave2 = "reg2";
    string clave3 = "reg3";
    string clave4 = "reg4";
    string clave5 = "reg5";
    string clave6 = "reg6";
    string clave7 = "reg7";
    string clave8 = "reg8";
    string clave9 = "reg9";
    string clave10 = "reg99";

    arbol->open(url);

    if(!arbol->agregar(clave1, 1))
            cout<<"1er add() devolvio FALSE"<<endl;
    if(!arbol->agregar(clave2, 2))
            cout<<"2do add() devolvio FALSE"<<endl;
    if(!arbol->agregar(clave3, 3))
            cout<<"3er add() devolvio FALSE"<<endl;
    if(!arbol->agregar(clave4, 4))
            cout<<"4to add() devolvio FALSE"<<endl;
    if(!arbol->agregar(clave5, 5))
            cout<<"5to add() devolvio FALSE"<<endl;
    if(!arbol->agregar(clave6, 6))
            cout<<"6to add() devolvio FALSE"<<endl;
    if(!arbol->agregar(clave7, 7))
            cout<<"7mo add() devolvio FALSE"<<endl;
    if(!arbol->agregar(clave8, 8))
            cout<<"8vo add() devolvio FALSE"<<endl;
    if(!arbol->agregar(clave9, 9))
            cout<<"9no add() devolvio FALSE"<<endl;
    if(!arbol->agregar(clave10, 10))
            cout<<"10mo add() devolvio FALSE"<<endl;

    long d = -1;

    arbol->buscar(clave1, d);
    cout<<"Valor del registro buscado: "<<d<<endl;
    d = -1;
    arbol->buscar(clave2, d);
    cout<<"Valor del registro buscado: "<<d<<endl;
    d = -1;
    arbol->buscar(clave3, d);
    cout<<"Valor del registro buscado: "<<d<<endl;
    d = -1;
    arbol->buscar(clave4, d);
    cout<<"Valor del registro buscado: "<<d<<endl;
    d = -1;
    arbol->buscar(clave5, d);
    cout<<"Valor del registro buscado: "<<d<<endl;
    d = -1;
    arbol->buscar(clave6, d);
    cout<<"Valor del registro buscado: "<<d<<endl;
    d = -1;
    arbol->buscar(clave7, d);
    cout<<"Valor del registro buscado: "<<d<<endl;
    d = -1;
    arbol->buscar(clave8, d);
    cout<<"Valor del registro buscado: "<<d<<endl;
    d = -1;
    arbol->buscar(clave9, d);
    cout<<"Valor del registro buscado: "<<d<<endl;
    d = -1;
    arbol->buscar(clave10, d);
    cout<<"Valor del registro buscado: "<<d<<endl;

    cout<<"Toque una tecla para terminar TestArbol1"<<endl;
    getchar();
}

/* Ejemplo de uso del hash
 *
 *
 * Crear hash:
 *
 * //recibe como parámetros las rutas del arcivo de bloques, el archivo de bloques libres y el archivo con la tabla de dispersion
 * hash_extensible *hash = new hash_extensible("archBloques", "archBloqLibres", "tablaDispersion");
 *
 * Obtener distrito:
 *
 * //crear un registro con la clave del distrito que se quiere obtener (el offset no importa asi que lo pongo en 0)
 * RegistroIndice registro("Avellaneda", 0);
 *
 * //pasar el registro al hash
 * hash_extensible->buscar(&registro);
 *
 * //Ahora haciendo registro.getOffset() se puede obtener el offset de ese distrito para buscarlo
 * //en su archivo. Si no estaba en el hash, buscar devuelve false
 *
 * //Los métodos guardar y borrar se usan de la misma forma
 */
