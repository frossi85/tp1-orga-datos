/*
 * TestABMentidades.cpp
 *
 *  Created on: 13/10/2011
 *      Author: martin
 */



#include "TestABMentidades.h"

TestABMentidades::TestABMentidades() {}

TestABMentidades::~TestABMentidades() {}


/* Se crean 6 Distritos, se guardan en archivo y hash y se recuperan en forma opuesta */
void TestABMentidades::testAltaDistrito() {
	cout << endl << "********************************************************" << endl;
	cout << "            Comienzo Alta Test Distritos" << endl;
	cout << "********************************************************" << endl << endl;

	vector<Distrito> vecDistritos;

	UtilidadesTests::cargarDistritos(vecDistritos);
	int cantidadDistritos = vecDistritos.size();

	for(int i=0;i<cantidadDistritos;i++)	vecDistritos[i].Imprimir();

    for(int i=0;i<cantidadDistritos;i++) {
        if (ABMtest.altaDistrito(vecDistritos[i])) cout << "Alta "<<vecDistritos[i].getNombre()<<" correcta" << endl;
        else cout << "Alta "<<vecDistritos[i].getNombre()<<" incorrecta (ya existia)" << endl;
    }
    cout << endl;


    /* Pido que se impriman archivos de texto del hash para control */
	string regs((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_DISTRITO_REGS));
	string bloq_lib((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_DISTRITO_BLOQ_LIB));
	string tabla((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_DISTRITO_TABLA));

    hash_extensible hash_distrito(regs,bloq_lib,tabla);
    hash_distrito.imprimir("./archivos/Tests/testABM_hash_distrito");

    regs = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDDISTRITO_REGS));
    bloq_lib = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDDISTRITO_BLOQ_LIB));
    tabla = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDDISTRITO_TABLA));

    hash_extensible hash_iddistrito(regs,bloq_lib,tabla);
    hash_iddistrito.imprimir("./archivos/Tests/testABM_hash_iddistrito");

    /* Recupero los valores de distritos */
    // Debo guardar las claves para que no se cambien al cargar los registros
	string clave[cantidadDistritos];
	for(int i=0;i<cantidadDistritos;i++)	clave[i] = vecDistritos[i].getNombre();

    for(int i=0;i<cantidadDistritos;i++)	this->ConsultaEntidadesTest.ObtenerRegistro(clave[cantidadDistritos-1-i],vecDistritos[i]);

	for(int i=0;i<cantidadDistritos;i++)	vecDistritos[i].Imprimir();

	/* Prueba modificacion de un distrito */
	this->ConsultaEntidadesTest.ObtenerRegistro(clave[2],vecDistritos[2]);

	/*Cambia Santa Fe por Santa */
	clave[2] = "Santa";
	vecDistritos[2].modificarNombre("Santa");
	if (this->ABMtest.modificacionDistrito(vecDistritos[2])) cout << "Correcto "<< endl;

	for(int i=0;i<cantidadDistritos;i++)	this->ConsultaEntidadesTest.ObtenerRegistro(clave[i],vecDistritos[i]);
	for(int i=0;i<cantidadDistritos;i++)	vecDistritos[i].Imprimir();


	cout << endl << "********************************************************" << endl;
	cout << "                Fin Test Alta Distritos" << endl;
	cout << "********************************************************" << endl << endl;
}


/* Se crean 6 Cargos principales, con "i" cargos secundarios (i es indice de cargo).
 * Se guardan en archivo y hash y se recuperan en forma opuesta */
