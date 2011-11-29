/* 
 * File:   RSA.cpp
 * Author: migue
 * 
 * Created on 19 de noviembre de 2011, 16:22
 */

#include "RSA.h"
#include <math.h>
#include <iostream>
using namespace std;

static EnteroLargo ultimo_valor_aleatorio=10001;


RSA::RSA() {
    
    this->generarCLaves();
    this->determinarCantidadChar();
    this->modo_encriptar=true;
    
}

RSA::RSA(Clave privada,Clave publica) {
    
    this->N=privada.N();
    this->D=privada.D();
    this->E=publica.E();    
    
    this->determinarCantidadChar();
    this->modo_encriptar=true;
    
}

int RSA::generarAleatorio(){
    
    //return rand();
    
    ultimo_valor_aleatorio +=2; 
    
    return ultimo_valor_aleatorio;
    
}



void RSA::generarCLaves(){
    do{
        //Se genera el numero Primo P
        do{
            this->P = this->generarAleatorio();

        }while(!this->esPrimo(this->P));


        //Se genera el numero Primo Q
        do{
            this->Q = this->generarAleatorio();

            while (this->P == this->Q){
                this->Q = this->generarAleatorio();
            }
        }while (!this->esPrimo(this->Q));


        this->N = this->P * this->Q;
        this->phiN=(this->P - 1) * (this->Q -1);

        this->generarD();

    /*
     * Modificar el codigo en esta parte, para contemplar el caso
     * que no se genere E y que se retorne falso
     */
   }while(!this->generarE(this->D,this->phiN));
      
        
    
}

void RSA::generarD(){
    
    do{
        this->D= this->generarAleatorio();
    }while(!this->esMCDUno(this->D,this->phiN));  
    
    
}

bool RSA::generarE(EnteroLargo d,EnteroLargo phi_n){
    
    EnteroLargo a[3]={0,0,0},b[3]={0,0,0},m,aux;
    int i;
    bool e_generado=false;
    
    a[0]=1;  
    a[1]=0;
    a[2]=EnteroLargo(phi_n);
    
    b[0]=0;
    b[1]=1;
    b[2]=EnteroLargo(d);
    
    do{
        
        m = a[2] / b[2];
        
        for (i=0;i<3;i++){
            
            aux=b[i];
            b[i]=a[i]-m*b[i];
            a[i]=aux;
            
        }
        
        
    }while (!(b[2]==1 || b[2]==0));
    
    
    if( b[2]==1){
        e_generado=true;
        this->complementoEspecial(b[1],phi_n);
        this->E=EnteroLargo(b[1]);   
    }else
        cout<<"E no generado con d:"<<d<<" y phi(N):"<<phi_n<<endl;
    
    /*
    EnteroLargo semilla=1;
    EnteroLargo n=0;
    
    while (!e_generado){
        semilla=semilla -1;
        
        e_generado = (semilla * d ) %  phi_n == 1;
        
        
    }
    
    this->E=semilla*d;*/
        
    return e_generado;
    
}

int RSA::tamanioEnteroUtilizado(){
    
    return sizeof(EnteroLargo)*8;
    
}

void RSA::complementoEspecial(EnteroLargo& a,const EnteroLargo &phi_n){
    
    EnteroLargo anulador=0x01,aux,_xor=0;
    anulador = anulador << (this->tamanioEnteroUtilizado() -1);
    
    aux= anulador & a;
    _xor = _xor -1;
    
    if( aux != 0){
     
        a = a ^ _xor;
        a = a + 1;
       
        a= 2*phi_n -(a % phi_n);
    }
    
    
}


bool RSA::esMCDUno(const EnteroLargo& a, const EnteroLargo& b){
    bool resultado=true;
    
    EnteroLargo mayor,menor,aux;
    if (a == b){
        resultado = false;
    }else if (a > b){
        mayor = a;
        menor = b;      
    }else{
        mayor = b;
        menor = a;
    }
    
    if (resultado){
        
        while (menor != 0 ){
            aux = menor;
            menor = mayor % menor;
            mayor = aux;
            
        }
        
        resultado = (mayor == 1);       
    }
    
    return resultado;
}

