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

#include "Criptografía/TestFactorizacion.h"
#include "Criptografía/RSA/TestRomperRSA.h"
#include "./Criptografía/AlgoVigenere/Vigenere.h"

using namespace std;

int main(int argc, char *argv[]){

	//TestFactorizacion::ejecutar();

    ConsultaEntidades consulta;
    ABMentidades abm;

	Distrito distrito1("Capital");
	abm.altaDistrito(distrito1);

	Cargo cargo("CargoPrincipal");
	abm.altaCargo(cargo);

	Eleccion eleccion("10/02/2011", cargo, distrito1);
	abm.altaEleccion(eleccion);

	Lista lista("Lista1", eleccion);
	abm.altaLista(lista);

	Votante votante1(31533482, "Facundo Rossi", "hackersout", "Saraza", distrito1);

	abm.altaVotante(votante1);

	abm.agregarVoto(votante1, lista, distrito1);

	Votante votante2;
	string dni = "31533482";

	if(!(consulta.ObtenerRegistro(dni, votante2)))
	{
		cout<<"El votante no existe"<<endl;
	}

	cout<<endl<<votante2.getDNI()<<endl;
	cout<<votante2.getNombreYApellido()<<endl;
	cout<<votante2.getClave()<<endl;
	cout<<votante2.getDomicilio()<<endl;
	votante2.getDistrito().Imprimir();
	votante2.getElecciones()[0]->Imprimir();

	cout<<endl<<endl;

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

	if ( argumento == "-a" || argumento== "--admin" )
	{
		cout << "Ingreso como administrador. \n(para salir ingrese \"salir\" en alguno de los campos) \n";
		// La funcionalidad deseada es acceder como administrador
		// Se pide y verifica usuario y contraseña
		do {
			menu->pedirUsuario();
			menu->pedirContrasena();
		} while (!menu->accesoAdmin());

		return 0;
	}

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

	if ( argumento == "-c" || argumento == "--cargainicial" )
	{
		CargaInicial::ejecutar();
		return 0;
	}

	if ( argumento == "-v" || argumento == "--votanteautomatico" )
	{
		VotanteAleatorio::ejecutar();
		return 0;
	}

	if ( argumento == "--romperRSA" )
	{
		TestRomperRSA test;

		test.iniciar();

		return 0;
	}

	if ( argumento == "--testVigenere" )
	{
		Vigenere test;

		test.ejecutarTestArchivo();

		return 0;
	}

	cout << "Uso: voto_electronico -h\n";   // Mal uso de las opciones

	return 0;
}
