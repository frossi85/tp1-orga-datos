/*
 * menu.h
 *
 *  Created on: Oct 1, 2011
 *      Author: pablo
 */

#ifndef MENU_H_
#define MENU_H_

#include <string.h>

using namespace std;

class Menu {

public:
	void mostrar_ayuda();

	void pedir_usuario();

	void pedir_contrasena();

	bool acceder_admin();

	bool acceder_usuario();

	void admin_main();

	void admin_distritos();

	void admin_votante();

public:
	static Menu *getMenu();

private:
	char user[20];
	char pass[20];
	char salir[6];

	Menu();

	virtual ~Menu();

};

#endif /* MENU_H_ */
