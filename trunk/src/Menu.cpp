/*
 * Menu.cpp
 *
 *  Created on: Oct 1, 2011
 *      Author: pablo
 */

#include "Menu.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <cctype>
#include "DataAccess.h"
#include "DataGetter.h"
using namespace std;

Menu::Menu() {
	salir = "salir";
}

Menu *Menu::getMenu() {
	 static Menu instance;
	 return &instance;
}

void Menu::mostrarAyuda() {
    cout << "*************************************************************\n";
    cout << "Voto Electronico - Ayuda\n\n" << "Opciones:\n";
    cout << "-h, --help: Muestra esta ayuda\n";
    cout << "-u, --user: Login al sistema en calidad de usuario\n";
    cout << "-a, --admin: Login al sistema en calidad de administrador\n\n";
    cout << "Consulte el manual para mas informacion\n";
    cout << "*************************************************************\n";
}

void Menu::pedir_usuario() {
    cout<<("Usuario: ");
    cin >> user;
}

void Menu::pedir_contrasena() {
	cout<<("Contraseña: ");
	system("stty -echo");
	cin >> pass;
	system("stty echo");
}

bool Menu::acceder_admin() {
	//Administrator admin = DataGet::getAdministrator();

	string userOk="tp"; //admin.getUser();
	string passOk="tp"; //admin.getPassword();

	if ( user == userOk && pass == passOk ) {
		cout<< "Accedio al sistema." << endl;
		admin_main();
		return true;
	} else {
		if ( user == salir || pass == salir) {
			cout << "Eligio terminar el programa." << endl;
			return true;
		} else {
			cout << "El usuario o la contraseña son invalidos." << endl;
			return false;
		}
	}
}

bool Menu::acceder_usuario() {
	DataAccess data_access;
	Votante *votante= DataGetter::getVotante(user);

	if ((votante!=NULL) && (votante->getClave() == pass))
	{
		cout<< "Accedio al sistema." << endl;

		//Se LLama al menu del Votante

		MenuVotante menuVotante(votante);

		return true;
	} else {
		if ( user == salir || pass == salir ) {
			cout << "Eligio terminar el programa." << endl;
			return true;
		} else {
			cout << "El usuario o la contraseña son invalidos." << endl;
			return false;
		}
	}
}

void Menu::admin_main() {
	char opcion;


	bool invalida=false;
	bool retorno=false;
	do {
		system("clear");
		if (invalida) {
			cout << "Opcion invalida, intente nuevamente." << endl;
		}
		cout << "********************************" << endl;
		cout << "D => Mantenimiento de Distritos." << endl;
		cout << "V => Mantenimiento de Votantes." << endl;
		cout << "E => Mantenimiento de Elecciones." << endl;
		cout << "C => Mantenimiento de Cargos." << endl;
		cout << "L => Mantenimiento de Listas." << endl;
		cout << "A => Mantenimiento de Candidatos." << endl;
		cout << "R => Mantenimiento de Resultados." << endl;
		cout << "S => Salir." << endl << "Opcion: ";
		cin >> opcion;

		retorno=false;
		invalida=false;
		switch ((char)toupper(opcion)) {
		case 'D':
			admin_distritos();
			retorno=true;
			break;
		case 'V':
			admin_votante();
			retorno=true;
			break;
		case 'S':
			system("clear");
			break;
		default:
			invalida=true;
			break;
		}

	} while ((invalida) || (retorno));
}

