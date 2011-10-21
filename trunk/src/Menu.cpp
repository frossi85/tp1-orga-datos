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
#include <cstdio>
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
	Votante votante;//= DataGetter::getVotante(user);
	ConsultaEntidades consulta;


	if(consulta.ObtenerRegistro(this->user,votante) && votante.getClave()== pass)
	{
		cout<< "Accedio al sistema." << endl;

		//Se LLama al menu del Votante

		MenuVotante menuVotante(&votante);

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
		case 'L':
			adminLista();
			break;
		case 'E':
			adminEleccion();
			break;
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

void Menu::adminCandidato(){

	char opcion;
	char opcionSiNo;
	bool invalida=false;
	bool retorno=false;

	ABMentidades abm;
	ConsultaEntidades consulta;

	Candidato candidato;
	Eleccion eleccion;
	string fechaEleccion;
	string cargo;

	Lista lista;
	string nombreLista;
	string claveConsulta;
	string dni;


	do {
		system("clear");
		if (invalida) {
			cout << "Opcion invalida, intente nuevamente." << endl;
		}
		cout << "********************************" << endl;
		cout << "A => Crear una Candidato." << endl;
		cout << "B => Borrar una Candidato." << endl;
		cout << "M => Modificar una Candidato." << endl;
		cout << "V => Volver." << endl << "Opcion: ";
		cin >> opcion;

		retorno=false;
		invalida=false;
		switch ((char)toupper(opcion)) {


		case 'A':
			cout << endl <<endl;
			cout << "Ingrese el nombre de la Lista del Candidato: ";
			cin.ignore();
			getline(cin, nombreLista);
			cout << "Lista ingresada: " << nombreLista <<endl;
			cout << endl <<endl;
			cout << "Eleccion a la que se postula: "<<endl;
			cout << "- Ingrese fecha: ";
			cin >> fechaEleccion;
			//cin.ignore() sirve para sacar el Enter del buffer y podes usar despues getline()

			cout<< "Fecha ingresada: " << fechaEleccion << endl;
			cin.ignore();
			cout << "- Ingrese el Cargo del candidato: ";
			getline(cin, cargo);

			cout<< "Cargo ingresado: " << cargo << endl;

			cout<< endl<<"Ingrese DNI del candidato: "<<endl;
			getline(cin, dni);

			claveConsulta = Utilidades::indexarFecha(fechaEleccion) + "$" + cargo + "$" + nombreLista;
			Utilidades::formatearClave(claveConsulta);

			if(consulta.ObtenerRegistro(claveConsulta,lista))
			{

				Utilidades::formatearClave(dni);
				Votante votante;
				if (consulta.ObtenerRegistro(dni,votante)){
					Candidato candidato(votante,lista);
					if(abm.altaCandidato(candidato)){
						cout<<"El Candidato se creo correctamente."<<endl;
					}else{
						cout<<"Hubo un problema al dar de Alta al Candidato."<<endl;
					}

				}else{
					cout<<"No existe el Votante asociado al Candidato"<<endl;
				}

			}
			else
				cout<<endl<<"No existe la Lista Ingresada."<<endl;

			cout<<endl<<"Presione una tecla para continuar."<<endl;

			getchar();
			break;
		case 'B':
			cout << endl <<endl;
			cout << "Ingrese el nombre de la Lista del Candidato: ";
			cin.ignore();
			getline(cin, nombreLista);
			cout << "Lista ingresada: " << nombreLista <<endl;
			cout << endl <<endl;
			cout << "Eleccion a la que se postula: "<<endl;
			cout << "- Ingrese fecha: ";
			cin >> fechaEleccion;
			//cin.ignore() sirve para sacar el Enter del buffer y podes usar despues getline()

			cout<< "Fecha ingresada: " << fechaEleccion << endl;
			cin.ignore();
			cout << "- Ingrese el Cargo del candidato: ";
			getline(cin, cargo);

			cout<< "Cargo ingresado: " << cargo << endl;

			cout<< endl<<"Ingrese DNI del candidato: "<<endl;
			getline(cin, dni);

			claveConsulta = Utilidades::indexarFecha(fechaEleccion) + "$" + cargo + "$" + nombreLista;
			Utilidades::formatearClave(claveConsulta);

			if(consulta.ObtenerRegistro(claveConsulta,lista))
			{

				string fechaIndex=Utilidades::indexarFecha(fechaEleccion);
				string clave=fechaIndex + "$" + cargo + "$" + nombreLista + "$" + dni;
				Utilidades::formatearClave(clave);
				Candidato candidato;
				if (consulta.ObtenerRegistro(clave,candidato)){

					if(abm.bajaCandidato(candidato)){

						cout<<"Se dio de baja como Candidato a:"<<candidato.getNombreYApellido()<<endl;

					}else{

						cout<<"Hubo un problema al dar de baja al Candidato."<<endl;

					}



				}else{
					cout<<"No existe el Candidato ingresado."<<endl;
				}

			}
			else
				cout<<endl<<"No existe la Lista Ingresada."<<endl;

			cout<<endl<<"Presione una tecla para continuar."<<endl;

			getchar();

			retorno=true;
			break;

		case 'M':

			cout << endl;
			cout << "Ingrese el nombre de la Lista del Candidato: ";
			cin.ignore();
			getline(cin, nombreLista);
			cout << "Lista ingresada: " << nombreLista <<endl;
			cout << endl <<endl;
			cout << "Eleccion a la que se postula: "<<endl;
			cout << "- Ingrese fecha: ";
			cin >> fechaEleccion;
			//cin.ignore() sirve para sacar el Enter del buffer y podes usar despues getline()

			cout<< "Fecha ingresada: " << fechaEleccion << endl;
			cin.ignore();
			cout << "- Ingrese el Cargo del candidato: ";
			getline(cin, cargo);

			cout<< "Cargo ingresado: " << cargo << endl;

			cout<< endl<<"Ingrese DNI del candidato: "<<endl;
			getline(cin, dni);

			claveConsulta = Utilidades::indexarFecha(fechaEleccion) + "$" + cargo + "$" + nombreLista;
			Utilidades::formatearClave(claveConsulta);

			if(consulta.ObtenerRegistro(claveConsulta,lista))
			{

				string fechaIndex=Utilidades::indexarFecha(fechaEleccion);
				string clave=fechaIndex + "$" + cargo + "$" + nombreLista + "$" + dni;
				Utilidades::formatearClave(clave);
				Candidato candidato;
				if (consulta.ObtenerRegistro(clave,candidato)){

					bool huboCambios=false;
					string nuevoDomicilio;
					cout<<"Candidato: "<<candidato.getNombreYApellido()<<" Postulado para:"<<candidato.getCargo().getCargoPrincipal()<<endl;
					cout<<"Domicilio Actual: "<<candidato.getVotante().getDomicilio()<<endl;
					cout<<"Ingrese Nuevo Domicilio(0 para no cambiarlo):";

					cin.ignore();
					getline(cin,nuevoDomicilio);

					if(nuevoDomicilio!="0"){
						huboCambios=true;
						candidato.getVotante().setDomicilio(nuevoDomicilio);

					}


					if(huboCambios){

						if(abm.modificacionCandidato(candidato)){
							cout<<"Se modifico correctamente el Candidato."<<endl;
						}else{
							cout<<"Hubo un problema al intertar modificar el Candidato."<<endl;
						}

					}




				}else{
					cout<<"No existe el Candidato ingresado."<<endl;
				}

			}
			else
				cout<<endl<<"No existe la Lista Ingresada."<<endl;


			cout<<endl<<"Presione una tecla para continuar."<<endl;
			getchar();
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

void Menu::adminLista(){


	char opcion;
	char opcionSiNo;
	bool invalida=false;
	bool retorno=false;

	ABMentidades abm;
	ConsultaEntidades consulta;

	Eleccion eleccion;
	string fechaEleccion;
	string cargo;

	Lista lista;
	string nombreLista;
	string claveConsulta;


	do {
		system("clear");
		if (invalida) {
			cout << "Opcion invalida, intente nuevamente." << endl;
		}
		cout << "********************************" << endl;
		cout << "C => Consultar una Lista." << endl;
		cout << "A => Crear una Lista." << endl;
		cout << "B => Borrar una Lista." << endl;
		cout << "M => Modificar una Lista." << endl;
		cout << "V => Volver." << endl << "Opcion: ";
		cin >> opcion;

		retorno=false;
		invalida=false;
		switch ((char)toupper(opcion)) {

		case 'C':
			cout << endl <<endl;
			cout << "Ingrese el nombre de la Lista: ";
			cin.ignore();
			getline(cin, nombreLista);
			cout << "Lista ingresada: " << nombreLista <<endl;
			cout << endl <<endl;
			cout << "Ingrese el Fecha de Eleccion: ";
			cin >> fechaEleccion;
			//cin.ignore() sirve para sacar el Enter del buffer y podes usar despues getline()

			cout<< "Fecha ingresada: " << fechaEleccion << endl;
			cin.ignore();
			cout << "Ingrese el Cargo: ";
			getline(cin, cargo);

			cout<< "Cargo ingresado: " << cargo << endl;

			claveConsulta = Utilidades::indexarFecha(fechaEleccion) + "$" + cargo + "$" + nombreLista;
			Utilidades::formatearClave(claveConsulta);

			if(consulta.ObtenerRegistro(claveConsulta, lista))
			{
				cout<<endl;
				lista.Imprimir();
			}
			else
				cout<<endl<<"No existe la lista solicitada."<<endl;

			cout<<endl<<"Presione una tecla para continuar."<<endl;

			getchar();
			break;
		case 'A':
			cout << endl <<endl;
			cout << "Ingrese el nombre de la Lista: ";
			cin.ignore();
			getline(cin, nombreLista);
			cout << "Lista ingresada: " << nombreLista <<endl;
			cout << endl <<endl;
			cout << "Eleccion a presentarse: "<<endl;
			cout << "- Ingrese fecha: ";
			cin >> fechaEleccion;
			//cin.ignore() sirve para sacar el Enter del buffer y podes usar despues getline()

			cout<< "Fecha ingresada: " << fechaEleccion << endl;
			cin.ignore();
			cout << "- Ingrese el cargo: ";
			getline(cin, cargo);

			cout<< "Cargo ingresado: " << cargo << endl;

			claveConsulta = Utilidades::indexarFecha(fechaEleccion) + "$" + cargo;
			Utilidades::formatearClave(claveConsulta);

			if(consulta.ObtenerRegistro(claveConsulta, eleccion))
			{
				claveConsulta += ("$" + nombreLista);
				Utilidades::formatearClave(claveConsulta);

				lista.setNombre(nombreLista);
				lista.setEleccion(eleccion);

				if(!abm.altaLista(lista))
					cout<<endl<<"La lista ya existe."<<endl;
			}
			else
				cout<<endl<<"No existe la eleccion a la cual se quiere presentar."<<endl;

			cout<<endl<<"Presione una tecla para continuar."<<endl;

			getchar();
			break;
		case 'B':

			cout << endl <<endl;
			cout << "Ingrese el nombre de la Lista: ";
			cin.ignore();
			getline(cin, nombreLista);
			cout << "Lista ingresada: " << nombreLista <<endl;
			cout << endl;
			cout << "Eleccion a la que pertenece: "<<endl;
			cout << "- Ingrese fecha: ";
			cin >> fechaEleccion;
			//cin.ignore() sirve para sacar el Enter del buffer y podes usar despues getline()

			cout<< "Fecha ingresada: " << fechaEleccion << endl;
			cin.ignore();
			cout << "- Ingrese el Cargo: ";
			getline(cin, cargo);

			cout<< "Cargo ingresado: " << cargo << endl;

			claveConsulta = Utilidades::indexarFecha(fechaEleccion) + "$" + cargo;
			Utilidades::formatearClave(claveConsulta);

			if(consulta.ObtenerRegistro(claveConsulta, eleccion))
			{
				claveConsulta += ("$" + nombreLista);
				Utilidades::formatearClave(claveConsulta);

				if(consulta.ObtenerRegistro(claveConsulta,lista)){

					if(abm.bajaLista(lista)){
						cout<<"Hubo un problema al dar de baja la Lista."<<endl;
					}else{
						cout<<"Se dio de baja correctamente."<<endl;
					}

				}else{
					cout<<"No existe la Lista."<<endl;
				}


			}
			else
				cout<<endl<<"No existe la eleccion que se ingreso."<<endl;

			cout<<endl<<"Presione una tecla para continuar."<<endl;
			getchar();
			retorno=true;
			break;

		case 'M':

			cout << endl <<endl;
			cout << "Ingrese el nombre de la Lista: ";
			cin.ignore();
			getline(cin, nombreLista);
			cout << "Lista ingresada: " << nombreLista <<endl;
			cout << endl;
			cout << "Eleccion a la que pertenece: "<<endl;
			cout << "- Ingrese fecha: ";
			cin >> fechaEleccion;
			//cin.ignore() sirve para sacar el Enter del buffer y podes usar despues getline()

			cout<< "Fecha ingresada: " << fechaEleccion << endl;
			cin.ignore();
			cout << "- Ingrese el Cargo: ";
			getline(cin, cargo);

			cout<< "Cargo ingresado: " << cargo << endl;

			claveConsulta = Utilidades::indexarFecha(fechaEleccion) + "$" + cargo;
			Utilidades::formatearClave(claveConsulta);

			if(consulta.ObtenerRegistro(claveConsulta, eleccion))
			{
				claveConsulta += ("$" + nombreLista);
				Utilidades::formatearClave(claveConsulta);

				if(consulta.ObtenerRegistro(claveConsulta,lista)){
					bool hubo_cambios=false;
					string nv_nombre;
					cout<<"******Modificaciones******"<<endl;
					cout<<"Nombre de la Lista: "<<lista.getNombre()<<endl;
					cout<<"Ingrese Nuevo nombre para la Lista(0 para finalizar):";
					cin.ignore();
					getline(cin,nv_nombre);

					if(nv_nombre!="0"){

						hubo_cambios=true;
						lista.setNombre(nv_nombre);
					}


					if(hubo_cambios){
						if(abm.modificacionLista(lista)){
							cout<<"Se modifico correctamente."<<endl;
						}else{
							cout<<"Hubo un error al Modificar la Lista."<<endl;
						}
					}

				}else{
					cout<<"No existe la Lista."<<endl;
				}


			}
			else
				cout<<endl<<"No existe la eleccion que se ingreso."<<endl;

			cout<<endl<<"Presione una tecla para continuar."<<endl;
			getchar();
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

			cin.ignore();
			getline(cin,nombre_distrito);

			//nombre_distrito.append(nombre);

			distrito=new Distrito(nombre_distrito);

			if(abm.altaDistrito(*distrito))
				cout << "Se creo el Distrito \"" << nombre_distrito << "\"." << endl;
			else
				cout << "El Distrito ya existe o se produjo un error al crearlo." << endl;

			cout << "Ingrese cualquier letra para continuar: ";
			cin >> opcion;
			retorno=true;
			break;
		case 'B':
			cout << endl <<endl;
			cout << "Ingrese el nombre del ditrito a borrar: ";
			cin.ignore();
			getline(cin,nombre_distrito);

			distrito=new Distrito;


			if (!consulta.ObtenerRegistro(nombre_distrito,*distrito))
			{
				cout << "No existe el Distrito \"" << nombre << "\"." << endl;
			}else{
				abm.bajaDistrito(*distrito);
			}
			cout << "Presione cualquier letra para continuar: ";
			getchar();
			retorno=true;
			break;

		case 'M':
			cout << endl <<endl;
			cout << "Ingrese el nombre del ditrito a modificar: ";
			cin.ignore();
			getline(cin,nombre_distrito);

			distrito=new Distrito();

			if(consulta.ObtenerRegistro(nombre_distrito,*distrito)){
				cout << "Distrito encontrado." << endl;
				cout << "ingrese el nuevo nombre del distrito: ";
				cin.ignore();
				getline(cin,nombre_distrito);

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
			getchar();
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


	char opcionSiNo;
	char opcion;
	bool invalida=false;
	bool retorno=false;

	ABMentidades abm;
	ConsultaEntidades consulta;

	Eleccion eleccion;
	string fecha_eleccion;

	Cargo cargo;
	string cargo_eleccion;

	Distrito distrito;
	string nom_distrito;

	string nombreCargo,claveConsulta;


	do {
		system("clear");
		if (invalida) {
			cout << "Opcion invalida, intente nuevamente." << endl;
		}
		cout << "********************************" << endl;
		cout << "C => Consultar una Eleccion." << endl;
		cout << "A => Crear un Eleccion." << endl;
		cout << "B => Borrar un Eleccion." << endl;
		cout << "M => Modificar un Eleccion." << endl;
		cout << "V => Volver." << endl << "Opcion: ";
		cin >> opcion;


		retorno=false;
		invalida=false;
		switch ((char)toupper(opcion)) {
		case 'C':
			cout << endl <<endl;
			cout << "Ingrese el Fecha de Eleccion: ";
			cin >> fecha_eleccion;
			//cin.ignore() sirve para sacar el Enter del buffer y podes usar despues getline()
			cin.ignore();
			cout << "Ingrese el Cargo: ";
			getline(cin, nombreCargo);

			claveConsulta = Utilidades::indexarFecha(fecha_eleccion) + "$" + nombreCargo;
			Utilidades::formatearClave(claveConsulta);

			if(consulta.ObtenerRegistro(claveConsulta, eleccion))
			{
				cout<<endl;
				eleccion.Imprimir();
				cout<<"Desea ver sus diistritos? (S/N)"<<endl;

				cin>>opcionSiNo;
				cin.ignore();

				if(toupper(opcionSiNo) == 'S')
					eleccion.ImprimirDistritos();
			}
			else
				cout<<endl<<"No existe la eleccion solicitada."<<endl;

			cout<<endl<<"Presione una tecla para continuar."<<endl;

			getchar();
			break;
		case 'A':
			cout << endl <<endl;

			cout<<"Ingrese el Cargo Para la Eleccion: ";
			cin.ignore();
			getline(cin,cargo_eleccion);


			if(consulta.ObtenerRegistro(cargo_eleccion,cargo)){

				cout << "Ingrese el Fecha de Eleccion: ";
				cin >> fecha_eleccion;

				string fecha_index=Utilidades::indexarFecha(fecha_eleccion);

				string clave= fecha_index + "$" + cargo_eleccion;
				Utilidades::formatearClave(clave);

				if(!consulta.ObtenerRegistro(clave,eleccion)){

					cout<<"Ingrese el Primer Distrito para esta Eleccion: ";
					cin.ignore();
					getline(cin,nom_distrito);


					if (consulta.ObtenerRegistro(nom_distrito,distrito)){

						eleccion.setCargo(cargo);
						eleccion.agregarDistrito(distrito);

						if(abm.altaEleccion(eleccion)){
							cout<<"La eleccion se creo correctamente."<<endl;
						}else{
							cout<<"Ya existe o hubo un problema al crear la eleccion."<<endl;
						}


					}else {
						cout<<"No existe el Distrito: "<<nom_distrito<<endl;
					}


				}else{
					cout<<"Ya Existe la Eleccion."<<endl;
				}

			}else{

				cout<<"No esta registrado el Cargo: "<<cargo_eleccion<<endl;

			}

		cout<<"Presione una tecla para continuar:";
		getchar();
		break;
		case 'B':

			cout<<"Ingrese el Cargo de la Eleccion a Borrar: ";
			cin.ignore();
			getline(cin,cargo_eleccion);

			cout << "Ingrese fecha de la Eleccion: ";
			cin >> fecha_eleccion;

			if(consulta.ObtenerRegistro(cargo_eleccion,cargo)){

				string fecha_index=Utilidades::indexarFecha(fecha_eleccion);
				string clave= fecha_index + "$" + cargo_eleccion;
				Utilidades::formatearClave(clave);
				if(consulta.ObtenerRegistro(clave,eleccion)){


					//Aca se hace la baja de la Eleccion
					if(!abm.bajaEleccion(eleccion)){
						cout<<"Hubo un problema al dar de baja la eleccion."<<endl;
					}

				}else{

					cout<<"No existe la Eleccion"<<endl;
				}


			}else{
				cout<<"No existe el Cargo Ingresado."<<endl;

			}


			cout<<"Presione una tecla para continuar:";
			getchar();
			retorno=true;
			break;

		case 'M':
			cout<<"Ingrese el Cargo de la Eleccion: ";
			cin >> cargo_eleccion;

			cout << "Ingrese fecha de la Eleccion: ";
			cin >> fecha_eleccion;


			if(consulta.ObtenerRegistro(cargo_eleccion,cargo)){

				string fecha_index=Utilidades::indexarFecha(fecha_eleccion);
				string clave=fecha_index + "$" + cargo_eleccion;

				if(consulta.ObtenerRegistro(clave,eleccion)){
						string cargo_sec;
						bool ingresando=false;
						bool hubo_cambios=false;

						do{
							cout<<"Agregue un Cargo Secundario(ingrese '0' para finalizar):";
							cin.ignore();
							getline(cin,cargo_sec);

							ingresando=cargo_sec!="0";
							if(ingresando){
								eleccion.getCargo().agregarCargoSecundario(cargo_sec);

								hubo_cambios=true;
							}

						}while(ingresando);

						ingresando=false;
						string nombre_distrito;

						do{
							cout<<"Ingrese nombre del Distrito a agregar(0 para finalizar):";
							cin.ignore();
							getline(cin,nombre_distrito);
							Distrito dist;

							ingresando=nombre_distrito!="0";
							if(ingresando){
								if(consulta.ObtenerRegistro(nombre_distrito,dist)){
									eleccion.agregarDistrito(dist);
									hubo_cambios=true;
								}else{
									cout<<"No existe el distrito."<<endl;
								}
							}

						}while(ingresando);


						if(hubo_cambios){

							if(!abm.modificacionEleccion(eleccion)){
								cout<<"Se produjo un error en la Modificacion"<<endl;
							}
						}

				}else{
					cout<<"No existe la eleccion."<<endl;
				}

			}else{
				cout<<"No existe el Cargo Ingresado."<<endl;

			}


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
    char nombre[50], direccion[50], dni[50],clave_votante[30],nombreDistrito[50];
    string dniM;

    Votante votante,*vot=NULL;
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
        //cin >> opcion;
        //fgets(&opcion,1,stdin);
        //cin.getline(&opcion,1);
        scanf("%c",&opcion);

        retorno=false;
        invalida=false;
        opcion = (char)toupper(opcion);
        switch (opcion) {
					/*
					 * Crear un Votante
					 */
            case 'A':
                    cout <<endl; //((DNI)i, NombreyApellido, clave, domicilio, (distrito)ie, ((eleccion)ie)*)
                    int dniN;
                    dniN= -2;
                    do {
							if (dniN!=-2) {
								cout << "El DNI ingresado es invalido." << endl;
							}

                            cout << "Ingrese el DNI: ";

                            cin.ignore();
                            fgets(dni,50,stdin);

                            dniN = atoi(dni);


                    } while ( (dniN<5000000) || (dniN>100000000) );

                    cout<<"ingrese una clave para el Votante:";
                    //cin>>clave_votante;
                    //cin.getline(clave_votante,50);
                    fgets(clave_votante,50,stdin);

                    cout << "Ingrese el nombre y apellido del nuevo Votante: ";
                    //cin >> nombre;
                    //cin.getline(nombre,50);
                    fgets(nombre,50,stdin);

                    cout << "Ingrese el domicilio: ";
                    //cin >> direccion;
                    //cin.getline(direccion,30);
                    fgets(direccion,30,stdin);

                    cout << "ingrese el nombre del distrito del Votante: ";
                    //cin >> nombreDistrito;
                    //cin.getline(nombreDistrito,50);
                    fgets(nombreDistrito,50,stdin);

                    cout<<"Distro es: "<<nombreDistrito<<"."<<endl;

                    //Se verifica si existe el distrito
                    if(consulta.ObtenerRegistro(nombreDistrito, distrito))
                        //votante.setDistrito(distrito);
                    	vot=new Votante(dniN,nombre,clave_votante,direccion,distrito);
                    else
                        cout << "No existe el distrito " <<nombreDistrito<< endl; // no se encontro distrito

					//TODO: Faltan set de los atributos basicos del votante, ver en la modificacion y baja

                    //Se crea el votante, verificando si no existia

                    //if(abm.altaVotante(votante))
                    if(vot!=NULL && abm.altaVotante(*vot))
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
                        getchar();
                        break;
                    }

                    if(abm.bajaVotante(votante))
                        cout << "Se borro el Votante \"" << votante.getNombreYApellido() << "\"." << endl;
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
               // do {
                    if (dniN!=-2) {
                        cout << "El DNI ingresado es invalido. para salir ingrese salir" << endl;
                    }
                    cout << "Ingrese el DNI del Votante a modificar: ";
                    //cin >> dni;
                    cin >> dniM;
                    //dniN = atoi(dni);
                //} while (( (dniN<5000000) || (dniN>100000000) ) && dni != salir);

                //string dniAux(dni);

                if(!(consulta.ObtenerRegistro(dniM, votante)))
                {
                    cout<<"El votante no existe"<<endl;
                    resultado = -1;
                    cout<<"Presione una tecla para continuar.";
                    getchar();
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
