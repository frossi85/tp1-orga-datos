/*
 * DataGetter.cpp
 *
 *  Created on: 13/10/2011
 *      Author: administrador
 */

#include "DataGetter.h"

DataGetter::DataGetter() {}

DataGetter::~DataGetter() {}


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


bool DataGetter::getEleccionesPorFechayDistrito(vector<Eleccion*> vecElecciones,string fecha, Votante &votante) {

	/* Chequeo si el vector de Elecciones esta vacio, si no lo vacio */
	if(vecElecciones.size() != 0) {
		int cantidad = vecElecciones.size();
		for(int i=0;i<cantidad;i++){
			if(vecElecciones[i] != NULL) {
				delete vecElecciones[i];
				vecElecciones[i] = NULL;
			}
		}
		vecElecciones.clear();
	}

	/* Obtengo la clave que quiero buscar */
	string claveInicial = Utilidades::indexarFecha(fecha);

	/* Pongo la clave hasta la que quiero buscar */
	string claveFinal = claveInicial + "&";

	/* Abro el arbol de Eleccion */
	ArbolBMas *arbolEleccion = new ArbolBMas();
	arbolEleccion->abrir((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_ARBOL_ELECCION));

	/* Busco en el arbol todos los ids de elecciones con la fecha pedida */
	list<RegistroArbol *> IDsElecciones;
    if (!arbolEleccion->buscar(IDsElecciones, claveInicial, claveFinal)) return false;		// Si no habia ninguna coincidencia, se devuelve false
    arbolEleccion->cerrar();
    delete arbolEleccion;
    arbolEleccion = NULL;

    /* A partir de la lista de IDs de elecciones se descartan las elecciones en las que ya participo el votante */
    int cantidadEleccionesVotante = votante.getElecciones().size();
    vector<long int> vecIDs;
    long int aux;
    bool encontrado = false;
    int j = 0;
    RegistroArbol *registroEnLista = NULL;
    list<RegistroArbol *>::iterator it;
    for (it = IDsElecciones.begin(); it != IDsElecciones.end(); it++){
    	registroEnLista = *it;
    	aux = registroEnLista->getOffset();
    	j = 0;
    	encontrado = false;
    	while ((!encontrado) && (j != cantidadEleccionesVotante)){
    		if (aux == votante.getElecciones()[j]->getId()) {
    			encontrado = true;
    		} else j++;
    	}
    	if (!encontrado) vecIDs.push_back(aux);
    }
    if (vecIDs.size() == 0) return false;		// Se descartaron todas las elecciones xq el votante ya habia votado en todas.

    /* Busco en el hash de id_eleccion/offset todas las elecciones restantes, y comparo si el distrito del votante pertenece a la eleccion */
    /* Si pertenece, se agrega a esa eleccion para retornar en el vector de elecciones */
    string arch_registros = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDELECCION_REGS));
    string arch_bloq_libres = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDELECCION_BLOQ_LIB));
    string arch_tabla = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDELECCION_TABLA));
    hash_extensible *hash_eleccion = new hash_extensible(arch_registros,arch_bloq_libres,arch_tabla);
    int cantidadIDs = vecIDs.size();
    RegistroIndice aBuscarID(" ",0);
   	RegistroIndice *returnRegID = NULL;
   	DataAccess dataAccess;
   	Eleccion aAgregar;
   	string nombreDistrito = votante.getDistrito().getNombre();
   	int cantidadDistritos;

    for(int k=0; k<cantidadIDs;k++) {
    	aBuscarID.setClave(Utilidades::toString(vecIDs[k]));
    	returnRegID = hash_eleccion->buscar(&aBuscarID);
    	if (returnRegID == NULL) throw VotoElectronicoExcepcion("No se encontro el id de la eleccion");
  		dataAccess.Leer(aAgregar,returnRegID->getOffset());
  		j = 0;
  		encontrado = false;
  		cantidadDistritos = aAgregar.getDistritos().size();
  		while ((!encontrado) && (j != cantidadDistritos)){
  			if (aAgregar.getDistritos()[j]->getNombre() == nombreDistrito) {
  				encontrado = true;
  				vecElecciones.push_back(new Eleccion(aAgregar));
  			} else j++;
  		}
    }
    delete hash_eleccion;
    hash_eleccion = NULL;
    if (vecElecciones.size() == 0) return false;
    return true;
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
