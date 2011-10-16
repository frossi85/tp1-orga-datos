/*
 * Menu_votante.cpp
 *
 *  Created on: 07/10/2011
 *      Author: Miguel Torres
 */

#include "MenuVotante.h"
#include "DataGetter.h"
#include <vector>

MenuVotante::MenuVotante(Votante *votante) {

	this->votante=votante;

	opciones();

}

void MenuVotante::opciones(){

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

void MenuVotante::mostrar_menu_elecciones(){

	char opcion;
	Eleccion *eleccion;


	eleccion=this->elegir_eleccion();


	if(eleccion==NULL){
		opciones();
	}else{
		mostrar_listas_a_votar(eleccion);
	}



}


Eleccion* MenuVotante::elegir_eleccion(){

	bool eleccion_elegida=false;
	unsigned opcion;
	Eleccion *resultado;
	vector<Eleccion *> elecciones=DataGetter::getElecciones_por_Votante(*this->votante);
	unsigned int cantidad_elecciones=elecciones.size();
	cout<<"************************************"<<endl;
	cout<<endl<<"Elecciones Disponibles: "<<endl;
	do{
		opcion=1;

		for(unsigned i=0;i<cantidad_elecciones;i++){

			cout<<opcion+i<<" - "<<elecciones[i]->getCargo().getCargoPrincipal()<<endl;

		}

		cout<<"0 - Volver a menu anterior"<<endl<<endl;
		cout<<"Elegir Eleccion: ";
		cin>>opcion;
		eleccion_elegida=( opcion>=0) && (opcion<=cantidad_elecciones);

	}while(!eleccion_elegida);


	if(opcion==0){

		resultado=NULL;

	}else{
		resultado=elecciones[opcion-1];
	}

	return resultado;

}


void MenuVotante::mostrar_listas_a_votar(Eleccion *eleccion){

	Lista *lista;

	bool confirmacion=false;

	do{

		lista=this->elegir_Lista(eleccion);

		if(lista!=NULL){
			confirmacion=confirmar_votacion(eleccion,lista);
		}

	}while((!confirmacion) && lista!=NULL);

	if (confirmacion){
		cout<<"Voto Aceptado"<<endl;

		//Se regresa al menu Principal
		opciones();
	}else if (lista==NULL) {


		mostrar_menu_elecciones();

	}

}


Lista* MenuVotante::elegir_Lista(Eleccion *eleccion){

	Lista *lista_resultado;
	bool lista_elegida=false;
	vector<Lista *> listas=DataGetter::getListas_por_Eleccion(*eleccion);
	int cantidad_listas=listas.size();
	unsigned opcion;

	do{
		cout<<"************************************"<<endl;
		cout<<endl<<"Listas Disponibles a votar:"<<endl;
		for(int i=0;i<cantidad_listas;i++){

			cout<<(i+1)<<" - "<<listas[i]->getNombre()<<endl;
		}

		cout<<endl<<"0 - Volver a menu anterior"<<endl;
		cout<<"Elegir Lista: ";
		cin>>opcion;

		lista_elegida=(opcion>=0) && (opcion<=cantidad_listas);
	}while(!lista_elegida);

	if(opcion==0){
		lista_resultado=NULL;
	}else{
		lista_resultado=listas[opcion-1];
	}

	return lista_resultado;


}


bool MenuVotante::confirmar_votacion(Eleccion *eleccion,Lista *lista){

	//system("clear");
	char opcion;
	bool opcion_elegida=false;
	bool confirmacion=false;

	do{


		cout<<"Confirmacion de voto a: "<<lista->getNombre()<<endl;
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

void MenuVotante::mostrar_menu_datos(){

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

void MenuVotante::cambiar_clave(){

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

void MenuVotante::cambiar_domicilio(){

	char nuevo_domicilio[30];
	cout<<"Domicilio Anterior: "<<this->votante->getDomicilio()<<endl;
	cout<<"Ingrese Nuevo Domicilio: ";

	scanf("%s",nuevo_domicilio);
	string nuevo_domicilio_str(nuevo_domicilio);
	this->votante->setDomicilio(nuevo_domicilio_str);
	this->guardar_cambios();

}

void MenuVotante::guardar_cambios(){



}

MenuVotante::~MenuVotante() {

	delete this->votante;
}
