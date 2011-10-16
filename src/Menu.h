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

using namespace std;

class Menu {

public:
	void mostrarAyuda();

	void pedir_usuario();

	void pedir_contrasena();

	bool acceder_admin();

	bool acceder_usuario();

	bool loggin();

	void admin_main();

	void admin_distritos();

	void admin_votante();

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
