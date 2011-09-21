#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
using namespace std;

void mostrar_ayuda();
string pedir_usuario();
string pedir_contrasena();
bool confirmar_usuario(int,string, string);

int main(int argc, char *argv[]){

	if (argc != 2){

		// Numero incorrecto de parametros

		cout << "Uso: voto_electronico -h\n";
		return 0;
	}

	if ( !(strcmp(argv[1],"-h")) || !(strcmp(argv[1],"--help")) ) {

		// La funcionalidad deseada es acceder a la ayuda del programa.
		mostrar_ayuda();

		return 0;

	}

	if ( !(strcmp(argv[1],"-a")) || !(strcmp(argv[1],"--admin")) ) {

		// La funcionalidad deseada es acceder como administrador
		// Se pide y verifica usuario y contraseña

		string usuario = pedir_usuario();
		string password = pedir_contrasena();
		bool es_usuario = confirmar_usuario(1, usuario, password);  // el 1 indica que se intenta acceder como administrador

		/* if (es_usuario){
			ACA COMIENZA EL ACCESO COMO ADMINISTRADOR
		 }*/
		return 0;
	}
	if ( !(strcmp(argv[1],"-u")) || !(strcmp(argv[1],"--user")) ) {

		// La funcionalidad deseada es acceder como usuario
		// Se pide y verifica usuario y contraseña

		string usuario = pedir_usuario();
		string password = pedir_contrasena();
		bool es_usuario = confirmar_usuario(0, usuario, password); // el 0 indica que se intenta acceder como usuario

		/* if (es_usuario){
			ACA COMIENZA EL ACCESO COMO USUARIO
		 }*/
		return 0;
	}

	cout << "Uso: voto_electronico -h\n";	// Mal uso de las opciones

	return 0;
}


void mostrar_ayuda(){
	cout << "*************************************************************\n";
	cout << "Voto Electronico - Ayuda\n\n" << "Opciones:\n";
	cout << "-h, --help: Muestra esta ayuda\n";
	cout << "-u, --user: Login al sistema en calidad de usuario\n";
	cout << "-a, --admin: Login al sistema en calidad de administrador\n\n";
	cout << "Consulte el manual para mas informacion\n";
	cout << "*************************************************************\n";
}

string pedir_usuario(){
	char user[20];
	cout<<("Usuario: ");
	scanf("%s",user);
	return user;
}

string pedir_contrasena(){
	char pass[20];
	cout<<("Contraseña: ");
	system("stty -echo");
	scanf("%s",pass);
	system("stty echo");
	printf("\nEscribiste (esto es para probar, desp se borra del codigo): ");	// ESTO DESP SE BORRA, ES PARA PROBAR
	printf("%s\n",pass);
	return pass;
}

bool confirmar_usuario(int,string, string){
	cout<<"ACA SE CONFIRMA EL ACCESO\n";
}
