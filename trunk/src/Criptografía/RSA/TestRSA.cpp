/* 
 * File:   TestRSA.cpp
 * Author: migue
 * 
 * Created on 19 de noviembre de 2011, 18:30
 * 
 * IMPORTANTE!!!
 * 
 * No modificar nada de este test.
 * Esta hecho para que sea clase amiga de RSA, y por eso pueden 
 * dar errores de que no se encuentren las funciones y atributos 
 * que se estan accediendo.
 * 
 * 
 */

#include "TestRSA.h"
#include <iostream>


using namespace std;

TestRSA::TestRSA() {
    this->rsa = new RSA(Clave(0,0),Clave(0,0));
    
}

void TestRSA::iniciar(){
    this->errores=0;
    
    if (!this->TestEsPrimo()){
        this->msjError("esPrimo");
        this->errores++;
    }
    else
        this->msjTestExitoso();
    
    if (!this->TestMCDesUno()){
        this->msjError("esMCDUno");
        this->errores++;
    }
    else
        this->msjTestExitoso();
    
    if(!this->TestGenerarE()){
        this->msjError("GenerarE");
        this->errores++;
    }
    else
        this->msjTestExitoso();
    
    if(!this->TestCalcularModulo()){
        this->msjError("CalcularModulo");
        this->errores++;
    }
    else
        this->msjTestExitoso();
    
    if(!this->TestDeterminarCantChar()){
        this->msjError("DeterminarChar");
        this->errores++;
    }
    else
        this->msjTestExitoso();
    
    if(!this->TestConvertirAEnteros()){
        this->msjError("ConvertirAEnteros");
        this->errores++;
    }
    else
        this->msjTestExitoso();
    
    /*
     * A partir de aqui comienzan las pruebas fuertes para la Clase RSA
     */
    
    
    if(!this->TestComprobacionNumeros()){
        this->msjError(", comprobracion de Numeros");
        this->errores++;
    }
    else
        this->msjTestExitoso();
    
    if(!this->TestCalcularModuloReal()){
        this->msjError("calcularModulo");
        this->errores++;
    }
    else
        this->msjTestExitoso();
    
    if(!this->TestEncriptacionPorBloque()){
        this->msjError("calcularModulo");
        this->errores++;
    }
    else
        this->msjTestExitoso();
    
    if(!this->TestComprobacionConversionCorrecta()){
        this->msjError("calcularModulo");
        this->errores++;
    }
    else
        this->msjTestExitoso();
    
    
    if(!this->TestEncriptacion()){
        this->msjError("Des/Encriptacion");
        this->errores++;
    }
    else
        this->msjTestExitoso();
    
    if(this->errores!=0){
        cout<<"****************************************"<<endl;
        cout<<"Fallaron "<<this->errores<<" Test"<<endl;
        cout<<"****************************************"<<endl;
    }else{
        
        cout<<"Todos los Test Pasaron Correctamente"<<endl;
    }
        
    
}

bool TestRSA::TestEsPrimo(){
    
    bool error_encontrado=false;
    
    
    this->msjInicioTest("esPrimo");
    
    
    EnteroLargo enteros[]={3,5,7,11,17};
    
    for (int i=0;i<5  && !error_encontrado ;i++){
        if(this->rsa->esPrimo(enteros[i])==false){
            cout<<"Error con el numero "<<enteros[i]<<endl;
            error_encontrado=true;
        }
        
    }
    
    EnteroLargo no_primos[]={2,8,10,30,81};
    
    for (int i=0;i<5  && !error_encontrado ;i++){
        if(this->rsa->esPrimo(no_primos[i])==true){
            cout<<"Error con el numero "<<no_primos[i]<<endl;
            error_encontrado=true;
        }
        
    }
   
    return !error_encontrado;
}

