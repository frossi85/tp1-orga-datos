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
	vectorVotantes = new Votante*[cantidad];
	srand(time(NULL));
	unsigned int DNI = rand();		// genero un DNI cualquiera para usar de semilla
	string nombre, apellido, clave, domicilio;
	//Distrito distrito();

	/* Cargo los votantes aleatoreamente */
	for(int i=0; i<cantidad; i++){
		DNI = Utilidades::getDNIaleatorio(DNI);	// Utilizo el DNI anterior como semilla
		nombre = getStringAleatorio();
		apellido = getStringAleatorio();
		clave = getStringAleatorio();
		domicilio = getStringAleatorio();
		apellido[apellido.find_first_of('\0')] = ' ';
		apellido = apellido + nombre;
		// distrito = getDistritoAleatorio()   //Cargar Distrito aleatorio
		vectorVotantes[i] = new Votante(DNI,apellido,clave,domicilio/*,distrito*/);
	}
}

VotanteAleatorio::~VotanteAleatorio() {
	for(int i=0; i<cantidad; i++)	delete vectorVotantes[i];
		delete[] vectorVotantes;
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
		filename = "src/Nombres/NombresAB.txt";
		break;
	}
	case 2: {
		filename = "src/Nombres/NombresCD.txt";
		break;
	}
	case 3: {
		filename = "src/Nombres/NombresEF.txt";
		break;
	}
	case 4: {
		filename = "src/Nombres/NombresGH.txt";
		break;
	}
	case 5: {
		filename = "src/Nombres/NombresIJ.txt";
		break;
	}
	case 6: {
		filename = "src/Nombres/NombresKL.txt";
		break;
	}
	case 7: {
		filename = "src/Nombres/NombresMN.txt";
		break;
	}
	case 8: {
		filename = "src/Nombres/NombresOP.txt";
		break;
	}
	case 9: {
		filename = "src/Nombres/NombresQRS.txt";
		break;
	}
	case 10: {
		filename = "src/Nombres/NombresTUV.txt";
		break;
	}
	case 11: {
		filename = "src/Nombres/NombresWXYZ.txt";
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
	for(int i=0;i<opcion;i++) fgets(nombre,20,archivo);		// Recorro el archivo hasta la cadena que debo levantar
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
	for(int i=0;i<cantidad;i++) {
		cout << "\nVotante "<<i<<":\n";
		vectorVotantes[i]->Imprimir();
	}

}
