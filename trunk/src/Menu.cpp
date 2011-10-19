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
#include "Informe.h"
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
		cout << "R => Informes de Resultados." << endl;
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
		case 'C':
			adminCargo();
			retorno=true;
			break;
		case 'R':
			adminInformes();
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
	std::string nombre_distrito;
	ABMentidades abm;
	ConsultaEntidades consulta;
	Distrito *distrito;


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

			cin >> nombre_distrito;

			//nombre_distrito.append(nombre);

			distrito=new Distrito(nombre_distrito);

			if(abm.altaDistrito(*distrito))
				cout << "Se creo el Distrito \"" << nombre << "\"." << endl;
			else
				cout << "El Distrito ya existe o se produjo un error al crearlo." << endl;

			cout << "Ingrese cualquier letra para continuar: ";
			cin >> opcion;
			retorno=true;
			break;
		case 'B':
			cout << endl <<endl;
			cout << "Ingrese el nombre del ditrito a borrar: ";
			cin >> nombre_distrito;

			distrito=new Distrito;


			if (!consulta.ObtenerRegistro(nombre_distrito,*distrito))
			{
				cout << "No existe el Distrito \"" << nombre << "\"." << endl;
			}else{
				abm.bajaDistrito(*distrito);
			}
			cout << "Ingrese cualquier letra para continuar: ";
			cin >> opcion;
			retorno=true;
			break;

		case 'M':
			cout << endl <<endl;
			cout << "Ingrese el nombre del ditrito a modificar: ";
			cin >> nombre_distrito;

			distrito=new Distrito();

			if(consulta.ObtenerRegistro(nombre_distrito,*distrito)){
				cout << "Distrito encontrado." << endl;
				cout << "ingrese el nuevo nombre del distrito: ";
				cin >> nombre_distrito;

				distrito->modificarNombre(nombre_distrito);

				if(abm.modificacionDistrito(*distrito)){
					cout<<"Se modifico el Distrito."<<endl;
				}else{
					cout << "Error al modificar el distrito."<<endl;
				}

			}else{
				cout<<"El distrito No Existe"<<endl;

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

void Menu::adminCargo() {
	char opcion;
		bool invalida=false;
		bool retorno=false;
		char nombre[50];
		Cargo cargo;
		int resultado;
	    ConsultaEntidades consulta;
	    ABMentidades abm;
		do {
			system("clear");
			if (invalida) {
				cout << "Opcion invalida, intente nuevamente." << endl;
			}
			cout << "********************************" << endl;
			cout << "A => Crear un Cargo." << endl;
			cout << "B => Borrar un Cargo." << endl;
			cout << "G => Agregar un Cargo secundario." << endl;
			cout << "V => Volver." << endl << "Opcion: ";
			cin >> opcion;

			retorno=false;
			invalida=false;
			switch ((char)toupper(opcion)) {
			case 'A':
			{
				cout << endl <<endl;
				cout << "Ingrese el nombre del nuevo Cargo: ";
				cin >> nombre;

				string cad(nombre);
				Cargo nuevo(cad);
				//Se crea el cargo, verificando si no existia
				if(abm.altaCargo(nuevo))
					cout << "Se creo el Cargo \"" << nombre << "\"." << endl;
				else
					cout << "El cargo ya existe o se produjo un error al crearlo." << endl;

				cout << "Ingrese cualquier letra para continuar: ";
				cin >> opcion;
				retorno=true;
				break;
			}
			case 'B':
				cout << endl <<endl;
				cout << "Ingrese el nombre del Cargo a borrar: ";
				cin >> nombre;


				if(!(consulta.ObtenerRegistro(nombre, cargo)))
				{
					cout<<"El cargo no existe"<<endl;
					resultado = -1;
					break;
				}
				if(abm.bajaCargo(cargo))
					cout << "Se borro el cargo \"" << nombre << "\"." << endl;
				else
					cout<< "No se ha podido borrar al cargo." << endl;

				cout << "Ingrese cualquier letra para continuar: ";
				cin >> opcion;
				retorno=true;
				break;
			case 'D':
				cout << endl <<endl;
				cout << "Ingrese el nombre del Cargo a modificar: ";
				cin >> nombre;

				if(!(consulta.ObtenerRegistro(nombre, cargo)))
				{
					cout<<"El cargo no existe"<<endl;
					resultado = -1;
					break;
				} else {
					cout << endl <<endl;
					cout << "Ingrese el nombre del Cargo secundario: ";
					cin >> nombre;

					cargo.agregarCargoSecundario(nombre);
				}

				cout << "Ingrese cualquier letra para continuar: ";
				cin >> opcion;
				retorno=true;
				break;
			}
		} while ((invalida) || (retorno));

}


void Menu::adminEleccion(){


	char opcion;
	bool invalida=false;
	bool retorno=false;

	ABMentidades abm;
	ConsultaEntidades consulta;

	Eleccion eleccion;
	string fecha_eleccion;

	Distrito distrito;
	string nom_distrito;


	do {
		system("clear");
		if (invalida) {
			cout << "Opcion invalida, intente nuevamente." << endl;
		}
		cout << "********************************" << endl;
		cout << "A => Crear un Eleccion." << endl;
		cout << "B => Borrar un Eleccion." << endl;
		cout << "M => Modificar un Eleccion." << endl;
		cout << "V => Volver." << endl << "Opcion: ";
		cin >> opcion;

		retorno=false;
		invalida=false;
		switch ((char)toupper(opcion)) {

		case 'A':
			cout << endl <<endl;
			cout << "Ingrese el Fecha de Eleccion: ";

			cin >> fecha_eleccion;


		case 'B':

			retorno=true;
			break;

		case 'M':

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
					/*
					 * Crear un Votante
					 */
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

					//TODO: Faltan set de los atributos basicos del votante, ver en la modificacion y baja

                    //Se crea el votante, verificando si no existia
                    if(abm.altaVotante(votante))
                        cout << "Se creo el Votante \"" << nombre << "\"." << endl;
                    else
                        cout << "El votante ya existe o se produjo un error al crearlo." << endl;

                    cout << "Ingrese cualquier letra para continuar: ";
                    cin >> opcion;
                    retorno=true;
                    break;

                    /*
                     * Borrar Votante
                     */
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

                    /*
                     * Modificar un Votante
                     *
                     */

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
                        case 'o':
                        case 'O':
                            cout << "ingrese el nuevo domicilio del Votante: ";
                            cin >> nombre;

                            votante.setDomicilio(nombre);
                            break;
                        case 'd':
                        case 'D':
                            cout << "ingrese el nombre del nuevo distrito del Votante: ";
                            cin >> nombre;
                            
                            if(consulta.ObtenerRegistro(nombre, distrito))
                                votante.setDistrito(distrito);
                            else
                                cout << "No existe el distrito" << resultado << endl; // no se encontro distrito
                            break;
                        case 'v':
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

void Menu::adminInformes(){

    char opcion;
    bool invalida=false;
    bool retorno=false;
    string nombre_distrito;
    Eleccion eleccion;
    string fecha_eleccion,fecha_eleccion_index,cargo_eleccion;
    string clave;
    string nombre_cargo,nombre_lista;

    Distrito distrito;
    Lista lista;

    Informe *informe;
    ConsultaEntidades consulta;
    ABMentidades abm;

    do {
        system("clear");
        if (invalida) {
                cout << "Opcion invalida, intente nuevamente." << endl;
        }
        cout << "********************************" << endl;
        cout << "E => Presentar Informe por Eleccion." << endl;
        cout << "D => Presentar Informe por Distrito." << endl;
        cout << "L => Presentar Informe por Lista." << endl;
        cout << "V => Volver." << endl << "Opcion: ";
        cin >> opcion;

        retorno=false;
        invalida=false;
        opcion = (char)toupper(opcion);
        switch (opcion) {

            case 'E':

				cout<<"Ingrese fecha Eleccion:";
				cin>>fecha_eleccion;
				fecha_eleccion_index=Utilidades::indexarFecha(fecha_eleccion);
				cout<<"Ingrese Cargo:";
				cin>>cargo_eleccion;

				clave=fecha_eleccion_index + "$" + cargo_eleccion;
				if(consulta.ObtenerRegistro(clave,eleccion)){

					informe=new Informe(eleccion);
					delete informe;

				}else{

					cout<<"No existe la Eleccion ingresada."<<endl;
				}

				cout << "Ingrese cualquier letra para continuar: ";
				cin >> opcion;
				retorno=true;
				break;

            case 'D':
				cout<<"Ingrese Nombre de Distrito:";
				cin>> nombre_distrito;

				clave=nombre_distrito;

				if(consulta.ObtenerRegistro(clave,distrito)){

					informe=new Informe(distrito);
					delete informe;

				}else{

					cout<<"No existe distrito "<<nombre_distrito<<"."<<endl;

				}


				cout << "Ingrese cualquier letra para continuar: ";
				cin >> opcion;
				retorno=true;
				break;

            case 'L':

            	cout<<"Ingrese Nombre de Lista:";
            	cin>>nombre_lista;

            	cout<<"Ingrese Cargo que se postula en la Lista:";
            	cin>>nombre_cargo;

            	cout<<"Ingrese fecha de eleccion para la lista:";
            	cin>>fecha_eleccion;

            	fecha_eleccion_index=Utilidades::indexarFecha(fecha_eleccion);

            	clave=fecha_eleccion_index + "$" + nombre_cargo + "$" + nombre_lista;

            	if(consulta.ObtenerRegistro(clave,lista)){

            		informe= new Informe(lista);
            		delete informe;

            	}else{

            		cout<<"No Existe la Lista Ingresada."<<endl;
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