void TestABMentidades::testAltaCargo() {
	cout << endl << "********************************************************" << endl;
	cout << "            Comienzo Alta Test Cargos" << endl;
	cout << "********************************************************" << endl << endl;

	vector<Cargo> vecCargos;

	UtilidadesTests::cargarCargos(vecCargos);
	int cantidadCargos = vecCargos.size();

	for(int i=0;i<cantidadCargos;i++)	vecCargos[i].Imprimir();

    for(int i=0;i<cantidadCargos;i++) {
        if (ABMtest.altaCargo(vecCargos[i])) cout << "Alta " << vecCargos[i].getCargoPrincipal() << " correcta" << endl;
        else cout << "Alta " << vecCargos[i].getCargoPrincipal() << " incorrecta (ya existia)" << endl;
    }
    cout << endl;


    /* Pido que se impriman archivos de texto del hash para control */
    string regs((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_CARGO_REGS));
    string bloq_lib((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_CARGO_BLOQ_LIB));
    string tabla((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_CARGO_TABLA));

    hash_extensible hash_cargo(regs,bloq_lib,tabla);
    hash_cargo.imprimir("./archivos/Tests/testABM_hash_cargo");

    regs = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDCARGO_REGS));
    bloq_lib = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDCARGO_BLOQ_LIB));
    tabla = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDCARGO_TABLA));

    hash_extensible hash_idcargo(regs,bloq_lib,tabla);
    hash_idcargo.imprimir("./archivos/Tests/testABM_hash_idcargo");

    /* Recupero los valores de cargos */
    // Debo guardar las claves para que no se cambien al cargar los registros
    string clave[cantidadCargos];
	for(int i=0;i<cantidadCargos;i++)	clave[i] = vecCargos[i].getCargoPrincipal();

	for(int i=0;i<cantidadCargos;i++) this->ConsultaEntidadesTest.ObtenerRegistro(clave[cantidadCargos-1-i],vecCargos[i]);

	for(int i=0;i<cantidadCargos;i++)	vecCargos[i].Imprimir();


	cout << endl << "********************************************************" << endl;
	cout << "                Fin Test Alta Cargos" << endl;
	cout << "********************************************************" << endl << endl;
}


/* Se crean 6 Elecciones, con "i+1" distritos donde se realiza la votacion (i es indice de eleccion).
 * Se guardan en archivo y arbol y se recuperan en forma opuesta */
void TestABMentidades::testAltaEleccion() {
	cout << endl << "********************************************************" << endl;
	cout << "                Comienzo Test Alta Eleccion" << endl;
	cout << "********************************************************" << endl << endl;

	 vector<Distrito> vecDistritos;
	 vector<Cargo> vecCargos;

	 UtilidadesTests::cargarDistritos(vecDistritos);
	 UtilidadesTests::cargarCargos(vecCargos);
	 int cantidadDistritos = vecDistritos.size();
	 int cantidadCargos = vecCargos.size();


    /* Guardo los distritos. Verificar que ande antes el ABMentidades::altaDistrito() (ṔOR AHORA ANDA) */
	/* Para que tenga exito, no deben existir los archivos de hash de distrito */
    bool exito = true;
    for (int i=0;i<cantidadDistritos;i++)	if (exito) exito = this->ABMtest.altaDistrito(vecDistritos[i]);
    if (!exito) {
    	cout << "Fallo la carga de Distritos (verificar que no existan los hash de distrito)" << endl << endl;
    	return;
    }

	/* Guardo los cargos. Verificar que ande antes el ABMentidades::altaCargo() (ṔOR AHORA ANDA) */
    /* Para que tenga exito, no deben existir los archivos de hash de cargo */
	exito = true;
	for (int i=0;i<cantidadCargos;i++)	if (exito) exito = this->ABMtest.altaCargo(vecCargos[i]);
    if (!exito) {
    	cout << "Fallo la carga de Cargos (verificar que no existan los hash de cargo)" << endl << endl;
    	return;
    }

	vector<Eleccion> vecElecciones;

	UtilidadesTests::cargarElecciones(vecElecciones,vecCargos,vecDistritos);
	int cantidadElecciones = vecElecciones.size();

	for(int i=0;i<cantidadElecciones;i++) {
		vecElecciones[i].Imprimir();
		vecElecciones[i].ImprimirDistritos();
	}

	 for(int i=0;i<cantidadElecciones;i++) {
        if (ABMtest.altaEleccion(vecElecciones[i])) cout << "Alta " << vecElecciones[i].getFecha() << " correcta" << endl;
        else cout << "Alta " << vecElecciones[i].getFecha() << " incorrecta (ya existia)" << endl;
    }
    cout << endl;


    /* Recupero los valores de elecciones */
    // Debo guardar las claves para que no se cambien al cargar los registros
    string clave[cantidadElecciones];
 	for(int i=0;i<cantidadElecciones;i++)	{
 		clave[i] = Utilidades::indexarFecha(vecElecciones[i].getFecha()) + "$" + vecElecciones[i].getCargo().getCargoPrincipal();
 	}

   	for(int i=0;i<cantidadElecciones;i++) this->ConsultaEntidadesTest.ObtenerRegistro(clave[cantidadElecciones-1-i],vecElecciones[i]);

	for(int i=0;i<cantidadElecciones;i++) {
		vecElecciones[i].Imprimir();
		vecElecciones[i].ImprimirDistritos();
	}

	cout << endl << "********************************************************" << endl;
	cout << "                    Fin Test Alta Eleccion" << endl;
	cout << "********************************************************" << endl << endl;
}