void Menu::admin_distritos() {
	char opcion;
	bool invalida=false;
	bool retorno=false;
	char nombre[50];
	int resultado;
	do {
		system("clear");
		if (invalida) {
			cout << "Opcion invalida, intente nuevamente." << endl;
		}
		cout << "********************************" << endl;
		cout << "A => Crear un Distrito." << endl;
		cout << "B => Borrar un Distrito." << endl;
		cout << "M => Modificar un Distrito." << endl;
		cout << "V => Volver." << endl << "Opcion: ";
		cin >> opcion;

		retorno=false;
		invalida=false;
		switch ((char)toupper(opcion)) {
		case 'A':
			cout << endl <<endl;
			cout << "Ingrese el nombre del ditrito: ";
			cin >> nombre;

			//aqui
			resultado= 0;//creaDistrito(nombre);
			if (resultado==0) {
				cout << "Se creo el Distrito \"" << nombre << "\"." << endl;
			} else {
				cout << "Error al crear al distrito. Codigo: " << resultado << endl;
			}
			cout << "Ingrese cualquier letra para continuar: ";
			cin >> opcion;
			retorno=true;
			break;
		case 'B':
			cout << endl <<endl;
			cout << "Ingrese el nombre del ditrito a borrar: ";
			cin >> nombre;

			//aqui
			resultado= 0;//borraDistrito(nombre);
			if (resultado==0) {
				cout << "Se borro el Distrito \"" << nombre << "\"." << endl;
			} else {
				cout << "No se encontro el Distrito \"" << nombre << "\"." << endl;
			}
			cout << "Ingrese cualquier letra para continuar: ";
			cin >> opcion;
			retorno=true;
			break;
		case 'M':
			cout << endl <<endl;
			cout << "Ingrese el nombre del ditrito a modificar: ";
			cin >> nombre;

			//aqui
			resultado= 1;//buscarDistrito(nombre);
			if (resultado>0) {
				cout << "Distrito encontrado." << endl;
				cout << "ingrese el nuevo nombre del distrito: ";
				cin >> nombre;

				int resultado= 0;//modificarDistrito(nombre);
				if (resultado==0) {
					cout << "Se modifico el Distrito \"" << nombre << "\"." << endl;
				} else {
					cout << "Error al crear al distrito. Codigo: " << resultado << endl;
				}

			} else {
				cout << "No se encontro el Distrito \"" << nombre << "\"." << endl;
			}
			cout << "Ingrese cualquier letra para continuar: ";
			cin >> opcion;
			retorno=true;
			break;
		case 'V':
			system("clear");
			break;
		default:
			invalida=true;
			break;
		}

	} while ((invalida) || (retorno));
}

