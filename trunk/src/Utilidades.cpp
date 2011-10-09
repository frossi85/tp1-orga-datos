/*
 * Utilidades.cpp
 *
 *  Created on: 21/09/2011
 *      Author: facundo
 */

#include "Utilidades.h"

Utilidades::Utilidades() {
	// TODO Auto-generated constructor stub

}

Utilidades::~Utilidades() {
	// TODO Auto-generated destructor stub
}


//TODO: No se por q me da una hora mas a lo q dice mi PC
string Utilidades::getFechaYHora()
{
	// current date/time based on current system
	   time_t now = time(0);
	   tm *ltm = localtime(&now);

	   string year = toString(1900 + ltm->tm_year);
	   string month = toString(1 + ltm->tm_mon);
	   string day = toString(ltm->tm_mday);
	   string time = toString(1 + ltm->tm_hour) + ":" + toString(1 + ltm->tm_min) + ":" + toString(1 + ltm->tm_sec);

	   return time + " - " + day + "-" + month + "-" + year;
}

string Utilidades::toString(int a)
{
	stringstream ss;
	ss << a;
	return ss.str();
}

/* Retorna un DNI entre 1.000.000 y 39.999.999*/
unsigned int Utilidades::getDNIaleatorio(int semilla) {
	srand(semilla);
	unsigned int unidad = rand() % 10;
	unsigned int decena = (rand() % 10) * 10;
	unsigned int centena = (rand() % 10) * 100;
	unsigned int u_de_mil = (rand() % 10) * 1000;
	unsigned int d_de_mil = (rand() % 10) * 10000;
	unsigned int c_de_mil = (rand() % 10) * 100000;
	unsigned int d_de_millon = (rand() % 4) * 10000000;
	unsigned int u_de_millon;
	if (d_de_millon == 0) u_de_millon = 1000000;
		else u_de_millon =  (rand() % 10) * 1000000;
	return (unidad+decena+centena+u_de_mil+d_de_mil+c_de_mil+u_de_millon+d_de_millon);
}

//VER COMO HACER UNA FUCION TEMPLATE SIN Q LA CLASE LO SEA
//template <class T>
//inline std::string to_string (const T& t)
//{
//	std::stringstream ss;
//	ss << t;
//	return ss.str();
//}

void Utilidades::stringToFile(std::string & str, std::ofstream & ofs)
{
	int size = str.size();

	ofs.write(reinterpret_cast<char *>(&size), sizeof(size));
	ofs.write(str.c_str(), sizeof(char) * size);
}

string Utilidades::stringFromFile(std::ifstream & ifs)
{
	int size = 0;
	char buffer[500]; //MAX_STRING_BUFFER

	ifs.read(reinterpret_cast<char *>(&size), sizeof(size));
	ifs.read(buffer, sizeof(char) * size);

	buffer[size] = '\0';
	string nombre(buffer);	//Por lo que probe el constructor copia le pone el "\0";

	return nombre;
}
