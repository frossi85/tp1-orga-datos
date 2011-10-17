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
#include "ABM Entidades/ABMentidades.h"
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

void Menu::pedirUsuario() {
    cout<<"Usuario: ";
    cin >> user;
}

void Menu::pedirContrasena() {
	cout<<"Contraseña: ";
	system("stty -echo");
	cin >> pass;
	system("stty echo");
}

bool Menu::accesoAdmin() {
	//Administrator admin = DataGet::getAdministrator();

	string userOk="tp"; //admin.getUser();
	string passOk="tp"; //admin.getPassword();

	if ( user == userOk && pass == passOk ) {
		cout<< "Accedio al sistema." << endl;
		adminMain();
		return true;
	} else {
		if ( user == salir || pass == salir) {
			cout <<endl<< "Eligio terminar el programa." << endl;
			return true;
		} else {
			cout << "El usuario o la contraseña son invalidos." << endl;
			return false;
		}
	}
}

bool Menu::accesoUsuario() {
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

void Menu::adminMain() {
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
			adminDistrito();
			retorno=true;
			break;
		case 'V':
			adminVotante();
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

void Menu::adminDistrito() {
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

void Menu::adminVotante() {
    char opcion;
    bool invalida=false;
    bool retorno=false;
    char nombre[50], direccion[50], dni[50];
    string nombreDistrito;
    Votante votante;
    Distrito distrito;
    ConsultaEntidades consulta;
    ABMentidades abm;

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
        opcion = (char)toupper(opcion);
        switch (opcion) {
            case 'A':
                    cout << endl <<endl; //((DNI)i, NombreyApellido, clave, domicilio, (distrito)ie, ((eleccion)ie)*)
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

                    cout << "Ingrese el nombre y apellido del nuevo Votante: ";
                    cin >> nombre;
                    cout << "Ingrese el domicilio: ";
                    cin >> direccion;
                    cout << "ingrese el nombre del distrito del Votante: ";
                    cin >> nombreDistrito;

                    //Se verifica si existe el distrito
                    if(consulta.ObtenerRegistro(nombreDistrito, distrito))
                        votante.setDistrito(distrito);
                    else
                        cout << "No existe el distrito" << resultado << endl; // no se encontro distrito

                    //Se crea el votante, verificando si no existia
                    if(abm.altaVotante(votante))
                        cout << "Se creo el Votante \"" << nombre << "\"." << endl;
                    else
                        cout << "El votante ya existe o se produjo un error al crearlo." << endl;

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

                    if(!(consulta.ObtenerRegistro(dni, votante)))
                    {
                        cout<<"El votante no existe"<<endl;
                        resultado = -1;
                        break;
                    }
                    if(abm.bajaVotante(votante))
                        cout << "Se borro el Votante \"" << nombre << "\"." << endl;
                    else
                        cout<< "No se ha podido borrar al votante." << endl;
                    
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
                    cout << "Ingrese el DNI del Votante a modificar: ";
                    cin >> dni;
                    dniN = atoi(dni);
                } while (( (dniN<5000000) || (dniN>100000000) ) && dni != salir);

                if(!(consulta.ObtenerRegistro(dni, votante)))
                {
                    cout<<"El votante no existe"<<endl;
                    resultado = -1;
                    break;
                }
                resultado= 1;
                if (resultado>0) {
                    bool invalida_v=false;
                    do {
                        system("clear");
                        if (invalida_v) {
                            cout << "Opcion invalida, intente nuevamente." << endl;
                        }
                        cout << "********************************" << endl;
                        cout << "O => Modificar el domicilio." << endl;
                        cout << "D => Modificar el distrito." << endl;
                        cout << "V => Volver." << endl << "Opcion: ";
                        cin >> opcion;

                        int resultado_v;
                        invalida_v=false;
                        switch ((char)toupper(opcion)) {
                        case 'O':
                            cout << "ingrese el nuevo domicilio del Votante: ";
                            cin >> nombre;

                            votante.setDomicilio(nombre);
                            break;
                        case 'D':
                            cout << "ingrese el nombre del nuevo distrito del Votante: ";
                            cin >> nombre;
                            
                            if(consulta.ObtenerRegistro(nombre, distrito))
                                votante.setDistrito(distrito);
                            else
                                cout << "No existe el distrito" << resultado << endl; // no se encontro distrito
                            break;
                        case 'V':
                            break;
                        default:
                            invalida_v=true;
                            break;
                        }

                        if(!invalida_v && (opcion != 'V'))
                        {
                            if((abm.modificacionVotante(votante)))
                                cout << "Se modifico el Votante \"" << nombre << "\"." << endl;
                            else
                                cout << "Error al modificar al Votante." << endl;
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
