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

	for(int i=0;i<6;i++)	vecDistritos[i].Imprimir();

    for(int i=0;i<6;i++) {
        if (ABMtest.altaDistrito(vecDistritos[i])) cout << "Alta "<<vecDistritos[i].getNombre()<<" correcta" << endl;
        else cout << "Alta "<<vecDistritos[i].getNombre()<<" incorrecta (ya existia)" << endl;
    }
    cout << endl;


    /* Pido que se impriman archivos de texto del hash para control */
    string regs((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_distrito_regs>"));
    string bloq_lib((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_distrito_bloq_lib>"));
    string tabla((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_distrito_tabla>"));

    hash_extensible hash_distrito(regs,bloq_lib,tabla);
    hash_distrito.imprimir("./archivos/Tests/testABM_hash_distrito");

    regs = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_iddistrito_regs>"));
    bloq_lib = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_iddistrito_bloq_lib>"));
    tabla = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_iddistrito_tabla>"));

    hash_extensible hash_iddistrito(regs,bloq_lib,tabla);
    hash_iddistrito.imprimir("./archivos/Tests/testABM_hash_iddistrito");

    /* Recupero los valores de distritos */
    // Debo guardar las claves para que no se cambien al cargar los registros
	string clave[6];
	for(int i=0;i<6;i++)	clave[i] = vecDistritos[i].getNombre();

    for(int i=0;i<6;i++)	this->ConsultaEntidadesTest.ObtenerRegistro(clave[5-i],vecDistritos[i]);

	for(int i=0;i<6;i++)	vecDistritos[i].Imprimir();


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

	for(int i=0;i<6;i++)	vecCargos[i].Imprimir();

    for(int i=0;i<6;i++) {
        if (ABMtest.altaCargo(vecCargos[i])) cout << "Alta " << vecCargos[i].getCargoPrincipal() << " correcta" << endl;
        else cout << "Alta " << vecCargos[i].getCargoPrincipal() << " incorrecta (ya existia)" << endl;
    }
    cout << endl;


    /* Pido que se impriman archivos de texto del hash para control */
    string regs((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_cargo_regs>"));
    string bloq_lib((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_cargo_bloq_lib>"));
    string tabla((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_cargo_tabla>"));

    hash_extensible hash_cargo(regs,bloq_lib,tabla);
    hash_cargo.imprimir("./archivos/Tests/testABM_hash_cargo");

    regs = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_idcargo_regs>"));
    bloq_lib = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_idcargo_bloq_lib>"));
    tabla = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_idcargo_tabla>"));

    hash_extensible hash_idcargo(regs,bloq_lib,tabla);
    hash_idcargo.imprimir("./archivos/Tests/testABM_hash_idcargo");

    /* Recupero los valores de cargos */
    // Debo guardar las claves para que no se cambien al cargar los registros
    string clave[6];
	for(int i=0;i<6;i++)	clave[i] = vecCargos[i].getCargoPrincipal();

	for(int i=0;i<6;i++) this->ConsultaEntidadesTest.ObtenerRegistro(clave[5-i],vecCargos[i]);

	for(int i=0;i<6;i++)	vecCargos[i].Imprimir();


	cout << endl << "********************************************************" << endl;
	cout << "                Fin Test Alta Cargos" << endl;
	cout << "********************************************************" << endl << endl;
}


/* Se crean 6 Elecciones, con "i+1" distritos donde se realiza la votacion (i es indice de eleccion).
 * Se guardan en archivo y hash y se recuperan en forma opuesta */
void TestABMentidades::testAltaEleccion() {
	cout << endl << "********************************************************" << endl;
	cout << "                Comienzo Test Alta Eleccion" << endl;
	cout << "********************************************************" << endl << endl;

	 vector<Distrito> vecDistritos;
	 vector<Cargo> vecCargos;

	 UtilidadesTests::cargarDistritos(vecDistritos);
	 UtilidadesTests::cargarCargos(vecCargos);


    /* Guardo los distritos. Verificar que ande antes el ABMentidades::altaDistrito() (ṔOR AHORA ANDA) */
	/* Para que tenga exito, no deben existir los archivos de hash de distrito */
    bool exito = true;
    for (int i=0;i<6;i++)	if (exito) exito = this->ABMtest.altaDistrito(vecDistritos[i]);
    if (!exito) {
    	cout << "Fallo la carga de Distritos (verificar que no exitan los hash de distrito)" << endl << endl;
    	return;
    }

	/* Guardo los cargos. Verificar que ande antes el ABMentidades::altaCargo() (ṔOR AHORA ANDA) */
    /* Para que tenga exito, no deben existir los archivos de hash de cargo */
	exito = true;
	for (int i=0;i<6;i++)	if (exito) exito = this->ABMtest.altaCargo(vecCargos[i]);
    if (!exito) {
    	cout << "Fallo la carga de Cargos (verificar que no exitan los hash de cargo)" << endl << endl;
    	return;
    }

	vector<Eleccion> vecElecciones;

	UtilidadesTests::cargarElecciones(vecElecciones,vecCargos,vecDistritos);

	for(int i=0;i<6;i++) {
		vecElecciones[i].Imprimir();
		vecElecciones[i].ImprimirDistritos();
	}

	 for(int i=0;i<6;i++) {
        if (ABMtest.altaEleccion(vecElecciones[i])) cout << "Alta " << vecElecciones[i].getFecha() << " correcta" << endl;
        else cout << "Alta " << vecElecciones[i].getFecha() << " incorrecta (ya existia)" << endl;
    }
    cout << endl;

    /* Pido que se impriman archivos de texto del hash para control */
    string regs((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_eleccion_regs>"));
    string bloq_lib((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_eleccion_bloq_lib>"));
    string tabla((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_eleccion_tabla>"));

    hash_extensible hash_eleccion(regs,bloq_lib,tabla);
    hash_eleccion.imprimir("./archivos/Tests/testABM_hash_eleccion");

    regs = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_ideleccion_regs>"));
    bloq_lib = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_ideleccion_bloq_lib>"));
    tabla = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_ideleccion_tabla>"));

    hash_extensible hash_ideleccion(regs,bloq_lib,tabla);
    hash_ideleccion.imprimir("./archivos/Tests/testABM_hash_ideleccion");

    /* Recupero los valores de elecciones */
    // Debo guardar las claves para que no se cambien al cargar los registros
    string clave[6];
 	for(int i=0;i<6;i++)	{
 		clave[i] = Utilidades::indexarFecha(vecElecciones[i].getFecha()) + "$" + vecElecciones[i].getCargo().getCargoPrincipal();
 	}

   	for(int i=0;i<6;i++) this->ConsultaEntidadesTest.ObtenerRegistro(clave[5-i],vecElecciones[i]);

	for(int i=0;i<6;i++) {
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

	vector<Cargo> vecCargos;
	UtilidadesTests::cargarCargos(vecCargos);

	/* Guardo los distritos. Verificar que ande antes el ABMentidades::altaDistrito() (ṔOR AHORA ANDA) */
	/* Para que tenga exito, no deben existir los archivos de hash de distrito */
	bool exito = true;
	for (int i=0;i<6;i++)	if (exito) exito = this->ABMtest.altaDistrito(vecDistritos[i]);
	if (!exito) {
	 	cout << "Fallo la carga de Distritos (verificar que no exitan los hash de distrito)" << endl << endl;
	  	return;
	}

	/* Guardo los cargos. Verificar que ande antes el ABMentidades::altaCargo() (ṔOR AHORA ANDA) */
    /* Para que tenga exito, no deben existir los archivos de hash de cargo */
	exito = true;
	for (int i=0;i<6;i++)	if (exito) exito = this->ABMtest.altaCargo(vecCargos[i]);
    if (!exito) {
    	cout << "Fallo la carga de Cargos (verificar que no exitan los hash de cargo)" << endl << endl;
    	return;
    }

    vector<Eleccion> vecElecciones;
    UtilidadesTests::cargarElecciones(vecElecciones,vecCargos,vecDistritos);

	/* Guardo las elecciones. Verificar que ande antes el ABMentidades::altaEleccion() */
	/* Para que tenga exito, no deben existir los archivos de hash de eleccion */
	exito = true;
	for (int i=0;i<6;i++)	if (exito) exito = this->ABMtest.altaEleccion(vecElecciones[i]);
	if (!exito) {
	 	cout << "Fallo la carga de Elecciones (verificar que no exitan los hash de eleccion)" << endl << endl;
	  	return;
	}

    vector<Votante> vecVotantes;
    UtilidadesTests::cargarVotantes(vecVotantes,vecDistritos,vecElecciones);

	for(int i=0;i<9;i++)	vecVotantes[i].Imprimir();

	for(int i=0;i<9;i++) {
      if (ABMtest.altaVotante(vecVotantes[i])) cout << "Alta " << vecVotantes[i].getDNI() << " correcta" << endl;
      else cout << "Alta " << vecVotantes[i].getDNI() << " incorrecta (ya existia)" << endl;
   }
   cout << endl;

   /* Pido que se impriman archivos de texto del hash para control */
   string regs((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_votante_regs>"));
   string bloq_lib((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_votante_bloq_lib>"));
   string tabla((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_votante_tabla>"));

   hash_extensible hash_votante(regs,bloq_lib,tabla);
   hash_votante.imprimir("./archivos/Tests/testABM_hash_votante");

   regs = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_idvotante_regs>"));
   bloq_lib = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_idvotante_bloq_lib>"));
   tabla = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_idvotante_tabla>"));

   hash_extensible hash_idvotante(regs,bloq_lib,tabla);
   hash_idvotante.imprimir("./archivos/Tests/testABM_hash_idvotante");

   /* Recupero los valores de los votantes */
   // Debo guardar las claves para que no se cambien al cargar los registros
   string clave[9];
   for(int i=0;i<9;i++)	clave[i] = Utilidades::toString(vecVotantes[i].getDNI());

   for(int i=0;i<9;i++) this->ConsultaEntidadesTest.ObtenerRegistro(clave[8-i],vecVotantes[i]);

   for(int i=0;i<9;i++)	vecVotantes[i].Imprimir();

	cout << endl << "********************************************************" << endl;
	cout << "                  Fin Test Alta Votantes" << endl;
	cout << "********************************************************" << endl << endl;
}


/* Se crean 21 listas (6 nombres de listas, que se presentan a varias elecciones).
 * Se guardan en archivo y se recuperan al reves */
void TestABMentidades::testAltaLista() {
	cout << endl << "********************************************************" << endl;
	cout << "              Comienzo Test Alta Listas" << endl;
	cout << "********************************************************" << endl << endl;

	/* Cargo valores */
	vector<Distrito> vecDistritos;
	UtilidadesTests::cargarDistritos(vecDistritos);

	vector<Cargo> vecCargos;
	UtilidadesTests::cargarCargos(vecCargos);

	/* Guardo los distritos. Verificar que ande antes el ABMentidades::altaDistrito() (ṔOR AHORA ANDA) */
	/* Para que tenga exito, no deben existir los archivos de hash de distrito */
	bool exito = true;
	for (int i=0;i<6;i++)	if (exito) exito = this->ABMtest.altaDistrito(vecDistritos[i]);
	if (!exito) {
	 	cout << "Fallo la carga de Distritos (verificar que no exitan los hash de distrito)" << endl << endl;
	  	return;
	}

	/* Guardo los cargos. Verificar que ande antes el ABMentidades::altaCargo() (ṔOR AHORA ANDA) */
    /* Para que tenga exito, no deben existir los archivos de hash de cargo */
	exito = true;
	for (int i=0;i<6;i++)	if (exito) exito = this->ABMtest.altaCargo(vecCargos[i]);
    if (!exito) {
    	cout << "Fallo la carga de Cargos (verificar que no exitan los hash de cargo)" << endl << endl;
    	return;
    }

    vector<Eleccion> vecElecciones;
    UtilidadesTests::cargarElecciones(vecElecciones,vecCargos,vecDistritos);

	/* Guardo las elecciones. Verificar que ande antes el ABMentidades::altaEleccion() */
	/* Para que tenga exito, no deben existir los archivos de hash de eleccion */
	exito = true;
	for (int i=0;i<6;i++)	if (exito) exito = this->ABMtest.altaEleccion(vecElecciones[i]);
	if (!exito) {
	 	cout << "Fallo la carga de Elecciones (verificar que no exitan los hash de eleccion)" << endl << endl;
	  	return;
	}

    vector<Lista> vecListas;
    UtilidadesTests::cargarListas(vecListas,vecElecciones);

	for(int i=0;i<21;i++)	vecListas[i].Imprimir();

	for(int i=0;i<21;i++) {
      if (ABMtest.altaLista(vecListas[i])) cout << "Alta " << vecListas[i].getNombre() << "$" << vecListas[i].getEleccion().getFecha() << " correcta" << endl;
      else cout << "Alta " << vecListas[i].getNombre() << "$" << vecListas[i].getEleccion().getFecha() << " incorrecta (ya existia)" << endl;
    }
   cout << endl;

   /* Pido que se impriman archivos de texto del hash para control */
   string regs((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_lista_regs>"));
   string bloq_lib((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_lista_bloq_lib>"));
   string tabla((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_lista_tabla>"));

   hash_extensible hash_lista(regs,bloq_lib,tabla);
   hash_lista.imprimir("./archivos/Tests/testABM_hash_lista");

   regs = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_idlista_regs>"));
   bloq_lib = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_idlista_bloq_lib>"));
   tabla = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_idlista_tabla>"));

   hash_extensible hash_idlista(regs,bloq_lib,tabla);
   hash_idlista.imprimir("./archivos/Tests/testABM_hash_idlista");

   /* Recupero los valores de los candidatos */
   // Debo guardar las claves para que no se cambien al cargar los registros
   string clave[21];
   for(int i=0;i<21;i++) {
	   clave[i] = Utilidades::indexarFecha(vecListas[i].getEleccion().getFecha()) + "$" + vecListas[i].getEleccion().getCargo().getCargoPrincipal() + "$" + vecListas[i].getNombre();
   }

   for(int i=0;i<21;i++) this->ConsultaEntidadesTest.ObtenerRegistro(clave[20-i],vecListas[i]);

	for(int i=0;i<21;i++)	vecListas[i].Imprimir();

	cout << endl << "********************************************************" << endl;
	cout << "                  Fin Test Alta Listas" << endl;
	cout << "********************************************************" << endl << endl;
}


/* Se crean 6 candidatos, se guardan en archivo y hash y se recuperan en forma opuesta */
void TestABMentidades::testAltaCandidato() {
	cout << endl << "********************************************************" << endl;
	cout << "              Comienzo Test Alta Candidatos" << endl;
	cout << "********************************************************" << endl << endl;

	/* Cargo valores */
	vector<Distrito> vecDistritos;
	UtilidadesTests::cargarDistritos(vecDistritos);

	vector<Cargo> vecCargos;
	UtilidadesTests::cargarCargos(vecCargos);

	/* Guardo los distritos. Verificar que ande antes el ABMentidades::altaDistrito() (ṔOR AHORA ANDA) */
	/* Para que tenga exito, no deben existir los archivos de hash de distrito */
	bool exito = true;
	for (int i=0;i<6;i++)	if (exito) exito = this->ABMtest.altaDistrito(vecDistritos[i]);
	if (!exito) {
	 	cout << "Fallo la carga de Distritos (verificar que no exitan los hash de distrito)" << endl << endl;
	  	return;
	}

	/* Guardo los cargos. Verificar que ande antes el ABMentidades::altaCargo() (ṔOR AHORA ANDA) */
    /* Para que tenga exito, no deben existir los archivos de hash de cargo */
	exito = true;
	for (int i=0;i<6;i++)	if (exito) exito = this->ABMtest.altaCargo(vecCargos[i]);
    if (!exito) {
    	cout << "Fallo la carga de Cargos (verificar que no exitan los hash de cargo)" << endl << endl;
    	return;
    }

    vector<Eleccion> vecElecciones;
    UtilidadesTests::cargarElecciones(vecElecciones,vecCargos,vecDistritos);

	/* Guardo las elecciones. Verificar que ande antes el ABMentidades::altaEleccion() */
	/* Para que tenga exito, no deben existir los archivos de hash de eleccion */
	exito = true;
	for (int i=0;i<6;i++)	if (exito) exito = this->ABMtest.altaEleccion(vecElecciones[i]);
	if (!exito) {
	 	cout << "Fallo la carga de Elecciones (verificar que no exitan los hash de eleccion)" << endl << endl;
	  	return;
	}

    vector<Lista> vecListas;
    UtilidadesTests::cargarListas(vecListas,vecElecciones);

	/* Guardo las listas. Verificar que ande antes el ABMentidades::altaLista() */
	/* Para que tenga exito, no deben existir los archivos de hash de lista */
	exito = true;
	for (int i=0;i<21;i++)	if (exito) exito = this->ABMtest.altaLista(vecListas[i]);
	if (!exito) {
	 	cout << "Fallo la carga de Listas (verificar que no exitan los hash de lista)" << endl << endl;
	  	return;
	}

    vector<Votante> vecVotantes;
    UtilidadesTests::cargarVotantes(vecVotantes,vecDistritos,vecElecciones);

	/* Guardo los votantes. Verificar que ande antes el ABMentidades::altaVotante() */
	/* Para que tenga exito, no deben existir los archivos de hash de votante */
	exito = true;
	for (int i=0;i<9;i++)	if (exito) exito = this->ABMtest.altaVotante(vecVotantes[i]);
	if (!exito) {
	 	cout << "Fallo la carga de Votantes (verificar que no exitan los hash de votante)" << endl << endl;
	  	return;
	}

	vector<Candidato> vecCandidatos;
	UtilidadesTests::cargarCandidatos(vecCandidatos,vecListas,vecVotantes);

	for(int i=0;i<6;i++)	vecCandidatos[i].Imprimir();

	for(int i=0;i<6;i++) {
      if (ABMtest.altaCandidato(vecCandidatos[i])) cout << "Alta " << vecCandidatos[i].getLista().getNombre() << "$" << vecCandidatos[i].getDNI() << " correcta" << endl;
      else cout << "Alta " << vecCandidatos[i].getLista().getNombre() << "$" << vecCandidatos[i].getDNI() << " incorrecta (ya existia)" << endl;
    }
   cout << endl;

   /* Pido que se impriman archivos de texto del hash para control */
   string regs((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_candidato_regs>"));
   string bloq_lib((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_candidato_bloq_lib>"));
   string tabla((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_candidato_tabla>"));

   hash_extensible hash_candidato(regs,bloq_lib,tabla);
   hash_candidato.imprimir("./archivos/Tests/testABM_hash_candidato");

   regs = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_idcandidato_regs>"));
   bloq_lib = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_idcandidato_bloq_lib>"));
   tabla = ((*Configuracion::getConfig()).getValorPorPrefijo("<ruta_hash_idcandidato_tabla>"));

   hash_extensible hash_idcandidato(regs,bloq_lib,tabla);
   hash_idcandidato.imprimir("./archivos/Tests/testABM_hash_idcandidato");

   /* Recupero los valores de los candidatos */
   // Debo guardar las claves para que no se cambien al cargar los registros
   string clave[6];
   for(int i=0;i<6;i++) {
	   clave[i] = Utilidades::indexarFecha(vecCandidatos[i].getLista().getEleccion().getFecha()) + "$" + vecCandidatos[i].getLista().getEleccion().getCargo().getCargoPrincipal() + "$" + vecCandidatos[i].getLista().getNombre() + "$" + Utilidades::toString(vecCandidatos[i].getDNI());
   }

   for(int i=0;i<6;i++) this->ConsultaEntidadesTest.ObtenerRegistro(clave[5-i],vecCandidatos[i]);

	for(int i=0;i<6;i++)	vecCandidatos[i].Imprimir();

	cout << endl << "********************************************************" << endl;
	cout << "                  Fin Test Candidatos" << endl;
	cout << "********************************************************" << endl << endl;
}
