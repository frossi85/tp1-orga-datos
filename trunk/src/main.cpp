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
	string dni = "31533482";
	string clave;
	string fecha = "10/02/2011";
	string cargoPrincipal = "CargoPrincipal";
	string nombreDistrito = "Capital";
	string nombreLista = "Lista1";

	Distrito distrito1(nombreDistrito);
	clave= nombreDistrito;
	Utilidades::formatearClave(clave);
	if(!(consulta.ObtenerRegistro(clave, distrito1)))
	{
		abm.altaDistrito(distrito1);
	}

	Cargo cargo(cargoPrincipal);
	clave= cargoPrincipal;
	Utilidades::formatearClave(clave);
	if(!(consulta.ObtenerRegistro(clave, cargo)))
	{
		abm.altaCargo(cargo);
	}

	Eleccion eleccion(fecha, cargo, distrito1);
	clave= Utilidades::indexarFecha(fecha) + "$" + cargoPrincipal;
	Utilidades::formatearClave(clave);
	if(!(consulta.ObtenerRegistro(clave, eleccion)))
	{
		abm.altaEleccion(eleccion);
	}

	Lista lista(nombreLista, eleccion);
	clave= Utilidades::indexarFecha(fecha) + "$" + cargoPrincipal + "$" + nombreLista;
	Utilidades::formatearClave(clave);
	if(!(consulta.ObtenerRegistro(clave, lista)))
	{
		abm.altaLista(lista);
	}

	Votante votante1(31533482, "Facundo Rossi", "hackersout", "Saraza", distrito1);
	clave= dni;
	Utilidades::formatearClave(dni);
	if(!(consulta.ObtenerRegistro(clave, votante1)))
	{
		abm.altaVotante(votante1);
	}

	abm.agregarVoto(votante1, lista, distrito1);

	Votante votante2;

	if(!(consulta.ObtenerRegistro(dni, votante2)))
	{
		cout<<"El votante no existe"<<endl;
	}

	cout<<endl<<votante2.getDNI()<<endl;
	cout<<votante2.getNombreYApellido()<<endl;
	cout<<votante2.getClave()<<endl;
	cout<<votante2.getDomicilio()<<endl;
	votante2.getDistrito().Imprimir();
	cout<<"Cantidad de elecciones: "<<votante2.getElecciones().size()<<endl;
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
