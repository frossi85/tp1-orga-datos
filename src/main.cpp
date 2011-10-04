#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstdlib>

#include "menu.h"
#include "Distrito.h"
#include "Cargo.h"
#include "DataAccess.h"

using namespace std;

void mostrar_ayuda();
string pedir_usuario();
string pedir_contrasena();
bool confirmar_usuario(int,string, string);

int main(int argc, char *argv[]){

	///CODIGO DE PRUEBA FACUNDO
	DataAccess dataAccess;

	Distrito distrito("Lanus");
	distrito.setId(45);

	dataAccess.Guardar(distrito);

	Distrito distrito2;

	dataAccess.getPorId(0, distrito2);

	dataAccess.Eliminar(distrito2);

	Cargo cargo("Presidente");
	cargo.setId(20);
	cargo.agregarCargoSecundario("Vice Presidente");
	cargo.agregarCargoSecundario("Gobernador");
	cargo.agregarCargoSecundario("Intendente");
	cargo.agregarCargoSecundario("Consejal");

	dataAccess.Guardar(cargo);

	Cargo cargo2;
	dataAccess.getPorId(0, cargo2);


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

