/*
 * ArbolBmas.cpp
 *
 *  Created on: 02/10/2011
 *      Author: martin
 */

#include "ArbolBmas.h"

ArbolBmas::ArbolBmas(unsigned int longitudID) {
	/*
	 * La cuenta es: Tamaño nodo = 4 * sizeof(unsigned int) + #RegistrosArbol * (sizeof(longitudID) + sizeof(offset))
	 */
	if (sizeof(longitudID) <= 12) this->longitudID = 12;
		else if (sizeof(longitudID) <= 27) this->longitudID = 27;
			else if (sizeof(longitudID) <= 58) this->longitudID = 58;
				else if (sizeof(longitudID) <= 80) this->longitudID = 80;
					else if (sizeof(longitudID) <= 108) this->longitudID = 108;
						else if (sizeof(longitudID) <= 164) this->longitudID = 164;
							else if (sizeof(longitudID) <= 250) this->longitudID = 250;

}

ArbolBmas::~ArbolBmas() {
	// TODO Auto-generated destructor stub
}
unsigned int ArbolBmas::calcularMaxCantidadRegistrosEnNodo(){
	switch (sizeof(longitudID)){
		/*
		 * Nodos de 512 bytes
		 */
		case 16:{
			maxCantidadRegistrosNodo = 31;
			break;
		}
		case 31:{
			maxCantidadRegistrosNodo = 16;
			break;
		}
		case 62:{
			maxCantidadRegistrosNodo = 8;
			break;
		}
		/*
		 * Nodos de 1024 bytes
		 */
		case 84:{
			maxCantidadRegistrosNodo = 12;
			break;
		}
		case 112:{
			maxCantidadRegistrosNodo = 9;
			break;
		}
		case 168:{
			maxCantidadRegistrosNodo = 6;
			break;
		}
		/*
		 * Nodos de 2048 bytes
		 */
		case 254:{
			maxCantidadRegistrosNodo = 8;
			break;
		}
	}
}
