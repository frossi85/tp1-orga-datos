/*
 * VotanteAleatorio.h
 *
 *  Created on: 08/10/2011
 *      Author: martin
 */

#ifndef VOTANTEALEATORIO_H_
#define VOTANTEALEATORIO_H_

/* Verificar Rutas */
#define URL_NOMBRES_AB "./Nombres/NombresAB.txt"
#define URL_NOMBRES_CD "./Nombres/NombresCD.txt"
#define URL_NOMBRES_EF "./Nombres/NombresEF.txt"
#define URL_NOMBRES_GH "./Nombres/NombresGH.txt"
#define URL_NOMBRES_IJ "./Nombres/NombresIJ.txt"
#define URL_NOMBRES_KL "./Nombres/NombresKL.txt"
#define URL_NOMBRES_MN "./Nombres/NombresMN.txt"
#define URL_NOMBRES_OP "./Nombres/NombresOP.txt"
#define URL_NOMBRES_QRS "./Nombres/NombresQRS.txt"
#define URL_NOMBRES_TUV "./Nombres/NombresTUV.txt"
#define URL_NOMBRES_WXYZ "./Nombres/NombresWXYZ.txt"

#include "../Votante.h"
#include "../Utilidades.h"
#include "../Distrito.h"
#include "../Eleccion.h"
#include "../Lista.h"
#include "../Conteo.h"
#include "../Logger.h"
#include "../CargaInicial.h"
#include <stdlib.h>
#include <time.h>
#include <string>
#include <stdio.h>
#include <vector>
#include "../DataGetter.h"
#include "../ABMEntidades/ABMentidades.h"

using namespace std;

class VotanteAleatorio {
public:
	VotanteAleatorio(unsigned int cantidad);
	virtual ~VotanteAleatorio();
	void Imprimir();
	unsigned int getAccesos() {return this->accesos;}
	unsigned int getVotos() {return this->votos;}
	int hacerlosAccederAlSistema();
	int hacerlosVotar();

	static void ejecutar();

private:
	Votante **vectorVotantes;
	unsigned int cantidad;
	unsigned int accesos;		// Cantidad de accesos de votantes al sistema (no cuenta accesos fallidos)
	unsigned int votos;			// Cantidad de votos totales (si en una eleccion se cambia de voto X veces, cuenta como 1 solo voto)
	string getStringAleatorio();
	Distrito getDistritoAleatorio();
	void simularAcceso(unsigned int DNI,string clave,bool);
	void simularVotacion(int indice,Eleccion* eleccion,bool esCorrecto);

};

#endif /* VOTANTEALEATORIO_H_ */
