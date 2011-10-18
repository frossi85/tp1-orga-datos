/*
 * menu.h
 *
 *  Created on: Oct 1, 2011
 *      Author: pablo
 */

#ifndef MENU_H_
#define MENU_H_

#include <string.h>
#include "MenuVotante.h"
#include "ABM Entidades/ABMentidades.h"
#include "ABM Entidades/ConsultaEntidades.h"

using namespace std;

class Menu {

public:
	void mostrarAyuda();

	void pedirUsuario();

	void pedirContrasena();

	bool accesoAdmin();

	bool accesoUsuario();

	bool loggin();

	void adminMain();

	void adminDistrito();

	void adminVotante();

	void adminCargo();

public:
	static Menu *getMenu();

private:
	string user;
	string pass;
	string salir;

	Menu();

	virtual ~Menu();

};

#endif /* MENU_H_ */
