/*
 * Menu_votante.cpp
 *
 *  Created on: 07/10/2011
 *      Author: Miguel Torres
 */

#include "Menu_votante.h"

Menu_votante::Menu_votante(Votante *votante) {

	this->votante=votante;

	opciones();

}

void Menu_votante::opciones(){

	char opcion;
	bool opcion_elegida=false;

	do{
		system("clear");
		cout<<"***********************"<<endl;
		cout<<"Menu Votante"<<endl<<endl;
		cout<<"V - Votar en Eleccion"<<endl;
		cout<<"O - Cambiar Datos personales"<<endl;
		cout<<"S - Salir"<<endl<<endl;

		cin>>opcion;

		opcion_elegida=	opcion=='v' || opcion=='V' ||
						opcion=='o' || opcion=='O' ||
						opcion=='s' || opcion=='S';
	}
	while(!opcion_elegida);

	switch (opcion){

	case 'v':
	case 'V':	mostrar_menu_elecciones();
		 		break;
	case 'o':
	case 'O': 	mostrar_menu_datos();
				break;

	case 's':
	case 'S':
				break;
	default: break;

	}


}

void Menu_votante::mostrar_menu_elecciones(){

	char opcion;
	Eleccion *eleccion;


	//Se cargan todas las Elecciones Disponibles para el Usuario
	//...
	//...


	cout<<"**********************************"<<endl;
	cout<<"Elecciones Disponibles"<<endl<<endl;
	/*
	 *Muestra todas las elecciones
	 *Se selecciona alguna y se llama
	 *a la funcion que muestra las listas
	 *que corresponden a esa Eleccion
	 *
	 */

	cout<<"A - Eleccion para Presidente"<<endl;
	cout<<"B - Eleccion para Diputados"<<endl;
	cout<<endl<<"V - Volver a menu anterior"<<endl;
	cin>>opcion;

	//Se asigna el puntero a la eleccion que corresponda
	//... ...
	//... ...

	if(opcion=='v' || opcion=='V'){
		opciones();
	}else{
		mostrar_listas_a_votar(eleccion);
	}



}


void Menu_votante::mostrar_listas_a_votar(Eleccion *eleccion){

	Lista *lista;

	char opcion;
	bool confirmacion=false;

	do{
		//Se muestran Las Listas para seleccionar alguna
		//...
		//...

		cout<<"Listas Para Eleccion: "<<endl; //eleccion->Imprimir();

		cout<<"A - Lista 001"<<endl<<"B - Lista 002"<<"C - Lista 003"<<endl;
		cout<<"V - Volver a Menu de Elecciones"<<endl;

		cin>>opcion;

		//SE selecciona la Lista
		//..
		//..



		if(opcion!='v' && opcion!='V'){
			confirmacion=confirmar_votacion(eleccion,lista);
		}

	}while(!confirmacion &&( opcion!='v' && opcion!='V'));

	if (confirmacion){
		cout<<"Voto Aceptado"<<endl;

		//Se regresa al menu Principal
		opciones();
	}else if(opcion=='v' || opcion=='V'){


		mostrar_menu_elecciones();

	}

}


Lista* Menu_votante::elegir_Lista(){

	Eleccion e;




}


bool Menu_votante::confirmar_votacion(Eleccion *eleccion,Lista *lista){

	system("clear");
	char opcion;
	bool opcion_elegida=false;
	bool confirmacion=false;

	do{


		cout<<"Confirmacion de voto a: PEPITO"<<endl;//lista->getNombre();
		cout<<"A - Aceptar voto"<<endl;
		cout<<"R - Rechazar Voto"<<endl;
		cin>>opcion;

		opcion_elegida= opcion=='a' || opcion=='A' ||
						opcion=='r' || opcion=='R';


	}while(!opcion_elegida);

	if (opcion=='a' || opcion=='A'){

		//votante->votarEnEleccionALista(*eleccion,*lista);
		confirmacion=true;
	}

	return confirmacion;

}

void Menu_votante::mostrar_menu_datos(){

	    char opcion;
		bool opcion_elegida=false;

		do{
			system("clear");
			cout<<"***********************"<<endl;
			cout<<"Menu Datos Personales"<<endl<<endl;
			cout<<"C - Cambiar Clave "<<endl;
			cout<<"D - Cambiar Domicilio"<<endl<<endl;
			cout<<"V - Volver a Menu Principal"<<endl;

			cin>>opcion;

			opcion_elegida=	opcion=='c' || opcion=='C' ||
							opcion=='d' || opcion=='D' ||
							opcion=='v' || opcion=='V';
		}
		while(!opcion_elegida);

		switch (opcion){

			case 'v':
			case 'V':	opciones();
				 		break;
			case 'c':
			case 'C': 	this->cambiar_clave();
						mostrar_menu_datos();
						break;

			case 'd':
			case 'D':	this->cambiar_domicilio();
						mostrar_menu_datos();
						break;
			default: break;

			}


}

void Menu_votante::cambiar_clave(){

	char nueva_clave[20],nueva_clave_conf[20];
	bool ingreso_correcto=false;

	while (!ingreso_correcto){

		cout<<"Ingresar Nueva Clave: ";
		system("stty -echo");
		cin >> nueva_clave;
		system("stty echo");

		cout<<"Reingresar Nueva Clave: ";
		system("stty -echo");
		cin >> nueva_clave_conf;
		system("stty echo");

		ingreso_correcto=strcmp(nueva_clave,nueva_clave_conf)==0;

		if (ingreso_correcto){

			cout<<"Clave Nueva ingresada Correctamente."<<endl;

		}
		else{

			cout<<"Ingreso de clave nueva incorrecto."<<endl;
			cout<<"Vuelva a ingresarla. "<<endl;

		}

	}
	string clave_cambiada(nueva_clave);
	this->votante->cambiarClave(votante->getClave(),clave_cambiada);
	this->guardar_cambios();

}

void Menu_votante::cambiar_domicilio(){

	char nuevo_domicilio[30];
	cout<<"Domicilio Anterior: "<<this->votante->getDomicilio()<<endl;
	cout<<"Ingrese Nuevo Domicilio: ";

	scanf("%s",nuevo_domicilio);
	string nuevo_domicilio_str(nuevo_domicilio);
	this->votante->setDomicilio(nuevo_domicilio_str);
	this->guardar_cambios();

}

void Menu_votante::guardar_cambios(){



}

Menu_votante::~Menu_votante() {

	delete this->votante;
}
