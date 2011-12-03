#include "Kasiski.h"


//inicialización de los atributos

char* Kasiski::bufferCriptograma = NULL;

size_t Kasiski::tamanioBuffer = 0;

vector<Kasiski::longitudPosible> Kasiski::longPosibles;

string aux[] = {"Lista", "Eleccion", "Distrito", "Votos", "Candidato", "Cargo"};
const vector<string> Kasiski::PALABRAS_CONOCIDAS(aux, aux + (sizeof(aux) / sizeof(aux[0])));

char aux2[] = {' ', 'e', 'a'};
const vector<char> Kasiski::CARACTERES_FRECUENTES(aux2, aux2 + (sizeof(aux2) / sizeof(aux2[0])));

const unsigned int Kasiski::MIN_LONG_CADENA = 3;

const unsigned int Kasiski::LONG_ALFABETO = 128;

/////////////////////////////////
/////////////////////////////////

//implementaciones

bool Kasiski::LeerCriptograma(const char* rutaCriptograma){

    ifstream criptograma(rutaCriptograma);
    if(!criptograma.is_open()) return false;

    //calcula el tamaño del archivo para reservar memoria para el buffer
    criptograma.seekg (0, ios::end);
    tamanioBuffer = criptograma.tellg();
    bufferCriptograma = new char[tamanioBuffer];
    criptograma.seekg(0, ios::beg);
    if(bufferCriptograma == NULL) return false;

    //carga la información en el buffer y cierra el archivo
    criptograma.read(bufferCriptograma, tamanioBuffer);   
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
                unsigned long distancia = j - i;
                //calcular MCDs y agregar longitud
                if(longPosibles.size() == 0) AgregarLongitud(distancia);
                else{
                    unsigned long cantLongitudes = longPosibles.size();
                    for(unsigned long k = 0; k < cantLongitudes; k++){
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

void Kasiski::AgregarAListaDeFrecuencias(vector<caracterFrecuencia> *listaFrec, char caracter){

    for(unsigned int i = 0; i < listaFrec->size(); i++){
        if(caracter == listaFrec->at(i).caracter){
            listaFrec->at(i).frecuencia++;
            return;
        }
    }

    caracterFrecuencia nuevoCaracter;
    nuevoCaracter.caracter = caracter;
    nuevoCaracter.frecuencia = 1;
    listaFrec->push_back(nuevoCaracter);
}

////////////////////

char Kasiski::ObtenerCaracterMasFrecuente(vector<caracterFrecuencia>* listaFrec){

    unsigned long max = 0;
    unsigned int posicionDeMasFrecuente;
    for(unsigned int i = 0; i < listaFrec->size(); i++){
        if(listaFrec->at(i).frecuencia > max){
            max = listaFrec->at(i).frecuencia;
            posicionDeMasFrecuente = i;
        }
    }

    char caracterMasProbable = listaFrec->at(posicionDeMasFrecuente).caracter;

    listaFrec->erase(listaFrec->begin() + posicionDeMasFrecuente);

    return caracterMasProbable;
}

////////////////////

void Kasiski::Desencriptar(const vector<char> *clave, const char* rutaDestino){

    ofstream textoPlano(rutaDestino);

    //en la primera línea imprime la clave usada
    textoPlano << "Clave: ";
    for(unsigned int i = 0; i < clave->size(); i++)
        textoPlano << clave->at(i);

    textoPlano << endl << endl;

    //imprime el mensaje desencriptado
    char caracter;
    unsigned int j = 0;

    for(unsigned int i = 0; i < tamanioBuffer; i++){
        caracter = (bufferCriptograma[i] - clave->at(j)) % LONG_ALFABETO;
        textoPlano << caracter;

        if(j == clave->size() - 1) j = 0;
        else j++;
    }

    textoPlano.close();
}

////////////////////

int Kasiski::CantidadDeOcurrencias(const vector<string> palabras, const char* rutaOrigen){

    ifstream textoPlano(rutaOrigen);

    //calcula el tamaño del archivo para reservar memoria para el buffer
    size_t principio = textoPlano.tellg();
    textoPlano.seekg (0, ios::end);
    size_t fin = textoPlano.tellg();
    char *buffer = new char[fin - principio + 1];
    if(buffer == NULL) return false;

    //carga la información en el buffer y cierra el archivo
    textoPlano >> buffer;
    textoPlano.close();
    buffer[fin - principio] = '\0';

    int ocurrencias = 0;
    char *cadena = strtok(buffer, " .,;:-+*¿?¡!'()$#%&/=ºª\"\\");
    while(cadena != NULL){
        for(unsigned int i = 0; i < PALABRAS_CONOCIDAS.size(); i++)
            if(strcmp(cadena, PALABRAS_CONOCIDAS[i].c_str())) ocurrencias++;

        cadena = strtok(NULL, " .,;:-+*¿?¡!'()$#%&/=ºª\"\\");
    }

    delete[] buffer;
    return ocurrencias;
}

///////////////////

void Kasiski::LiberarMemoria(){

    if(bufferCriptograma != NULL)
        delete[] bufferCriptograma;
}

///////////////////

bool Kasiski::Romper(const char* rutaCriptograma, const char* rutaDestino){

    if(!LeerCriptograma(rutaCriptograma)) return false;

    if(!ProcesarCadenasRepetidas()) return false;

    unsigned long longClave = ObtenerLongitudMasProbable();

    //se trata al buffer como si estuviera organizado en longClave columnas
    vector<caracterFrecuencia> frecuencias;
    unsigned long j;
    char carMasFrecuente;
    vector<char> *posibleClave = new vector<char>(longClave);
    vector<int> ocurrencias;
    ocurrencias.reserve(CARACTERES_FRECUENTES.size());
    char* ruta = NULL;
    unsigned int textoMasProbable = 0;
    unsigned int maxCombinaciones = CARACTERES_FRECUENTES.size();

    for(unsigned int combinacion = 0; combinacion < maxCombinaciones; combinacion++){
        for(unsigned long i = 0; i < longClave; i++){

            //analiza frecuencias en la columna i
            j = 0;
            frecuencias.clear();
            while(i + j*longClave < tamanioBuffer){
                AgregarAListaDeFrecuencias(&frecuencias, bufferCriptograma[i + j*longClave]);
                j++;
            }

            //calculando la resta mod 26 (o 256?) entre el caracter más frecuente y el que debería
            //reemplazarlo (espacio, 'e' o 'a'), se obtiene uno de los caracteres de la clave.
            carMasFrecuente = ObtenerCaracterMasFrecuente(&frecuencias);
            posibleClave->at(i) = (carMasFrecuente - CARACTERES_FRECUENTES[combinacion]) % LONG_ALFABETO;
        }
        //genera el archivo desencriptado con esa clave
        ruta = new char[strlen(rutaDestino) + 1];
        sprintf (ruta, "%s%i", rutaDestino, combinacion);
        Desencriptar(posibleClave, ruta);
        //busca las palabras conocidas
        ocurrencias[combinacion] = CantidadDeOcurrencias(PALABRAS_CONOCIDAS, ruta);
        if(ocurrencias[combinacion] > ocurrencias[textoMasProbable])
            textoMasProbable = combinacion;

        delete ruta;
    }

    //Al final borra todos los archivos menos el que tenga el mayor numero de
    //ocurrencias de palabras conocidas (si todos tienen 0 ocurrencias, deja el
    //primer archivo generado, que probablemente sea el más cercano al buscado).
    for(unsigned int combinacion = 0; combinacion < maxCombinaciones; combinacion++){
        if(combinacion != textoMasProbable){
            ruta = new char[strlen(rutaDestino) + 1];
            sprintf (ruta, "%s%i", rutaDestino, combinacion);
            remove(ruta);
            delete ruta;
        }
    }

    //le saca el número del final al textoMasProbable
    ruta = new char[strlen(rutaDestino) + 1];
    sprintf (ruta, "%s%i", rutaDestino, textoMasProbable);
    char *rutaNueva = new char[strlen(rutaDestino)];

    strncpy ( rutaNueva, ruta, strlen(rutaDestino) );

    if(!rename ( ruta, rutaNueva )) return false;

    delete ruta;
    delete rutaNueva;
    delete posibleClave;
    LiberarMemoria();
    return true;
}