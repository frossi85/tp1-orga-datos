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