bool TestRSA::TestMCDesUno(){
    
    EnteroLargo a[]={5,8,9, 10,34};
    EnteroLargo b[]={6,9,16,21,41};
    
    bool error_encontrado=false;
    
    
    this->msjInicioTest("esMCDUno");
    
    for(int i=0;i<5 && !error_encontrado;i++){
        if(!this->rsa->esMCDUno(a[i],b[i])){
         cout<<"Error con "<<a[i]<<" y "<<b[i]<<" en metodo MCDUno"<<endl;
         error_encontrado=true;
        }
    }
    
    EnteroLargo c[]={7,10,14,16,25};
    EnteroLargo d[]={7,5,7, 8, 5};
    
    for(int i=0;i<5 && !error_encontrado;i++){
        if(this->rsa->esMCDUno(c[i],d[i])){
         cout<<"Error con "<<c[i]<<" y "<<d[i]<<" en metodo MCDUno"<<endl;
         error_encontrado = true;
        }
    }
    return !error_encontrado;
}

bool TestRSA::TestGenerarE(){
    
    
    this->msjInicioTest("GenerarE");
    
    #define cant_pruebas_genE 6
    bool error_encontrado=false;
    
    EnteroLargo a[cant_pruebas_genE]={157,550,5001,201,913,3000};//,5043,5061};
    EnteroLargo q[cant_pruebas_genE]={2668,1759,523003,3007,3921,70021};//,25050016,25542900};
    
    for (int i=0;i < cant_pruebas_genE ;i++){
        if(!this->rsa->generarE(a[i],q[i])){
            cout<<"Error con "<<a[i]<<" y "<<q[i]<<" en metodo GenerarE"<<endl;

            
            error_encontrado = true;
        }

        cout<<"a: "<<a[i]<<" q:"<<q[i]<<" e:"<<this->rsa->E<<endl;

                  
    }
    
    return !error_encontrado;
}

bool TestRSA::TestCalcularModulo(){
    
    
    this->msjInicioTest("CalcularModulo");
    
    int cant=5;
    
    bool error_encontrado=false;
    EnteroLargo a[]={77,217,815,1219,635};
    EnteroLargo b[]={103,17,17,157,157};
    EnteroLargo q[]={138,2773,2773,2773,2773};
    EnteroLargo res[]={71,1219,635,217,815};
    EnteroLargo res_aux;
    
    for (int i=0;i<cant;i++){
        res_aux=this->rsa->calcularModulo(a[i],b[i],q[i]);
        if(res[i]!=res_aux){
            cout<<"Error en metodo Calcular Modulo"<<endl;
            cout<<"a: "<<a[i]<<"  b:"<<b[i]<<"  q:"<<q[i]<<endl;
            cout<<"Resultado Esperado: "<<res[i]<<endl;
            cout<<"Resultado Encontrado: "<<res_aux<<endl<<endl;
            error_encontrado =true;
        }
        
    }
    
    
    return !error_encontrado;
    
    
}

bool TestRSA::TestDeterminarCantChar(){
    
    
    this->msjInicioTest("DeterminarChar");
    
    bool error_encontrado =false;
    int cant_pruebas=4;
    Clave *publica= new Clave[cant_pruebas];
    Clave *privada= new Clave[cant_pruebas];
    int *cant_esperada=new int[cant_pruebas];
    
    EnteroLargo a1=5000,a2=300000000;
    
    a1*=1000000;
    a2*=1000000;
    
    cant_esperada[0]=2; privada[0].setN(140000);
    cant_esperada[1]=4; privada[1].setN(a1);
    cant_esperada[2]=6; privada[2].setN(a2);
    cant_esperada[3]=3; privada[3].setN(17000000);
    
    for(int i=0;i<cant_pruebas;i++)
        publica[i].setN(privada[i].N());
    
    
    
    for(int i=0;i<cant_pruebas;i++){

        this->rsa->setClaves(privada[i],publica[i]);

        if(this->rsa->cantidadChar!=cant_esperada[i]){
            error_encontrado = true;
            cout<<"Error en metodo DeterminarChar"<<endl;
            cout<<"Esperado: "<<cant_esperada[i]<<endl;
            cout<<"Encontrado: "<<this->rsa->cantidadChar<<endl<<endl;

        }
    }
    
    delete[] cant_esperada;
    delete[] publica;
    delete[] privada;
    
    return !error_encontrado;
}