/* Se crean 9 votantes y se le asignan elecciones (una o mas) a cada uno.
 * Se guardan en archivo y hash y luego se recuperan al reves. */
void TestABMentidades::testAltaVotante() {
	cout << endl << "********************************************************" << endl;
	cout << "              Comienzo Test Alta Votantes" << endl;
	cout << "********************************************************" << endl << endl;

	/* Cargo valores */
	vector<Distrito> vecDistritos;
	UtilidadesTests::cargarDistritos(vecDistritos);
	int cantidadDistritos = vecDistritos.size();

	vector<Cargo> vecCargos;
	UtilidadesTests::cargarCargos(vecCargos);
	int cantidadCargos = vecCargos.size();

	/* Guardo los distritos. Verificar que ande antes el ABMentidades::altaDistrito() (ṔOR AHORA ANDA) */
	/* Para que tenga exito, no deben existir los archivos de hash de distrito */
	bool exito = true;
	for (int i=0;i<cantidadDistritos;i++)	if (exito) exito = this->ABMtest.altaDistrito(vecDistritos[i]);
	if (!exito) {
	 	cout << "Fallo la carga de Distritos (verificar que no existan los hash de distrito)" << endl << endl;
	  	return;
	}

	/* Guardo los cargos. Verificar que ande antes el ABMentidades::altaCargo() (ṔOR AHORA ANDA) */
    /* Para que tenga exito, no deben existir los archivos de hash de cargo */
	exito = true;
	for (int i=0;i<cantidadCargos;i++)	if (exito) exito = this->ABMtest.altaCargo(vecCargos[i]);
    if (!exito) {
    	cout << "Fallo la carga de Cargos (verificar que no existan los hash de cargo)" << endl << endl;
    	return;
    }

    vector<Eleccion> vecElecciones;
    UtilidadesTests::cargarElecciones(vecElecciones,vecCargos,vecDistritos);
    int cantidadElecciones = vecElecciones.size();

	/* Guardo las elecciones. Verificar que ande antes el ABMentidades::altaEleccion() */
	/* Para que tenga exito, no debe existir el archivo de arbol de eleccion */
	exito = true;
	for (int i=0;i<cantidadElecciones;i++)	if (exito) exito = this->ABMtest.altaEleccion(vecElecciones[i]);
	if (!exito) {
	 	cout << "Fallo la carga de Elecciones (verificar que no exista el arbol de eleccion)" << endl << endl;
	  	return;
	}

    vector<Votante> vecVotantes;
    UtilidadesTests::cargarVotantes(vecVotantes,vecDistritos,vecElecciones);
    int cantidadVotantes = vecVotantes.size();

	for(int i=0;i<cantidadVotantes;i++)	vecVotantes[i].Imprimir();

	for(int i=0;i<cantidadVotantes;i++) {
      if (ABMtest.altaVotante(vecVotantes[i])) cout << "Alta " << vecVotantes[i].getDNI() << " correcta" << endl;
      else cout << "Alta " << vecVotantes[i].getDNI() << " incorrecta (ya existia)" << endl;
   }
   cout << endl;

   /* Pido que se impriman archivos de texto del hash para control */
   string regs((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_VOTANTE_REGS));
   string bloq_lib((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_VOTANTE_BLOQ_LIB));
   string tabla((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_VOTANTE_TABLA));

   hash_extensible hash_votante(regs,bloq_lib,tabla);
   hash_votante.imprimir("./archivos/Tests/testABM_hash_votante");

   regs = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDVOTANTE_REGS));
   bloq_lib = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDVOTANTE_BLOQ_LIB));
   tabla = ((*Configuracion::getConfig()).getValorPorPrefijo(RUTA_HASH_IDVOTANTE_TABLA));

   hash_extensible hash_idvotante(regs,bloq_lib,tabla);
   hash_idvotante.imprimir("./archivos/Tests/testABM_hash_idvotante");

   /* Recupero los valores de los votantes */
   // Debo guardar las claves para que no se cambien al cargar los registros
   string clave[cantidadVotantes];
   for(int i=0;i<cantidadVotantes;i++)	clave[i] = Utilidades::toString(vecVotantes[i].getDNI());

   for(int i=0;i<cantidadVotantes;i++) this->ConsultaEntidadesTest.ObtenerRegistro(clave[cantidadVotantes-1-i],vecVotantes[i]);

   for(int i=0;i<cantidadVotantes;i++)	vecVotantes[i].Imprimir();

	cout << endl << "********************************************************" << endl;
	cout << "                  Fin Test Alta Votantes" << endl;
	cout << "********************************************************" << endl << endl;
}


