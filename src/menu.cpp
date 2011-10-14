/*
 * Menu.cpp
 *
 *  Created on: Oct 1, 2011
 *      Author: pablo
 */

#include "menu.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include "DataAccess.h"
#include "DataGetter.h"
using namespace std;

Menu::Menu() {
	salir[0]='s';
	salir[1]='a';
	salir[2]='l';
	salir[3]='i';
	salir[4]='r';
}

Menu *Menu::getMenu() {
	 static Menu instance;
	 return &instance;
}

void Menu::mostrar_ayuda() {
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
	char userOk[20]="tp";
	char passOk[20]="tp";

	if ( (strncmp(user,userOk,20)==0) && (strncmp(pass,passOk,20)==0) ) {
		cout<< "Accedio al sistema." << endl;
		admin_main();
		return true;
	} else {
		if ( (strncmp(user,salir,5)==0) || (strncmp(pass,salir,5)==0) ) {
			cout << "Eligio terminar el programa." << endl;
			return true;
		} else {
			cout << "Los datos ingresados no coinciden." << endl;
			return false;
		}
	}
}

bool Menu::acceder_usuario() {
	//char userOk[20]="1111";
	//char passOk[20]="1111";

	DataAccess data_access;
	Votante *votante=DataGetter::getVotante(user);

	if ((votante!=NULL) && (strncmp(votante->getClave().c_str(),pass,20)==0))
	//if ( (strncmp(user,userOk,20)==0) && (strncmp(pass,passOk,20)==0) )
	{
		cout<< "Accedio al sistema." << endl;

		//Se LLama al menu del Votante

		Menu_votante menu_vot(votante);

		return true;
	} else {
		if ( (strncmp(user,salir,5)==0) || (strncmp(pass,salir,5)==0) ) {
			cout << "Eligio terminar el programa." << endl;
			return true;
		} else {
			cout << "Los datos ingresados no coinciden." << endl;
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
		switch (opcion) {
		case 'd':
		case 'D':
			admin_distritos();
			retorno=true;
			break;
		case 'v':
		case 'V':
			admin_votante();
			retorno=true;
			break;
		case 's':
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
		cout << "A => Crear un nuevo Distrito." << endl;
		cout << "B => Borrar un Distrito existente." << endl;
		cout << "M => Modificar un Distrito existente." << endl;
		cout << "V => Volver." << endl << "Opcion: ";
		cin >> opcion;

		retorno=false;
		invalida=false;
		switch (opcion) {
		case 'a':
		case 'A':
			cout << endl <<endl;
			cout << "Ingrese el nombre del nuevo ditrito: ";
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
		case 'b':
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
		case 'm':
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
		case 'v':
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
		cout << "A => Crear un nuevo Votante." << endl;
		cout << "B => Borrar un Votante existente." << endl;
		cout << "M => Modificar un Votante existente." << endl;
		cout << "V => Volver." << endl << "Opcion: ";
		cin >> opcion;

		retorno=false;
		invalida=false;
		switch (opcion) {
		case 'a':
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
		case 'b':
		case 'B':
			dniN= -2;
			do {
				if (dniN!=-2) {
					cout << "El DNI ingresado es invalido. para salir ingrese salir" << endl;
				}
				cout << "Ingrese el DNI del Votante a borrar: ";
				cin >> dni;
				dniN = atoi(dni);
			} while (( (dniN<5000000) || (dniN>100000000) ) && (strncmp(dni,salir,5)!=0));

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
		case 'm':
		case 'M':
			dniN= -2;
			do {
				if (dniN!=-2) {
					cout << "El DNI ingresado es invalido. para salir ingrese salir" << endl;
				}
				cout << "Ingrese el DNI: del Votante a modificar: ";
				cin >> dni;
				dniN = atoi(dni);
			} while (( (dniN<5000000) || (dniN>100000000) ) && (strncmp(dni,salir,5)!=0));

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
					switch (opcion) {
					case 'n':
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
					case 'o':
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
					case 'd':
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
					case 'i':
					case 'I':
						dniN= -2;
						do {
							if (dniN!=-2) {
								cout << "El DNI ingresado es invalido. para salir ingrese salir" << endl;
							}
							cout << "Ingrese el DNI: del Votante a modificar: ";
							cin >> dni;
							dniN = atoi(dni);
						} while (( (dniN<5000000) || (dniN>100000000) ) && (strncmp(dni,salir,5)!=0));

						resultado_v= 0;//modificarVotante('dni',dniN);
						if (resultado_v==0) {
							cout << "Se modifico el Votante \"" << nombre << "\"." << endl;
						} else {
							cout << "Error al modificar al Votante. Codigo: " << resultado << endl;
						}
						break;
					case 'v':
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
		case 'v':
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
	// TODO Auto-generated destructor stub
}
