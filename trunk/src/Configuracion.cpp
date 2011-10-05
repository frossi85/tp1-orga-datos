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

const string Configuracion::URL_VOTANTES = "<ruta_votantes>";
const string Configuracion::URL_DISTRITOS = "<ruta_distritos>";
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
	FILE *fp;
	char cadena[100];
	char *c,*conv;
	int i;
	fp = fopen("config.ini", "r");
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