/* Se crean 21 listas (6 nombres de listas, que se presentan a varias elecciones).
 * Se guardan en archivo arbol y se recuperan al reves */
void TestABMentidades::testAltaLista() {
	cout << endl << "********************************************************" << endl;
	cout << "              Comienzo Test Alta Listas" << endl;
	cout << "********************************************************" << endl << endl;

	/* Cargo valores */
	vector<Distrito> vecDistritos;
	UtilidadesTests::cargarDistritos(vecDistritos);
	int cantidadDistritos = vecDistritos.size();

	vector<Cargo> vecCargos;
	UtilidadesTests::cargarCargos(vecCargos);
	int cantidadCargos = vecCargos.size();

	/* Guardo los distritos. Verificar que ande antes el ABMentidades::altaDistrito() (ṔOR AHORA ANDA) */
	/* Para que tenga exito, no deben existir los archivos de hash de distrito */
	bool exito = true;
	for (int i=0;i<cantidadDistritos;i++)	if (exito) exito = this->ABMtest.altaDistrito(vecDistritos[i]);
	if (!exito) {
	 	cout << "Fallo la carga de Distritos (verificar que no existan los hash de distrito)" << endl << endl;
	  	return;
	}

	/* Guardo los cargos. Verificar que ande antes el ABMentidades::altaCargo() (ṔOR AHORA ANDA) */
    /* Para que tenga exito, no deben existir los archivos de hash de cargo */
	exito = true;
	for (int i=0;i<cantidadCargos;i++)	if (exito) exito = this->ABMtest.altaCargo(vecCargos[i]);
    if (!exito) {
    	cout << "Fallo la carga de Cargos (verificar que no existan los hash de cargo)" << endl << endl;
    	return;
    }

    vector<Eleccion> vecElecciones;
    UtilidadesTests::cargarElecciones(vecElecciones,vecCargos,vecDistritos);
    int cantidadElecciones = vecElecciones.size();

	/* Guardo las elecciones. Verificar que ande antes el ABMentidades::altaEleccion() */
	/* Para que tenga exito, no debe existir el archivo de arbol de eleccion */
	exito = true;
	for (int i=0;i<cantidadElecciones;i++)	if (exito) exito = this->ABMtest.altaEleccion(vecElecciones[i]);
	if (!exito) {
	 	cout << "Fallo la carga de Elecciones (verificar que no exista el arbol de eleccion)" << endl << endl;
	  	return;
	}

    vector<Lista> vecListas;
    UtilidadesTests::cargarListas(vecListas,vecElecciones);
    int cantidadListas = vecListas.size();

	for(int i=0;i<cantidadListas;i++)	vecListas[i].Imprimir();

	for(int i=0;i<cantidadListas;i++) {
      if (ABMtest.altaLista(vecListas[i])) cout << "Alta " << vecListas[i].getNombre() << "$" << vecListas[i].getEleccion().getFecha() << " correcta" << endl;
      else cout << "Alta " << vecListas[i].getNombre() << "$" << vecListas[i].getEleccion().getFecha() << " incorrecta (ya existia)" << endl;
    }
   cout << endl;

   /* Recupero los valores de las listas */
   // Debo guardar las claves para que no se cambien al cargar los registros
   string clave[cantidadListas];
   for(int i=0;i<cantidadListas;i++) {
	   clave[i] = Utilidades::indexarFecha(vecListas[i].getEleccion().getFecha()) + "$" + vecListas[i].getEleccion().getCargo().getCargoPrincipal() + "$" + vecListas[i].getNombre();
   }

   for(int i=0;i<cantidadListas;i++) this->ConsultaEntidadesTest.ObtenerRegistro(clave[cantidadListas-1-i],vecListas[i]);

	for(int i=0;i<cantidadListas;i++)	vecListas[i].Imprimir();

	cout << endl << "********************************************************" << endl;
	cout << "                  Fin Test Alta Listas" << endl;
	cout << "********************************************************" << endl << endl;
}


