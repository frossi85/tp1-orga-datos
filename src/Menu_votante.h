/*
 * Menu_votante.h
 *
 *  Created on: 07/10/2011
 *      Author: Miguel Torres
 */

#ifndef MENU_VOTANTE_H_
#define MENU_VOTANTE_H_
#include <iostream>
#include <cstdlib>
#include "Votante.h"
#include "Eleccion.h"
#include "Lista.h"

using namespace std;

class Menu_votante {
private:

	Votante *votante;

	Votante* getVotante();

	/*
	 * Muestra el Menu Princiapal de Votante
	 */
	void opciones();

	void mostrar_menu_elecciones();
	Eleccion* elegir_eleccion();
	void mostrar_menu_datos();
	void mostrar_listas_a_votar(Eleccion *eleccion);

	/*
	 * Confirma la votacion devolviendo TRUE si se confirma la
	 * Lista a votar.
	 */
	bool confirmar_votacion(Eleccion *eleccion,Lista *lista);
	Lista* elegir_Lista(Eleccion *eleccion);

	/*
	 * Guarda los cambios de los datos del Votante modificados
	 */
	void guardar_cambios();


	void cambiar_clave();
	void cambiar_domicilio();

public:
	Menu_votante(Votante *votante);

	virtual ~Menu_votante();
};

#endif /* MENU_VOTANTE_H_ */
