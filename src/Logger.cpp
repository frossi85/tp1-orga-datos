/*
 * Logger.cpp
 *
 *  Created on: 19/09/2011
 *      Author: facundo
 */

#include "Logger.h"

void Logger::logAccion(Logueable & obj, string accion) {
	string tipoEntidad = obj.getClassName();

	//TODO : Levantar del archivo de configuracion la ubicacion del archivo en donde voy a loguear
	string urlArchivoLog = "./log.txt";
	string log;
	ofstream archivoLog(urlArchivoLog.c_str(), ios::app); //Ver si debo abrirlo solo en modo escritura

	if(!archivoLog.is_open())
		throw VotoElectronicoExcepcion("No se pudo abrir el archivo de log" + urlArchivoLog);

	log =  "[" + Utilidades::getFechaYHora() + "]"+ ": " + obj.getClassName() + " - " + accion;

	archivoLog<<log;
	archivoLog<<endl;
}

void Logger::Alta(Logueable & obj) {
	logAccion(obj, "Alta");
}

void Logger::Eliminar(Logueable & obj) {
	logAccion(obj, "Eliminación");
}

void Logger::Modificacion(Logueable & obj) {
	logAccion(obj, "Modificación");
}

//void Logger::CambioDeVoto(Votante &votante)
//{
//	logAccion(votante, "El votante de dni " + votante.getDNI() + " cambio su voto");
//}
//
//void Logger::ConfirmacionDeVoto(Votante &votante)
//{
//	logAccion(votante, "El votante de dni " + votante.getDNI() + " confirmo su voto");
//}
//
//void Logger::Voto(Votante &votante)
//{
//	logAccion(votante, "El votante de dni " + votante.getDNI() + "  voto");
//}

