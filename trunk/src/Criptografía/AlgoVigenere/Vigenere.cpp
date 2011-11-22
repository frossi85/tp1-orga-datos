/*
 * File:   Vigenere.cpp
 * Author: martin
 *
 */

#include <string>
#include "Vigenere.h"


Vigenere::Vigenere() {
	this->clave = "abc";
    this->long_alfabeto = 128;
}


Vigenere::Vigenere(const Vigenere& orig) {
    this->clave = orig.clave;
    this->long_alfabeto = orig.long_alfabeto;
}


Vigenere::~Vigenere() {
}


string Vigenere::getClave() {
    return this->clave;
}


void Vigenere::setClave(string clave) {
    this->clave = clave;
}


/*
 *  Realiza el cifrado del archivo de texto "ruta_arch_aCifrar" (ej: ./Reporte.txt) y lo guarda en un archivo de texto
 * "ruta_arch_cifrado" (ej: ./ReporteCifrado.txt)
 *
 * Pre: El archivo a cifrar debe existir. Se debe setear la clave con "setClave", de lo contrario se usara la
 * asignada por defecto (abc123).
 *
 * Pos: Se crea o reemplaza el archivo cifrado. Retorna true si la operacion tuvo exito. En caso contrario
 * retorna false.
 */
bool Vigenere::cifrarArchivo(string ruta_arch_aCifrar, string ruta_arch_cifrado) {

	/* Abro los archivos que voy a utilizar */
	ifstream stream_aCifrar (ruta_arch_aCifrar.c_str(), ios::in);
	if(!stream_aCifrar.is_open()) {
		return false;
	}
	ofstream streamCifrado (ruta_arch_cifrado.c_str(), ios::out  | ios::trunc);
	if(!streamCifrado.is_open()) {
		stream_aCifrar.close();
		return false;
	}

	/* Obtengo la cantidad de caracteres */
	stream_aCifrar.seekg(0, ios::end);
	int long_mensaje = stream_aCifrar.tellg();
	stream_aCifrar.seekg(0, ios::beg);

	/* Creo un buffer para levantar todos los caracteres */
	char *buffer;
	buffer = new char[long_mensaje];

	/* Levanto todos los caracteres */
	stream_aCifrar.read(buffer,long_mensaje);

	/* Encripto */
	//string criptograma = this->cifrarCadena(buffer);



    string criptograma;
    int long_clave = this->clave.length();
    int pos = 0;
    for(int i=0;i<long_mensaje;i++) {
        int caracter = ((buffer[i] + this->clave[pos]) % this->long_alfabeto);
        pos++;
        if(pos >= long_clave)   pos = 0;
        criptograma += caracter;
    }



	/* Chequeo que la longitud de lo encriptado sea igual a lo leido originalmente */
	if (criptograma.length() != long_mensaje) {
		/* Si no lo era cierro los archivos y retorno false. De haber seguido, no se podria haber abierto
		 * el archivo cifrado ya que el sistema no reconoce la codificacion.
		 */
		delete[] buffer;
		stream_aCifrar.close();
		streamCifrado.close();
		return false;
	}

	/* Se prosigue a escribir el criptograma en el archivo cifrado */
	streamCifrado.write(criptograma.c_str(),long_mensaje);


	delete[] buffer;
	stream_aCifrar.close();
	streamCifrado.close();
	return true;
}


/*
 *  Realiza el desencriptado del archivo de texto "ruta_arch_aDescifrar" (ej: ./ReporteCifrado.txt) y lo guarda
 *  en un archivo de texto "ruta_arch_descifrado" (ej: ./ReporteDescifrado.txt)
 *
 * Pre: El archivo a descifrar debe existir. Para descifrar correctamente se debe setear la clave (si se cambio en el proceso)
 * igual con la que se cifro.
 *
 * Pos: Se crea o reemplaza el archivo descifrado. Retorna true si la operacion tuvo exito. En caso contrario
 * retorna false.
 */
