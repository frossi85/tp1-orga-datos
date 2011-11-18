#include "Kasiski.h"


//inicialización de los atributos

char* Kasiski::bufferCriptograma = NULL;

size_t Kasiski::tamanioBuffer = 0;

vector<Kasiski::longitudPosible> Kasiski::longPosibles;

string aux[] = {"lista", "eleccion", "elección", "distrito", "votos", "candidato"};
const vector<string> Kasiski::palabrasConocidas(aux, aux + (sizeof(aux) / sizeof(aux[0])));

const unsigned int Kasiski::MIN_LONG_CADENA = 3;

/////////////////////////////////
/////////////////////////////////

//implementaciones

bool Kasiski::LeerCriptograma(const char* rutaCriptograma){

    ifstream criptograma(rutaCriptograma);

    //calcula el tamaño del archivo para reservar memoria para el buffer
    size_t principio = criptograma.tellg();
    criptograma.seekg (0, ios::end);
    size_t fin = criptograma.tellg();
    criptograma.close();
    tamanioBuffer = fin - principio;
    bufferCriptograma = new char[tamanioBuffer];
    if(bufferCriptograma == NULL) return false;

    //carga la información en el buffer y cierra el archivo
    criptograma >> bufferCriptograma;
    criptograma.close();
    
    return true;
}

/////////////////

unsigned long Kasiski::MCD(unsigned long x, unsigned long y){

    if (!x) return y;
    while (y > 0) {
        unsigned long aux = x % y;
        x = y;
        y = aux;
    }
    
    return x;
}

///////////////////

bool Kasiski::AgregarLongitud(unsigned long longitud){

    for(unsigned int i = 0; i < longPosibles.size(); i++){
        if(longitud == longPosibles[i].longitud){
            longPosibles[i].ocurrencias++;
            return true;
        }
    }

    longitudPosible nuevaLongitud;
    nuevaLongitud.longitud = longitud;
    nuevaLongitud.ocurrencias = 1;
    longPosibles.push_back(nuevaLongitud);
    
    return true;
}

//////////////////

bool Kasiski::ProcesarCadenasRepetidas(){

    unsigned long coincidencias;
    unsigned long longitud;
    for(unsigned long i = 0; i < tamanioBuffer; i++){
        for(unsigned long j = i + MIN_LONG_CADENA; j < tamanioBuffer; j++){
            coincidencias = 0;
            while(bufferCriptograma[i + coincidencias] == bufferCriptograma[j + coincidencias]){
                coincidencias++;
            }
            if(coincidencias >= MIN_LONG_CADENA){
                //calcula la distancia entre las cadenas (REVISAR ESTA CUENTA)
                unsigned long distancia = j - i + coincidencias;
                //calcular MCDs y agregar longitud
                if(longPosibles.size() == 0) AgregarLongitud(distancia);
                else{
                    for(unsigned long k = 0; k < longPosibles.size(); k++){
                        longitud = MCD(distancia, longPosibles[k].longitud);
                        AgregarLongitud(longitud);
                    }
                }
            }
        }
    }

    return true;
}

////////////////////

unsigned long Kasiski::ObtenerLongitudMasProbable(){

    unsigned long max = 0;
    unsigned int posicionDeMasProbable;
    for(unsigned int i = 0; i < longPosibles.size(); i++){
        if(longPosibles[i].ocurrencias > max){
            max = longPosibles[i].ocurrencias;
            posicionDeMasProbable = i;
        }
    }

    unsigned long longitudMasProbable = longPosibles[posicionDeMasProbable].longitud;

    longPosibles.erase(longPosibles.begin() + posicionDeMasProbable);

    return longitudMasProbable;
}

////////////////////

void Kasiski::LiberarMemoria(){

    if(bufferCriptograma != NULL)
        delete[] bufferCriptograma;
}

///////////////////

bool Kasiski::Romper(const char* rutaCriptograma, const char* rutaDestino){

    if(!LeerCriptograma(rutaCriptograma)) return false;

    if(!ProcesarCadenasRepetidas()) return false;

    unsigned long longClave = ObtenerLongitudMasProbable();

    /* aca habria que tratar al buffer como si estuviera organizado en
     longClave columnas, buscar el caracter mas frecuente de cada columna,
     y calculando la resta mod 26 (o 256?) entre ese caracter y el que debería
     reemplazarlo (espacio, o 'e'), y así obtener uno de los caracteres de la clave.
     Repetir longClave veces.
     Generar el archivo desencriptado con esa clave y buscar las palabras conocidas.
     Si no estan, seguir probando con otras posibilidades (o probar primero todas las
     posibilidades y despues buscar las palabras conocidas). */

    return true;
}