/* Se crean 6 candidatos, se guardan en archivo y arbol y se recuperan en forma opuesta */
void TestABMentidades::testAltaCandidato() {
	cout << endl << "********************************************************" << endl;
	cout << "              Comienzo Test Alta Candidatos" << endl;
	cout << "********************************************************" << endl << endl;

	/* Cargo valores */
	vector<Distrito> vecDistritos;
	UtilidadesTests::cargarDistritos(vecDistritos);
	int cantidadDistritos = vecDistritos.size();

	vector<Cargo> vecCargos;
	UtilidadesTests::cargarCargos(vecCargos);
	int cantidadCargos = vecCargos.size();

	/* Guardo los distritos. Verificar que ande antes el ABMentidades::altaDistrito() (ṔOR AHORA ANDA) */
	/* Para que tenga exito, no deben existir los archivos de hash de distrito */
	bool exito = true;
	for (int i=0;i<cantidadDistritos;i++)	if (exito) exito = this->ABMtest.altaDistrito(vecDistritos[i]);
	if (!exito) {
	 	cout << "Fallo la carga de Distritos (verificar que no existan los hash de distrito)" << endl << endl;
	  	return;
	}

	/* Guardo los cargos. Verificar que ande antes el ABMentidades::altaCargo() (ṔOR AHORA ANDA) */
    /* Para que tenga exito, no deben existir los archivos de hash de cargo */
	exito = true;
	for (int i=0;i<cantidadCargos;i++)	if (exito) exito = this->ABMtest.altaCargo(vecCargos[i]);
    if (!exito) {
    	cout << "Fallo la carga de Cargos (verificar que no existan los hash de cargo)" << endl << endl;
    	return;
    }

    vector<Eleccion> vecElecciones;
    UtilidadesTests::cargarElecciones(vecElecciones,vecCargos,vecDistritos);
    int cantidadElecciones = vecElecciones.size();

	/* Guardo las elecciones. Verificar que ande antes el ABMentidades::altaEleccion() */
	/* Para que tenga exito, no debe existir el archivo de arbol de eleccion */
	exito = true;
	for (int i=0;i<cantidadElecciones;i++)	if (exito) exito = this->ABMtest.altaEleccion(vecElecciones[i]);
	if (!exito) {
	 	cout << "Fallo la carga de Elecciones (verificar que no exista el arbol de eleccion)" << endl << endl;
	  	return;
	}

    vector<Lista> vecListas;
    UtilidadesTests::cargarListas(vecListas,vecElecciones);
    int cantidadListas = vecListas.size();

	/* Guardo las listas. Verificar que ande antes el ABMentidades::altaLista() */
	/* Para que tenga exito, no debe existir el archivo de arbol de lista */
	exito = true;
	for (int i=0;i<cantidadListas;i++)	if (exito) exito = this->ABMtest.altaLista(vecListas[i]);
	if (!exito) {
	 	cout << "Fallo la carga de Listas (verificar que no exista el arbol de lista)" << endl << endl;
	  	return;
	}

    vector<Votante> vecVotantes;
    UtilidadesTests::cargarVotantes(vecVotantes,vecDistritos,vecElecciones);
    int cantidadVotantes = vecVotantes.size();

	/* Guardo los votantes. Verificar que ande antes el ABMentidades::altaVotante() */
	/* Para que tenga exito, no deben existir los archivos de hash de votante */
	exito = true;
	for (int i=0;i<cantidadVotantes;i++)	if (exito) exito = this->ABMtest.altaVotante(vecVotantes[i]);
	if (!exito) {
	 	cout << "Fallo la carga de Votantes (verificar que no existan los hash de votante)" << endl << endl;
	  	return;
	}

	vector<Candidato> vecCandidatos;
	UtilidadesTests::cargarCandidatos(vecCandidatos,vecListas,vecVotantes);
	int cantidadCandidatos = vecCandidatos.size();

	for(int i=0;i<cantidadCandidatos;i++)	vecCandidatos[i].Imprimir();

	for(int i=0;i<cantidadCandidatos;i++) {
      if (ABMtest.altaCandidato(vecCandidatos[i])) cout << "Alta " << vecCandidatos[i].getLista().getNombre() << "$" << vecCandidatos[i].getDNI() << " correcta" << endl;
      else cout << "Alta " << vecCandidatos[i].getLista().getNombre() << "$" << vecCandidatos[i].getDNI() << " incorrecta (ya existia)" << endl;
    }
   cout << endl;

   /* Recupero los valores de los candidatos */
   // Debo guardar las claves para que no se cambien al cargar los registros
   string clave[cantidadCandidatos];
   for(int i=0;i<cantidadCandidatos;i++) {
	   clave[i] = Utilidades::indexarFecha(vecCandidatos[i].getLista().getEleccion().getFecha()) + "$" + vecCandidatos[i].getLista().getEleccion().getCargo().getCargoPrincipal() + "$" + vecCandidatos[i].getLista().getNombre() + "$" + Utilidades::toString(vecCandidatos[i].getDNI());
   }

   for(int i=0;i<cantidadCandidatos;i++) this->ConsultaEntidadesTest.ObtenerRegistro(clave[cantidadCandidatos-1-i],vecCandidatos[i]);

	for(int i=0;i<cantidadCandidatos;i++)	vecCandidatos[i].Imprimir();

	cout << endl << "********************************************************" << endl;
	cout << "                  Fin Test Candidatos" << endl;
	cout << "********************************************************" << endl << endl;
}