bool TestRSA::TestConvertirAEnteros(){
    
    this->msjInicioTest("ConvertirAEntero");
    
    bool error_encontrado = false;
    
    Clave privada(0,17000000);
    Clave publica(0,privada.N());
    this->rsa->setClaves(privada,publica);
    int cant_char = this->rsa->cantidadChar;
    int cant_elem;
    EnteroLargo N;
    
    N=this->rsa->N;
    
#define cant_pruebas_conv 8
    
    string mensaje[cant_pruebas_conv];//("ABCDEFG 012345 HIJKLMNOPQRSTUVWXYZ 012");
    
    mensaje[0]="HOLA a todos";
    mensaje[1]="Llevo mas de 12 horas programando";
    mensaje[2]="Tengo Suenio";
    mensaje[3]="El vencido no esta del todo vencido hasta que le cierran la boca";
    mensaje[4]="Hace mucho calor";
    mensaje[5]="0123456789 numeros";
    mensaje[6]="Ella tiene que trabajar";
    mensaje[7]="No se que carajo escribir";

    for(int i=0; i< cant_pruebas_conv;i++){
        EnteroLargo *enteros;
        this->rsa->modo_encriptar=true;
        enteros = this->rsa->convertirAEnteroLargo(mensaje[i],cant_elem);


        for(int j=0;j<cant_elem && j < 8;j++){

            if (enteros[j]>=N){
                error_encontrado = true;
                cout<<"Entero: "<<enteros[j]<<" es mayor/igual que N:"<<N<<endl;
     
            }
            
            
        }

        string msj_resultante;
        
        this->rsa->modo_encriptar=false;
        
        msj_resultante = this->rsa->convertirAString(enteros,cant_elem);


        if(mensaje[i] != msj_resultante){
            this->msjError("Convertir");
            this->mostrarError(mensaje[i],msj_resultante);
            error_encontrado=true;

        }
    }
    
    
    return !error_encontrado;
    
}


bool TestRSA::TestCalcularModuloReal(){
    
    this->msjInicioTest("CalcularModulo Real");
    
    bool error_encontrado = false;
    
    int cant_pruebas = 20;
    
    this->cargarRSACompleto();
   
    
    EnteroLargo num_aleatorio,num_encrip,num_descrip;
    EnteroLargo E=this->rsa->E;
    EnteroLargo D=this->rsa->D;
    EnteroLargo N=this->rsa->N;
    for (int i = 0;i<cant_pruebas;i++){
        
        num_aleatorio = this->rsa->generarAleatorio();
        
        num_encrip = this->rsa->calcularModulo(num_aleatorio,E,N);
        
        num_descrip = this->rsa->calcularModulo(num_encrip,D,N);
        
        if (num_aleatorio != num_descrip){
            error_encontrado = true;
            this->mostrarError(num_aleatorio,num_descrip);
        }
        
    }
    
    
    return !error_encontrado;
    
}

