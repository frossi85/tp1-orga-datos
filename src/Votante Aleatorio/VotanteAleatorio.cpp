/*
 * VotanteAleatorio.cpp
 *
 *  Created on: 08/10/2011
 *      Author: martin
 */

#include "VotanteAleatorio.h"
using namespace std;

VotanteAleatorio::VotanteAleatorio(unsigned int cantidad) {
	this->cantidad = cantidad;
	this->accesos = 0;
	this->votos = 0;
	vectorVotantes = new Votante*[cantidad];
	srand(time(NULL));
	unsigned int DNI = rand();		// genero un DNI cualquiera para usar de semilla
	string nombre, apellido, clave, domicilio;
	Distrito *distrito;

	/* Cargo los votantes aleatoreamente */
	for(unsigned int i=0; i<cantidad; i++){
		DNI = Utilidades::getDNIaleatorio(DNI);		// Utilizo el DNI anterior como semilla
		nombre = getStringAleatorio();
		apellido = getStringAleatorio();
		clave = getStringAleatorio();
		domicilio = getStringAleatorio();
		apellido[apellido.find_first_of('\0')] = ' ';
		apellido = apellido + nombre;
		distrito = new Distrito(getDistritoAleatorio());   		//Cargar Distrito aleatorio
		vectorVotantes[i] = new Votante(DNI,apellido,clave,domicilio,*distrito);
		delete distrito;
	}
}

VotanteAleatorio::~VotanteAleatorio() {
	for(unsigned int i=0; i<cantidad; i++)	delete vectorVotantes[i];
		delete[] vectorVotantes;
}


int VotanteAleatorio::hacerlosAccederAlSistema() {
	unsigned int randomNumber;
	int contadorFallidos = 0;
	for(unsigned int i=0;i<cantidad;i++) {
		randomNumber = (rand() % 20);	// Numero entre 0 y 19
		if (randomNumber == 19) {		// Probabilidad 1/20 de que falle el acceso
			simularAcceso(this->vectorVotantes[i]->getDNI(),this->vectorVotantes[i]->getClave(),false);
			contadorFallidos++;
		}
			else simularAcceso(this->vectorVotantes[i]->getDNI(),this->vectorVotantes[i]->getClave(),true);
	}
	return contadorFallidos;
}


int VotanteAleatorio::hacerlosVotar() {
	unsigned int randomNumber;
	int contadorModificacionVoto = 0;
	int cantidadElecciones = 0;
	vector<Eleccion*> elecciones;
	for(unsigned int i=0;i<cantidad;i++) {
		elecciones = this->vectorVotantes[i]->getElecciones();
		cantidadElecciones = elecciones.size();
		for(int j = 0;j<cantidadElecciones;j++) {
			randomNumber = (rand() % 20);						// Numero entre 0 y 19
			if (randomNumber == 19) {
				simularVotacion(i,elecciones[j],false);			// Modificacion de voto
				contadorModificacionVoto++;
			}
				else simularVotacion(i,elecciones[j],true);
			delete elecciones[j];						// ESTA BIEN ESTE DELETE?
		}
	}
	return contadorModificacionVoto;
}

/* Busca aleatoreamente un nombre en una base de datos de nombres y lo retorna.
 * Aunque en la base de datos hay "nombres", se puede usar esta funcion para
 * retornar un string y asignarselo a un apellido, clave o domicilio y asi ahorrarse
 * de tener bases de datos adicionales para estos campos, ya que esto es solamente una prueba
 * para el programa.
 */
string VotanteAleatorio::getStringAleatorio() {
	string cadena_retorno = "ERROR";
	string filename;
	FILE* archivo;

	unsigned int opcion = (rand() % 11) + 1;
	switch (opcion){
	case 1: {
		filename = URL_NOMBRES_AB;
		break;
	}
	case 2: {
		filename = URL_NOMBRES_CD;
		break;
	}
	case 3: {
		filename = URL_NOMBRES_EF;
		break;
	}
	case 4: {
		filename = URL_NOMBRES_GH;
		break;
	}
	case 5: {
		filename = URL_NOMBRES_IJ;
		break;
	}
	case 6: {
		filename = URL_NOMBRES_KL;
		break;
	}
	case 7: {
		filename = URL_NOMBRES_MN;
		break;
	}
	case 8: {
		filename = URL_NOMBRES_OP;
		break;
	}
	case 9: {
		filename = URL_NOMBRES_QRS;
		break;
	}
	case 10: {
		filename = URL_NOMBRES_TUV;
		break;
	}
	case 11: {
		filename = URL_NOMBRES_WXYZ;
		break;
	}
	default: {
		cout<<endl<<"No abrio ningun archivo de nombres."<<endl;
		return cadena_retorno;
	}
	}

	/*Abro el archivo y aleatoreamente elijo un nombre*/
	archivo = fopen(filename.c_str(),"r");
	if (archivo == NULL) {
		cout<<endl<<"Error al abrir archivo"<<endl;
		return cadena_retorno;
	}
	char aux[4];								// *********************************************
	char* nombre = new char[20]; 				//	Parseo la cantidad de nombres en ese archivo
	fgets(aux,4,archivo);						//
	unsigned int cantidadNombres = atoi(aux);	// **********************************************
	opcion = (rand() % cantidadNombres)+1;					// Elijo una posicion de nombre aleatoria
	for(unsigned int i=0;i<opcion;i++) fgets(nombre,20,archivo);		// Recorro el archivo hasta la cadena que debo levantar
	cadena_retorno = nombre;								// Obtengo la cadena a retornar
	cadena_retorno[cadena_retorno.find_first_of('\n')] = '\0';

	/* Cierre de archivo*/
	if (archivo) {
		fclose(archivo);
		archivo = NULL;
	}
	delete[] nombre;
	return cadena_retorno;
}


void VotanteAleatorio::Imprimir(){
	for(unsigned int i=0;i<cantidad;i++) {
		cout << "\nVotante "<<i<<":\n";
		vectorVotantes[i]->Imprimir();
	}

}


Distrito VotanteAleatorio::getDistritoAleatorio() {
	Distrito distrito(this->getStringAleatorio());
	return distrito;			//HARDCODEO
}

/* Si esCorrecto es true, se simula que se accede correctamente. Si es false, se simula que pone mal la contraseña una vez y luego bien */
void VotanteAleatorio::simularAcceso(unsigned int DNI,string clave,bool esCorrecto) {
	this->accesos++;
}

/* Si esCorrecto es true, se simula que vota sin modificacion. Si es false, se simula que modifica el voto 1 vez */
void VotanteAleatorio::simularVotacion(int indice,Eleccion* eleccion,bool esCorrecto) {
	this->votos++;
}