/* Se crean 55 Conteos, se guardan en archivo y arboles y luego se usan los reportes para chequear los resultados */
void TestABMentidades::testAltaConteo() {

	cout << endl << "********************************************************" << endl;
	cout << "              Comienzo Test AgregarVoto Conteo" << endl;
	cout << "********************************************************" << endl << endl;

    vector<Cargo> vecCargos;
    UtilidadesTests::cargarCargos(vecCargos);
    int cantidadCargos = vecCargos.size();

    vector<Distrito> vecDistritos;
    UtilidadesTests::cargarDistritos(vecDistritos);
    int cantidadDistritos = vecDistritos.size();

	/* Guardo los distritos. Verificar que ande antes el ABMentidades::altaDistrito() (ṔOR AHORA ANDA) */
	/* Para que tenga exito, no deben existir los archivos de hash de distrito */
	ABMentidades ABMaux;
	bool exito = true;
	for (int i=0;i<cantidadDistritos;i++)	if (exito) exito = ABMaux.altaDistrito(vecDistritos[i]);
	if (!exito) {
	 	cout << "Fallo la carga de Distritos (verificar que no existan los hash de distrito)" << endl << endl;
	  	return;
	}

	/* Guardo los cargos. Verificar que ande antes el ABMentidades::altaCargo() (ṔOR AHORA ANDA) */
    /* Para que tenga exito, no deben existir los archivos de hash de cargo */
	exito = true;
	for (int i=0;i<cantidadCargos;i++)	if (exito) exito = ABMaux.altaCargo(vecCargos[i]);
    if (!exito) {
    	cout << "Fallo la carga de Cargos (verificar que no existan los hash de cargo)" << endl << endl;
    	return;
    }

    vector<Eleccion> vecElecciones;
    UtilidadesTests::cargarElecciones(vecElecciones, vecCargos, vecDistritos);
    int cantidadElecciones = vecElecciones.size();

	/* Guardo las elecciones. Verificar que ande antes el ABMentidades::altaEleccion() (ṔOR AHORA ANDA)*/
	/* Para que tenga exito, no debe existir el archivo de arbol de eleccion */
	exito = true;
	for (int i=0;i<cantidadElecciones;i++)	if (exito) exito = ABMaux.altaEleccion(vecElecciones[i]);
	if (!exito) {
	 	cout << "Fallo la carga de Elecciones (verificar que no exista el arbol de eleccion)" << endl << endl;
	  	return;
	}

    vector<Lista> vecListas;
    UtilidadesTests::cargarListas(vecListas, vecElecciones);
    int cantidadListas = vecListas.size();

	/* Guardo las listas. Verificar que ande antes el ABMentidades::altaLista() (ṔOR AHORA ANDA) */
	/* Para que tenga exito, no debe existir el archivo de arbol de lista */
	exito = true;
	for (int i=0;i<cantidadListas;i++)	if (exito) exito = ABMaux.altaLista(vecListas[i]);
	if (!exito) {
	 	cout << "Fallo la carga de Listas (verificar que no exista el arbol de lista)" << endl << endl;
	  	return;
	}

	vector<Conteo> vecConteos;
	UtilidadesTests::cargarConteos(vecConteos, vecListas, vecDistritos);
	int cantidadConteos = vecConteos.size();

	for(int i=0;i<cantidadConteos;i++)	this->ABMtest.agregarVoto(vecConteos[i].getLista(),vecConteos[i].getDistrito());

// ACA SE LLAMA A LOS IMPRIMIR_REPORTES PARA CHEQUEAR LA CANTIDAD DE VOTOS

	cout << endl << "********************************************************" << endl;
	cout << "                  Fin Test AgregarVoto Conteo" << endl;
	cout << "********************************************************" << endl << endl;
}