void Menu::admin_votante() {
	char opcion;
	bool invalida=false;
	bool retorno=false;
	char nombre[50], direccion[50], dni[50];
	int resultado;
	do {
		system("clear");
		if (invalida) {
			cout << "Opcion invalida, intente nuevamente." << endl;
		}
		cout << "********************************" << endl;
		cout << "A => Crear un Votante." << endl;
		cout << "B => Borrar un Votante." << endl;
		cout << "M => Modificar un Votante." << endl;
		cout << "V => Volver." << endl << "Opcion: ";
		cin >> opcion;

		retorno=false;
		invalida=false;
		switch ((char)toupper(opcion)) {
		case 'A':
			cout << endl <<endl; //((DNI)i, NombreyApellido, clave, domicilio, (distrito)ie, ((eleccion)ie)*)
			cout << "Ingrese el nombre y apellido del nuevo Votante: ";
			cin >> nombre;
			cout << "Ingrese el domicilio: ";
			cin >> direccion;
			int dniN;
			dniN= -2;
			do {
				if (dniN!=-2) {
					cout << "El DNI ingresado es invalido." << endl;
				}
				cout << "Ingrese el DNI: ";
				cin >> dni;
				dniN = atoi(dni);
			} while ( (dniN<5000000) || (dniN>100000000) );

			//aqui
			resultado= 0;//creaDistrito(nombre);
			if (resultado==0) {
				cout << "Se agrego al Votante \"" << dni << "\"." << endl;
			} else {
				cout << "Error al crear al Votante. Codigo: " << resultado << endl;
			}
			cout << "Ingrese cualquier letra para continuar: ";
			cin >> opcion;
			retorno=true;
			break;
		case 'B':
			dniN= -2;
			do {
				if (dniN!=-2) {
					cout << "El DNI ingresado es invalido. para salir ingrese salir" << endl;
				}
				cout << "Ingrese el DNI del Votante a borrar: ";
				cin >> dni;
				dniN = atoi(dni);
			} while (( (dniN<5000000) || (dniN>100000000) ) && dni != salir);

			//aqui
			resultado= 0;//borraVotante(dniN);
			if (resultado==0) {
				cout << "Se borro el Votante \"" << nombre << "\"." << endl;
			} else {
				cout << "No se encontro el Votante \"" << nombre << "\"." << endl;
			}
			cout << "Ingrese cualquier letra para continuar: ";
			cin >> opcion;
			retorno=true;
			break;
		case 'M':
			dniN= -2;
			do {
				if (dniN!=-2) {
					cout << "El DNI ingresado es invalido. para salir ingrese salir" << endl;
				}
				cout << "Ingrese el DNI: del Votante a modificar: ";
				cin >> dni;
				dniN = atoi(dni);
			} while (( (dniN<5000000) || (dniN>100000000) ) && dni != salir);

			//aqui
			resultado= 1;//buscarDistrito(nombre);
			if (resultado>0) {
				bool invalida_v=false;
				do {
					system("clear");
					if (invalida_v) {
						cout << "Opcion invalida, intente nuevamente." << endl;
					}
					cout << "********************************" << endl;
					cout << "N => Modificar el nombre." << endl;
					cout << "O => Modificar el domicilio." << endl;
					cout << "D => Modificar el distrito." << endl;
					cout << "I => Modificar el DNI." << endl;
					cout << "V => Volver." << endl << "Opcion: ";
					cin >> opcion;

					int resultado_v;
					invalida_v=false;
					switch ((char)toupper(opcion)) {
					case 'N':
						cout << "ingrese el nuevo nombre del Votante: ";
						cin >> nombre;

						resultado_v= 0;//modificarVotante('nombre',nombre);
						if (resultado_v==0) {
							cout << "Se modifico el Votante \"" << nombre << "\"." << endl;
						} else {
							cout << "Error al modificar al Votante. Codigo: " << resultado << endl;
						}
						break;
					case 'O':
						cout << "ingrese el nuevo domicilio del Votante: ";
						cin >> nombre;

						resultado_v= 0;//modificarVotante('domicilio',nombre);
						if (resultado_v==0) {
							cout << "Se modifico el domicilio \"" << nombre << "\"." << endl;
						} else {
							cout << "Error al modificar al Votante. Codigo: " << resultado << endl;
						}
						break;
					case 'D':
						cout << "ingrese el nombre del nuevo distrito del Votante: ";
						cin >> nombre;

						resultado_v= 0;//modificarVotante('distiro',nombre);
						if (resultado_v==0) {
							cout << "Se modifico el Votante al distrito \"" << nombre << "\"." << endl;
						} else {
							cout << "Error al modificar al Votante. Codigo: " << resultado << endl; // no se encontro distrito
						}
						break;
					case 'I':
						dniN= -2;
						do {
							if (dniN!=-2) {
								cout << "El DNI ingresado es invalido. para salir ingrese salir" << endl;
							}
							cout << "Ingrese el DNI: del Votante a modificar: ";
							cin >> dni;
							dniN = atoi(dni);
						} while (( (dniN<5000000) || (dniN>100000000) ) && dni != salir,5);

						resultado_v= 0;//modificarVotante('dni',dniN);
						if (resultado_v==0) {
							cout << "Se modifico el Votante \"" << nombre << "\"." << endl;
						} else {
							cout << "Error al modificar al Votante. Codigo: " << resultado << endl;
						}
						break;
					case 'V':
						break;
					default:
						invalida_v=true;
						break;
					}

				} while (invalida_v);
			} else {
				cout << "No se encontro el Votante \"" << nombre << "\"." << endl;
			}
			cout << "Ingrese cualquier letra para continuar: ";
			cin >> opcion;
			retorno=true;
			break;
		case 'V':
			system("clear");
			break;
		default:
			invalida=true;
			break;
		}

	} while ((invalida) || (retorno));
}

Menu::~Menu() {
}
