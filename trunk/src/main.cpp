#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <cstdlib>

#include "Menu.h"
#include "CargaInicial.h"
#include "VotanteAleatorio/VotanteAleatorio.h"
#include "./ABMEntidades/ConsultaEntidades.h"
#include "./Eleccion.h"


using namespace std;

int main(int argc, char *argv[]){

	try{
		Menu *menu = Menu::getMenu();
		if (argc != 2){
			// Numero incorrecto de parametros
			cout << "Uso: voto_electronico -h\n";
			return 0;
		}

		//Esta declaracion va aca ya que si no corroboro q argc es 2, va a lanzar una excepcion
		//el constructor
		string argumento(argv[1]);

		if ( argumento == "-h" || argumento == "--help" ) {
			// La funcionalidad deseada es acceder a la ayuda del programa.
			menu->mostrarAyuda();
			return 0;
		}

		if ( argumento == "-a" || argumento== "--admin" ) {
			cout << "Ingreso como administrador. \n(para salir ingrese \"salir\" en alguno de los campos) \n";
			// La funcionalidad deseada es acceder como administrador
			// Se pide y verifica usuario y contraseña
			do {
				menu->pedirUsuario();
				menu->pedirContrasena();
			} while (!menu->accesoAdmin());

			return 0;
		}
		else
		{
			if ( argumento == "-u" || argumento == "--user" )
			{
				cout << "Ingreso como usuario. \n(para salir ingrese \"salir\" en alguno de los campos) \n";
				// La funcionalidad deseada es acceder como usuario
				// Se pide y verifica usuario y contraseña
				do {
					menu->pedirUsuario();
					menu->pedirContrasena();
				} while (!menu->accesoUsuario());

				return 0;
			}
		}

		cout << "Uso: voto_electronico -h\n";   // Mal uso de las opciones
	}
	catch(string str) {
		cout << endl << endl << "*********************************************************************************************************";
		cout << endl << str << endl;
		cout << "*********************************************************************************************************";
	}
	return 0;
}