///////////////////////////////////////////////////



void TestABMentidades::testBajaDistrito() {
	cout << endl << "********************************************************" << endl;
	cout << "            Comienzo Test Baja Distritos" << endl;
	cout << "********************************************************" << endl << endl;

	vector<Distrito> vecDistritos;

	UtilidadesTests::cargarDistritos(vecDistritos);
	int cantidadDistritos = vecDistritos.size();

	//doy de alta los distritos
    for(int i=0;i<cantidadDistritos;i++) {
        if (ABMtest.altaDistrito(vecDistritos[i])) cout << "Alta "<<vecDistritos[i].getNombre()<<" correcta" << endl;
        else cout << "Alta "<<vecDistritos[i].getNombre()<<" incorrecta (ya existia)" << endl;
    }
    cout << endl;

    //los doy de baja
    for(int i=0;i<cantidadDistritos;i++) {
            if (ABMtest.bajaDistrito(vecDistritos[i])) cout << "Baja "<<vecDistritos[i].getNombre()<<" correcta" << endl;
            else cout << "Baja "<<vecDistritos[i].getNombre()<<" incorrecta" << endl;
    }
    cout << endl;

    //trato de obtenerlos para confirmar que se hayan borrado
     string clave[cantidadDistritos];
     	for(int i=0;i<cantidadDistritos;i++)	clave[i] = vecDistritos[i].getNombre();

     for(int i=0;i<cantidadDistritos;i++)
    	 if(this->ConsultaEntidadesTest.ObtenerRegistro(clave[i],vecDistritos[i])) cout <<"error en bajas distrito";
     cout << endl;

 	cout << endl << "********************************************************" << endl;
 	cout << "                Fin Test Baja Distritos" << endl;
 	cout << "********************************************************" << endl << endl;
}

void TestABMentidades::testBajaCargo() {
	cout << endl << "********************************************************" << endl;
	cout << "            Comienzo Test Baja Cargos" << endl;
	cout << "********************************************************" << endl << endl;

	vector<Cargo> vecCargos;

	UtilidadesTests::cargarCargos(vecCargos);
	int cantidadCargos = vecCargos.size();

	//doy de alta los cargos
    for(int i=0;i<cantidadCargos;i++) {
        if (ABMtest.altaCargo(vecCargos[i])) cout << "Alta " << vecCargos[i].getCargoPrincipal() << " correcta" << endl;
        else cout << "Alta " << vecCargos[i].getCargoPrincipal() << " incorrecta (ya existia)" << endl;
    }
    cout << endl;

	//doy de baja los cargos
    for(int i=0;i<cantidadCargos;i++) {
        if (ABMtest.bajaCargo(vecCargos[i])) cout << "Baja " << vecCargos[i].getCargoPrincipal() << " correcta" << endl;
        else cout << "Baja " << vecCargos[i].getCargoPrincipal() << " incorrecta (ya existia)" << endl;
    }
    cout << endl;

    //trato de obtenerlos para confirmar que se hayan borrado
    string clave[cantidadCargos];
    for(int i=0;i<cantidadCargos;i++)	clave[i] = vecCargos[i].getCargoPrincipal();

    for(int i=0;i<cantidadCargos;i++) this->ConsultaEntidadesTest.ObtenerRegistro(clave[i],vecCargos[i]);


	cout << endl << "********************************************************" << endl;
	cout << "                Fin Test Baja Cargos" << endl;
	cout << "********************************************************" << endl << endl;
}
