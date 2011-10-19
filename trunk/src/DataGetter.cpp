/*
 * DataGetter.cpp
 *
 *  Created on: 13/10/2011
 *      Author: administrador
 */

#include "DataGetter.h"
#include "Nodo.h"
#include "ArbolBMas.h"

DataGetter::DataGetter() {
	// TODO Auto-generated constructor stub

}


Votante* DataGetter::getVotante(const string dni){

	Votante *votante_resultante;

	//...
	//...

	Distrito distrito_prueba("Lanus");
	Votante *votante_prueba=new Votante(1111,"Juan Perez","tp","Corrientes 443",distrito_prueba);
	votante_resultante=votante_prueba;

	return votante_resultante;
}


vector<Lista *> DataGetter::getListas_por_Eleccion(Eleccion& eleccion){

	vector<Lista *> resultado;


	//Para probar

	Lista *l1,*l2,*l3;
	l1= new Lista("Proyecto Sur",eleccion);
	l2= new Lista("Pro",eleccion);
	l3= new Lista("Frente Amplio Progresista",eleccion);

	resultado.push_back(l1);
	resultado.push_back(l2);
	resultado.push_back(l3);

	return resultado;

}

vector<Eleccion *> DataGetter::getElecciones_por_Votante(Votante &votante){

	vector<Eleccion *> elecciones_resultado;



	//Para Probar Metodo
	Cargo cargo1("Presidente"),cargo2("Gobernador");
	Distrito distrito("Lanus");

	Eleccion *e1,*e2;

	e1= new Eleccion("20111023",cargo1,distrito);
	e2= new Eleccion("20111023",cargo2,distrito);

	elecciones_resultado.push_back(e1);
	elecciones_resultado.push_back(e2);

	return elecciones_resultado;


}

DataGetter::~DataGetter() {
	// TODO Auto-generated destructor stub
}

vector<Conteo *> DataGetter::getConteosPorDistrito(Distrito& distrito){

    //obtiene los offsets de los conteos requeridos
    ArbolBMas *arbol = new ArbolBMas();
    arbol->abrir(RUTA_ARBOL_REPORTE_DISTRITO);

    string claveInicial = distrito.getNombre();
    Utilidades::formatearClave(claveInicial);
    string claveFinal = claveInicial + "&";

    list<RegistroArbol *> offsetsConteos;
    arbol->buscar(offsetsConteos, claveInicial, false, claveFinal);

    //a partir de la lista de offsets crea un vector de Conteo* y lo devuelve
    DataAccess dataAccess;
    RegistroArbol *registroEnLista = NULL;
    list<RegistroArbol *>::iterator it;
    vector<Conteo *> conteos;
    conteos.reserve(offsetsConteos.size());
    Conteo contAux;
    for (it = offsetsConteos.begin(); it != offsetsConteos.end(); it++){
	registroEnLista = *it;
        dataAccess.Leer(contAux, registroEnLista->getOffset());
        conteos.push_back(new Conteo(contAux));
    }
    return conteos;
}


vector<Conteo *> DataGetter::getConteosPorLista(Lista& lista){

    //obtiene los offsets de los conteos requeridos
    ArbolBMas *arbol = new ArbolBMas();
    arbol->abrir(RUTA_ARBOL_REPORTE_LISTA);

    string fecha = Utilidades::indexarFecha(lista.getEleccion().getFecha());
    string claveInicial = fecha +"$" +lista.getEleccion().getCargo().getCargoPrincipal() +"$" +lista.getNombre();
    Utilidades::formatearClave(claveInicial);
    string claveFinal = claveInicial + "&";

    list<RegistroArbol *> offsetsConteos;
    arbol->buscar(offsetsConteos, claveInicial, false, claveFinal);

    //a partir de la lista de offsets crea un vector de Conteo* y lo devuelve
    DataAccess dataAccess;
    RegistroArbol *registroEnLista = NULL;
    list<RegistroArbol *>::iterator it;
    vector<Conteo *> conteos;
    conteos.reserve(offsetsConteos.size());
    Conteo contAux;
    for (it = offsetsConteos.begin(); it != offsetsConteos.end(); it++){
	registroEnLista = *it;
        dataAccess.Leer(contAux, registroEnLista->getOffset());
        conteos.push_back(new Conteo(contAux));
    }
    return conteos;
}

vector<Conteo *> DataGetter::getConteosPorEleccion(Eleccion& eleccion){
    
    //obtiene los offsets de los conteos requeridos
    ArbolBMas *arbol = new ArbolBMas();
    arbol->abrir(RUTA_ARBOL_REPORTE_ELECCION);

    string fecha = Utilidades::indexarFecha(eleccion.getFecha());
    string claveInicial = fecha +"$" +eleccion.getCargo().getCargoPrincipal();
    Utilidades::formatearClave(claveInicial);
    string claveFinal = claveInicial + "&";

    list<RegistroArbol *> offsetsConteos;
    arbol->buscar(offsetsConteos, claveInicial, false, claveFinal);

    //a partir de la lista de offsets crea un vector de Conteo* y lo devuelve
    DataAccess dataAccess;
    RegistroArbol *registroEnLista = NULL;
    list<RegistroArbol *>::iterator it;
    vector<Conteo *> conteos;
    conteos.reserve(offsetsConteos.size());
    Conteo contAux;
    for (it = offsetsConteos.begin(); it != offsetsConteos.end(); it++){
	registroEnLista = *it;
        dataAccess.Leer(contAux, registroEnLista->getOffset());
        conteos.push_back(new Conteo(contAux));
    }
    return conteos;
}