bool RSA::esPrimo(const EnteroLargo& numero){
    bool es_primo;
    EnteroLargo i=3;
    
    es_primo = (numero % 2) != 0;
    
    while (i < numero & es_primo){
        
        es_primo = (numero % i)!= 0;
        i=i+2;
        
    }
    
    return es_primo;
    
}

EnteroLargo RSA::calcularModulo(EnteroLargo a, EnteroLargo b, EnteroLargo q){
    
    EnteroLargo desplazador=0x001;
    EnteroLargo resultado=1;
    EnteroLargo q_en_bits,mod_anterior;
    int cant_bits=sizeof(EnteroLargo)*8;
    
    mod_anterior = a % q;
    
    for (int i=0;i<cant_bits-1;i++){
        q_en_bits = desplazador & b;
        desplazador = desplazador * 2;
        
        if (q_en_bits != 0){
            
            resultado = (mod_anterior*resultado) % q;
        
        }
            mod_anterior*=mod_anterior ;
            mod_anterior= mod_anterior % q;
    }
    
    
    resultado = resultado % q; 
    
    return resultado;    
    
}

void RSA::determinarCantidadChar(){
    
    bool uno_encontrado =false;
    int cant_bits= sizeof(EnteroLargo)*8;
    
    EnteroLargo desplazador = 0x001;
    EnteroLargo n=this->N;

    
    desplazador = desplazador << cant_bits-1;
    
    cant_bits=cant_bits + 1;
    
    while (!uno_encontrado && desplazador > 1 ){
        
        uno_encontrado = (desplazador & n ) != 0;
        desplazador = desplazador >> 1;
        cant_bits= cant_bits-1;
    }
    
    
    this->cantidadChar= cant_bits / 8;
    
}


Clave RSA::getClavePrivadaActual(){
    return Clave(this->D,this->N);
}

Clave RSA::getClavePublicaActual(){
    return Clave(this->E,this->N);
}

void RSA::setClaves(Clave privada,Clave publica){
    
    if(privada.N()!=publica.N())
        cout<<"Error No coincide parametro para las clave publica y privada."<<endl;
    
    this->N=privada.N();
    this->D=privada.D();
    this->E=publica.E();    
    
    this->determinarCantidadChar();
    
}

string RSA::convertirAString(EnteroLargo* numeros, int cant){
    
    int tam_char=sizeof(char)*8;
    EnteroLargo anulador=0xff,enteroActual=0;

    
    string mensaje;
    int cant_char;
    int cantidad_char_entero=0;
    if(this->modo_encriptar){
        cantidad_char_entero=this->cantidadChar+1;
    }else{
        cantidad_char_entero=this->cantidadChar;        
    }
    
    cant_char=cantidad_char_entero * cant;
    
    //int indice_caracter=0,indice_entero=0,contador_ind_ent=0;
    mensaje.resize(cant_char);
    enteroActual=numeros[0];
    
    unsigned char caracter;

    
    for(int i=0; i < cant -1 && cant > 1 ;i++){
        
        enteroActual = numeros[i];
        
        for(int indice_char=0;indice_char<cantidad_char_entero;indice_char++){
            
            caracter = enteroActual & anulador;
            enteroActual = enteroActual >> tam_char;
            int indice = i*cantidad_char_entero+cantidad_char_entero-indice_char-1;
            mensaje[indice]=caracter;
            
        }
        
        
         
        
    }
    
    /*
     * Se maneja al ultimo bloque por separado
     * ya que puede ser que no tenga todos caractes validos
     */
    enteroActual=numeros[cant-1];
    int char_validos_ultimo=0;
    bool ultimo_char_leido=false;
    
    string parte_final;
    parte_final.resize(cantidad_char_entero);
    
    for(int indice_char=0;indice_char<cantidad_char_entero && !ultimo_char_leido;indice_char++){
            
            caracter = enteroActual & anulador;
            enteroActual = enteroActual >> tam_char;
            
            if (caracter != 0){
                int indice= cantidad_char_entero - indice_char - 1;
                parte_final[indice]=char(caracter);
                char_validos_ultimo++;
                
            }else{
                ultimo_char_leido=true;
            }
                
            
        }
    
    int dif_chars= cantidad_char_entero - char_validos_ultimo;
    
    const char *c_parte_final=parte_final.c_str();
    const char *c_mensaje=mensaje.c_str();
    
     if (dif_chars!=0){
        mensaje.resize(cant_char-dif_chars);

    }
    
    
    for(int i=0;i<char_validos_ultimo;i++){
            mensaje[mensaje.size() -i -1]=parte_final[cantidad_char_entero-i-1];
        }
    
    
    //delete numeros;
    
    return mensaje;
    
    
}

