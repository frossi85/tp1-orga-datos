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

//VER COMO HACER UNA FUCION TEMPLATE SIN Q LA CLASE LO SEA
//template <class T>
//inline std::string to_string (const T& t)
//{
//	std::stringstream ss;
//	ss << t;
//	return ss.str();
//}

void stringToFile(std::string & str, std::ofstream & ofs)
{
	int size = str.size();

	ofs.write(reinterpret_cast<char *>(&size), sizeof(size));
	ofs.write(str.c_str(), sizeof(char) * size);
}

std::string stringFromFile(std::ifstream & ifs)
{
	int size = 0;
	char buffer[500]; //MAX_STRING_BUFFER

	ifs.read(reinterpret_cast<char *>(&size), sizeof(size));
	ifs.read(buffer, sizeof(char) * size);

	string nombre(buffer);	//Por lo que probe el constructor copia le pone el "\0";

	return nombre;
}