bool Vigenere::descifrarArchivo(string ruta_arch_aDescifrar, string ruta_arch_descifrado) {

	/* Abro los archivos que voy a utilizar */
	ifstream stream_aDescifrar (ruta_arch_aDescifrar.c_str(), ios::in);
	if(!stream_aDescifrar.is_open()) {
		return false;
	}
	ofstream streamDescifrado (ruta_arch_descifrado.c_str(), ios::out | ios::trunc);
	if(!streamDescifrado.is_open()) {
		stream_aDescifrar.close();
		return false;
	}

	/* Obtengo la cantidad de caracteres */
	stream_aDescifrar.seekg(0, ios::end);
	int long_criptograma = stream_aDescifrar.tellg();
	stream_aDescifrar.seekg(0, ios::beg);

	/* Creo un buffer para levantar todos los caracteres */
	char *buffer;
	buffer = new char[long_criptograma];

	/* Levanto todos los caracteres */
	stream_aDescifrar.read(buffer,long_criptograma);

	/* Desencripto */
	//string mensaje = this->descifrarCadena(buffer);



    string mensaje;
    int long_clave = this->clave.length();
    int pos = 0;
    for(int i=0;i<long_criptograma;i++) {
        int caracter = ((buffer[i] - this->clave[pos]) % this->long_alfabeto);
        if (caracter < 0) caracter += this->long_alfabeto;
        pos++;
        if(pos >= long_clave)   pos = 0;
        mensaje += caracter;
    }



	/* Chequeo que la longitud de lo desencriptado sea igual a lo leido originalmente */
	if (mensaje.length() != long_criptograma) {
		/* Si no lo era cierro los archivos y retorno false. De haber seguido, no se podria haber abierto
		 * el archivo descifrado ya que el sistema no reconoce la codificacion.
		 */
		delete[] buffer;
		stream_aDescifrar.close();
		streamDescifrado.close();
		return false;
	}

	/* Se prosigue a escribir el mensaje en el archivo descifrado */
	streamDescifrado.write(mensaje.c_str(),long_criptograma);

	delete[] buffer;
	stream_aDescifrar.close();
	streamDescifrado.close();
	return true;
}


/* ESTO DESPUES SE BORRA. ES PARA PRUEBAS RAPIDAS */
string Vigenere::cifrarCadena(string mensaje) {
    string criptograma;
    int long_clave = this->clave.length();
    int long_mensaje = mensaje.length();
    int pos = 0;
    for(int i=0;i<long_mensaje;i++) {
        int caracter = ((mensaje[i] + this->clave[pos]) % this->long_alfabeto);
        pos++;
        if(pos >= long_clave)   pos = 0;
        criptograma += caracter;
    }
    return criptograma;
}

/* ESTO DESPUES SE BORRA. ES PARA PRUEBAS RAPIDAS */
string Vigenere::descifrarCadena(string criptograma) {
    string mensaje;
    int long_clave = this->clave.length();
    int long_criptograma = criptograma.length();
    int pos = 0;
    for(int i=0;i<long_criptograma;i++) {
        int caracter = ((criptograma[i] - this->clave[pos]) % this->long_alfabeto);
        if (caracter < 0) caracter += this->long_alfabeto;
        pos++;
        if(pos >= long_clave)   pos = 0;
        mensaje += caracter;
    }
    return mensaje;
}

/* ESTO DESPUES SE BORRA. ES PARA PRUEBAS RAPIDAS */
void Vigenere::ejecutarTestDirecto() {

    string cad_aux;
    string criptograma;
    string mensaje;

    cout << "Ingrese una clave: ";
    cin >> cad_aux;
    this->setClave(cad_aux);
    cout << "Su clave es: " << this->getClave() << endl;

    do {
        cout << endl << "Ingrese un mensaje: ";
        cin >> mensaje;
        criptograma = this->cifrarCadena(mensaje);
        cout << "El criptograma es: " << criptograma << endl;
        cout << "El desencriptado es: " << this->descifrarCadena(criptograma) << endl;
        cout << "¿Desea probar con otro mensaje? (S/N): ";
        cin >> cad_aux;
    } while (cad_aux[0] == 'S');

    return;
}


/* TEST */
void Vigenere::ejecutarTestArchivo() {

    string clave;
    string ruta_origen;
    string ruta_destino;
    string cad_aux;
    bool exito;

    cout << "Ingrese una clave: ";
    cin >> clave;
    this->setClave(clave);
    cout << "Su clave es: " << this->getClave() << endl;

    do {
        cout << endl << "Ingrese la ruta del archivo a cifrar: ";
        cin >> ruta_origen;
        cout << "Ingrese la ruta donde se guardara el archivo cifrado: ";
        cin >> ruta_destino;
        exito = this->cifrarArchivo(ruta_origen,ruta_destino);
        if (!exito) {
        	cout << "NO SE PUDO CIFRAR CORRECTAMENTE";
        	return;
        }
        cout << "ARCHIVO CIFRADO CORRECTAMENTE" << endl;
        cout << endl << "Ingrese la ruta del archivo a descifrar: ";
        cin >> ruta_origen;
        cout << "Ingrese la ruta donde se guardara el archivo descifrado: ";
        cin >> ruta_destino;
        exito = this->descifrarArchivo(ruta_origen,ruta_destino);
        if (!exito) {
        	cout << "NO SE PUDO DESCIFRAR CORRECTAMENTE";
        	return;
        }
        cout << "ARCHIVO DESCIFRADO CORRECTAMENTE" << endl;
        cout << endl << "¿Desea probar con otro archivo? (S/N): ";
        cin >> cad_aux;
    } while (cad_aux[0] == 'S');

    return;
}
