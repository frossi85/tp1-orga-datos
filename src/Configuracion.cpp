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

Configuracion::Configuracion() {
	constantes[0]=RUTA_VOTANTES;
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
		if (constantes[i]==RUTA_VOTANTES) {
			return valores[i];
		}
	}
	return NULL;
}

