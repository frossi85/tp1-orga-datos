/*
 * Configuracion.cpp
 *
 *  Created on: 19/09/2011
 *      Author: facundo
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Configuracion.h"
using namespace std;

const string Configuracion::URL_VOTANTES = "<ruta_votante>";
const string Configuracion::URL_DISTRITOS = "<ruta_distrito>";
const string Configuracion::URL_ELECCION = "<ruta_eleccion>";
const string Configuracion::URL_LISTA = "<ruta_lista>";
const string Configuracion::URL_CONTEO = "<ruta_conteo>";
const string Configuracion::URL_CANDIDATO = "<ruta_candidato>";
const string Configuracion::URL_CARGO = "<ruta_cargo>";
const string Configuracion::URL_ADMINISTRADOR = "<ruta_administrador>";


Configuracion::Configuracion() {
	constantes[0]=RUTA_VOTANTES;
	constantes[1]=RUTA_DISTRITOS;
	constantes[2]=RUTA_ELECCION;
	constantes[3]=RUTA_LISTA;
	constantes[4]=RUTA_CONTEO;
	constantes[5]=RUTA_CANDIDATO;
	constantes[6]=RUTA_CARGO;
	constantes[7]=RUTA_ADMINISTRADOR;
	constantes[8]=RUTA_HASH_ELECCION_REGS;
	constantes[9]=RUTA_HASH_ELECCION_BLOQ_LIB;
	constantes[10]=RUTA_HASH_ELECCION_TABLA;
	constantes[11]=RUTA_HASH_DISTRITO_REGS;
	constantes[12]=RUTA_HASH_DISTRITO_BLOQ_LIB;
	constantes[13]=RUTA_HASH_DISTRITO_TABLA;
	constantes[14]=RUTA_HASH_CARGO_REGS;
	constantes[15]=RUTA_HASH_CARGO_BLOQ_LIB;
	constantes[16]=RUTA_HASH_CARGO_TABLA;
	constantes[17]=RUTA_HASH_LISTA_REGS;
	constantes[18]=RUTA_HASH_LISTA_BLOQ_LIB;
	constantes[19]=RUTA_HASH_LISTA_TABLA;
	constantes[20]=RUTA_HASH_CANDIDATO_REGS;
	constantes[21]=RUTA_HASH_CANDIDATO_BLOQ_LIB;
	constantes[22]=RUTA_HASH_CANDIDATO_TABLA;
	constantes[23]=RUTA_HASH_VOTANTE_REGS;
	constantes[24]=RUTA_HASH_VOTANTE_BLOQ_LIB;
	constantes[25]=RUTA_HASH_VOTANTE_TABLA;

	FILE *fp;
	char cadena[100];
	char *c,*conv;
	int i;
	fp = fopen("./config.ini", "r");
	do {
		c = fgets(cadena, 100, fp);
		if (c != NULL) {
			for (i=0;i<20;i++){
				if (cadena[i]=='\n'){
					cadena[i]='\0';
				}
			}
			for (i=0; i<CANT_CONF;i++) {
				conv=&constantes[i][0];
				if (strcmp(cadena,conv)==0) {
					c = fgets(cadena, 100, fp);
					valores[i]=string(cadena);
				}
			}
		}
	} while (c != NULL);
	fclose(fp);

}

Configuracion::~Configuracion() {
}

Configuracion *Configuracion::getConfig() {
	 static Configuracion instance;
	 return &instance;
}


string Configuracion::getValorPorPrefijo(string prefijo)
{
	int i;
	for(i=0;i<CANT_CONF; i++)
	{
		if (constantes[i]==prefijo) {
			return valores[i];
		}
	}
	return NULL;
}