bool TestRSA::TestEncriptacionPorBloque(){
    
    
    this->msjInicioTest("de Encriptacion por Bloque");
    
    bool error_encontrado = false;
    int cant_elem;
    
    this->cargarRSACompleto();
    
    #define cant_pruebas_porBloque 8
    
    string mensaje[cant_pruebas_porBloque];//("ABCDEFG 012345 HIJKLMNOPQRSTUVWXYZ 012");
    cout<<"Cantidad de caracterez por Bloque Entero: "<<this->rsa->cantidadChar<<endl;
    mensaje[0]="HOLA a todos";
    mensaje[1]="Llevo mas de 12 horas programando";
    mensaje[2]="Tengo Suenio";
    mensaje[3]="El vencido no esta del todo vencido hasta que le cierran la boca";
    mensaje[4]="Hace mucho calor";
    mensaje[5]="0123456789 numeros";
    mensaje[6]="Ella tiene que trabajar";
    mensaje[7]="No se que carajo escribir";
    
    EnteroLargo ent_encript,ent_descript,E,D,N;
    
    E=this->rsa->E;
    N=this->rsa->N;
    D=this->rsa->D;

    EnteroLargo *enteros;
    EnteroLargo *desencriptados;
    
    for(int i=0; i< cant_pruebas_porBloque;i++){
        this->rsa->modo_encriptar = true;
        enteros = this->rsa->convertirAEnteroLargo(mensaje[i],cant_elem);

        string msj_resultante;
        
        desencriptados = new EnteroLargo[cant_elem];
        
        
        for ( int j=0;j<cant_elem;j++){
            
            ent_encript=this->rsa->calcularModulo(enteros[j],E,N);
            
            ent_descript=this->rsa->calcularModulo(ent_encript,D,N);
            
            if(enteros[j]>=N){
                error_encontrado= true;
                cout<<"Entero: "<<enteros[j]<<" es mayor/igual que N:"<<N<<endl;
                cout<<"De mensaje: "<<mensaje[i]<<" Parte: "<<j+1<<endl<<endl;
            }
            
            if(ent_encript>=N){
                error_encontrado= true;
                cout<<"Entero encriptado: "<<ent_encript<<" es mayor/igual que N:"<<N<<endl;
            }
            
            if(ent_descript>=N){
                error_encontrado= true;
                cout<<"Entero desencriptado: "<<ent_descript<<" es mayor/igual que N:"<<N<<endl;
            }
            
            if(enteros[j]!=ent_descript){
                error_encontrado = true;
               
                this->msjError(", No coincide Entero Encriptado");
                this->mostrarError(enteros[j],ent_descript);
                cout<<"En mensaje: "<<mensaje[i]<<endl;
                
            }
            
            
            desencriptados[j] = ent_descript;
           
            
        }
        this->rsa->modo_encriptar=false;
        msj_resultante = this->rsa->convertirAString(desencriptados,cant_elem);
        
        //delete[] desencriptados;
        
        if (msj_resultante!=mensaje[i]){
            
            this->msjError(", al desencriptar Bloque");
            this->mostrarError(mensaje[i],msj_resultante);
            
        }
        
        /*
        if(mensaje[i] != msj_resultante){
            this->msjError("Des/Ecriptacion por Bloque Entero");
            this->mostrarError(mensaje[i],msj_resultante);
            error_encontrado=true;

        }*/
    }
    
    
    
    return !error_encontrado;
    
}

bool TestRSA::TestComprobacionConversionCorrecta(){
    
    this->msjInicioTest(" de Corvension Correcta");;
    
    bool error_encontrado = false;
    int cant_elem;
    
    this->cargarRSACompleto();
    
    #define cant_pruebas_porBloque 8
    
    string mensaje[cant_pruebas_porBloque],msj_encript;
    cout<<"Cantidad de caracterez por Bloque Entero: "<<this->rsa->cantidadChar<<endl;
    mensaje[0]="HOLA a todos";
    mensaje[1]="Llevo mas de 12 horas programando";
    mensaje[2]="Tengo Suenio";
    mensaje[3]="El vencido no esta del todo vencido hasta que le cierran la boca";
    mensaje[4]="Hace mucho calor";
    mensaje[5]="0123456789 numeros";
    mensaje[6]="Ella tiene que trabajar";
    mensaje[7]="No se que carajo escribir";
    
    EnteroLargo ent_encript,ent_descript,E,D,N;
    
    E=this->rsa->E;
    N=this->rsa->N;
    D=this->rsa->D;

    EnteroLargo *enteros;
    EnteroLargo *desencriptados,*encriptados,*ent_encrip_verificar;
    
    for(int i=0; i< cant_pruebas_porBloque;i++){
        this->rsa->modo_encriptar=true;
        enteros = this->rsa->convertirAEnteroLargo(mensaje[i],cant_elem);

        string msj_resultante;
        
        desencriptados = new EnteroLargo[cant_elem];
        encriptados = new EnteroLargo[cant_elem];
        
        
        for ( int j=0;j<cant_elem;j++){
            
            ent_encript=this->rsa->calcularModulo(enteros[j],E,N);
            ent_descript=this->rsa->calcularModulo(ent_encript,D,N);
            
            encriptados[j] = ent_encript;
            desencriptados[j] = ent_descript;
           
            
        }
        this->rsa->modo_encriptar=true;
        msj_encript = this->rsa->convertirAString(encriptados,cant_elem);
        
        this->rsa->modo_encriptar=false;
        msj_resultante = this->rsa->convertirAString(desencriptados,cant_elem);
        
        ent_encrip_verificar = this->rsa->convertirAEnteroLargo(msj_encript,cant_elem);
        
        
        for(int j=0;j<cant_elem;j++){
            
            if (ent_encrip_verificar[j]!=encriptados[j]){
                error_encontrado=true;
                this->msjError("por no coincidencia de enteros");
                this->mostrarError(encriptados[j],ent_encrip_verificar[j]);
                cout<<"De Mensaje: "<<mensaje[i]<<" Parte: "<<j+1<<endl;
   
            }
        }
        
        
        delete[] encriptados;
        delete[] desencriptados;
        delete[] ent_encrip_verificar;
        
        if (msj_resultante!=mensaje[i]){
            
            this->msjError(", al descriptar Bloque");
            this->mostrarError(mensaje[i],msj_resultante);
            cout<<"Tamaño"<<endl;
            this->mostrarError(mensaje[i].size(),msj_resultante.size());
        }
    }
    
    
    return !error_encontrado;
    
}

