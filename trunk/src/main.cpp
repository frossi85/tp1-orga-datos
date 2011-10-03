#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstdlib>

#include "menu.h"

using namespace std;

void mostrar_ayuda();
string pedir_usuario();
string pedir_contrasena();
bool confirmar_usuario(int,string, string);

int main(int argc, char *argv[]){
	Menu *menu = Menu::getMenu();
	if (argc != 2){
		// Numero incorrecto de parametros
		cout << "Uso: voto_electronico -h\n";
		return 0;
	}

	if ( !(strcmp(argv[1],"-h")) || !(strcmp(argv[1],"--help")) ) {
		// La funcionalidad deseada es acceder a la ayuda del programa.
		menu->mostrar_ayuda();
		return 0;
	}

	if ( !(strcmp(argv[1],"-a")) || !(strcmp(argv[1],"--admin")) ) {

		cout << "Ingreso como administrador. \n(para salir ingrese \"salir\" en alguno de los campos) \n";
		// La funcionalidad deseada es acceder como administrador
		// Se pide y verifica usuario y contraseña
		do {
			menu->pedir_usuario();
			menu->pedir_contrasena();
		} while (!menu->acceder_admin());

		return 0;
	}
	if ( !(strcmp(argv[1],"-u")) || !(strcmp(argv[1],"--user")) ) {

		cout << "Ingreso como usuario. \n(para salir ingrese \"salir\" en alguno de los campos) \n";
		// La funcionalidad deseada es acceder como usuario
		// Se pide y verifica usuario y contraseña
		do {
			menu->pedir_usuario();
			menu->pedir_contrasena();
		} while (!menu->acceder_usuario());

		return 0;
	}

	cout << "Uso: voto_electronico -h\n";   // Mal uso de las opciones

	return 0;
}

