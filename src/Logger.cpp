/*
 * Logger.cpp
 *
 *  Created on: 19/09/2011
 *      Author: facundo
 */

#include "Logger.h"

Logger::Logger() {
	// TODO Auto-generated constructor stub

}

Logger::~Logger() {
	// TODO Auto-generated destructor stub
}

void Logger::logAccion(Logueable obj, string accion) {
	string tipoEntidad = obj.getClassName();

	//TODO : Levantar del archivo de configuracion la ubicacion del archivo en donde voy a loguear
	string urlArchivoLog = "./log.txt";
	string log;
	ofstream archivoLog("./log.txt", ios::app); //Ver si debo abrirlo solo en modo escritura

	//TODO : Ver de reemplazarlo por otro tipo de excepcion??
	if(!archivoLog)
		throw VotoElectronicoExcepcion("No se pudo abrir el archivo de log" + urlArchivoLog);

	log =  "[" + Utilidades::getFechaYHora() + "]"+ ": " + accion + " - " + obj.getClassName();
}

void Logger::Alta(Logueable obj) {
	logAccion(obj, "Alta");
}

void Logger::Baja(Logueable obj) {
	logAccion(obj, "Baja");
}

void Logger::Modificacion(Logueable obj) {
	logAccion(obj, "Modificación");
}