bool TestRSA::TestComprobacionNumeros(){
    
    this->msjInicioTest("Comprobacion de Numeros");
    
    this->cargarRSACompleto();
    
    bool error_encontrado=false;
    
    if(!this->rsa->esPrimo(this->rsa->P)){
        error_encontrado=true;
        this->msjError(", p no es primo");
    }
    cout<<"P: "<<this->rsa->P<<endl;
    
    if(!this->rsa->esPrimo(this->rsa->Q)){
        error_encontrado=true;
        this->msjError(", q no es primo");
        
    }
    cout<<"Q: "<<this->rsa->Q<<endl;
    cout<<"N: "<<this->rsa->N<<endl;
    cout<<"phi(N): "<<this->rsa->phiN<<endl;
    cout<<"D: "<<this->rsa->D<<endl;
    cout<<"E: "<<this->rsa->E<<endl;
    
    return !error_encontrado;
    
    
}


bool TestRSA::TestEncriptacion(){
    
    this->msjInicioTest("Des/Encriptacion");
    this->cargarRSACompleto();
    
#define cant_mensajes 6
    
    Clave clave = this->rsa->getClavePrivadaActual();
    Clave publica = this->rsa->getClavePublicaActual();
    cout<<"Numero N: "<<clave.N()<<endl;
    cout<<"NumeroPhi(N): "<<this->rsa->phiN<<endl;
    cout<<"Numero D: "<<clave.D()<<endl;
    cout<<"Numero E: "<<publica.E()<<endl;
    cout<<"Cantidad de Char por Entero: "<<this->rsa->cantidadChar<<endl;
    
    bool error_encontrado = false;
    
    string mensaje[cant_mensajes],msj_encriptado,msj_desencriptado;
    
    //mensaje = "Hola Mundo";
    
    
    mensaje[0]="HOLA MUNDO!!!";
    mensaje[1]="Esta cayendo el sol ... Oh dios";
    mensaje[2]="Mis zapatillas estan blancas pero tiene algo de tierra";
    mensaje[3]="Estoy podrido de escribir frases boludas";
    mensaje[4]="abcdefghijklmnopqrstuvwxyz 01234567890";
    mensaje[5]="ABCDEFGHIJKLMNOPQRSTUVWXYZ !?¡[]*];:_?¡==)(/&%$#";
         
    
    for (int i=0;i < cant_mensajes ; i++){
    
        msj_encriptado = this->rsa->encriptar(mensaje[i]);

        msj_desencriptado = this->rsa->desencriptar(msj_encriptado);


        if (mensaje[i] != msj_desencriptado){
            error_encontrado =true;
            this->msjError("Des/Encriptacion");
            this->mostrarError(mensaje[i],msj_desencriptado);

        }else{
            
            cout<<"Encriptacion Correcta"<<endl;
            cout<<"Mensaje: "<<mensaje[i]<<endl;
            cout<<"Mensaje Encrip: "<<msj_encriptado<<endl<<endl;
            
        }

    }
    
    return !error_encontrado;
    
}

TestRSA::~TestRSA(){
    
    delete this->rsa;
}