EnteroLargo* RSA::convertirAEnteroLargo(std::string mensaje, int& cant){
    
    int tam_char=sizeof(char)*8;
    int cant_char=mensaje.size();
    int cant_ent_largos;
    EnteroLargo* enteros;
    EnteroLargo aux=0,anulador=0xff;
    
    int cantidad_char_entero=0;
    if(!this->modo_encriptar){
        cantidad_char_entero=this->cantidadChar+1;
    }else{
        cantidad_char_entero=this->cantidadChar;        
    }
    
    cant_ent_largos=cant_char / cantidad_char_entero;
    
    if (cant_char % cantidad_char_entero !=0)
        cant_ent_largos+=1;
    
    enteros=new EnteroLargo[cant_ent_largos];
    
    int indice_entero=0;
    int contador_indice_ent=0;
    for(int i=0;i<cant_char;i++){
        
        aux+= (EnteroLargo(mensaje[i])) & anulador;
        aux = aux << tam_char;

        contador_indice_ent++;
        if(contador_indice_ent >= cantidad_char_entero && indice_entero<cant_ent_largos){
            contador_indice_ent=0;
            aux=aux >> tam_char;
            enteros[indice_entero]=0;
            
            if(aux >= this->N)
                cout<<"         ERROR en calculo de Entero:"<<endl;
            
            enteros[indice_entero]=aux;
            aux=0;
            indice_entero++;
        }
    }
    
    if (contador_indice_ent!=0){
        aux=aux >> tam_char;
        enteros[cant_ent_largos-1]=aux;
    }
    cant=cant_ent_largos;
    return enteros;
    
}

string RSA::encriptar(std::string mensaje){
    
    this->modo_encriptar=true;
    return this->realizarProceso(mensaje,this->E);
    
}

string RSA::desencriptar(std::string msj_encrip){
    
    this->modo_encriptar=false;
    return this->realizarProceso(msj_encrip,this->D);
    
}

string RSA::realizarProceso(string mensaje, const EnteroLargo &clave){
    
    EnteroLargo *mensaje_ent=NULL,*mensaje_encript=NULL;
    int cant_elem;
    
    mensaje_ent=this->convertirAEnteroLargo(mensaje,cant_elem);
    
    mensaje_encript=new EnteroLargo[cant_elem];
    
    for (int i=0; i < cant_elem;i++){
        
        mensaje_encript[i]=this->calcularModulo(mensaje_ent[i],clave,this->N);
    }
    
    string msj_encriptado = this->convertirAString(mensaje_encript,cant_elem);
    
    return msj_encriptado;
}

EnteroLargo RSA::romper(EnteroLargo e, EnteroLargo n)
{
	EnteroLargo p, q, clavePrivada = 0, funcionEuler;
	RSA rsa;


	 rsa.getClavePublicaActual().E();

	    /*
	     * Metodo que devuelve la clave PRIVADA que se esta utilizando
	     */
	    Clave getClavePrivadaActual();


	Factorizacion::fermat(n, p, q);

	funcionEuler = (p-1)*(q-1);

	if(rsa.generarE(e, funcionEuler))
		clavePrivada = rsa.E;

	//(1/e) % funcionEuler;

	return clavePrivada;
}

RSA::~RSA() {
}

