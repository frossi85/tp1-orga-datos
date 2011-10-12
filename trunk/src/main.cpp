#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstdlib>

#include "menu.h"
#include "Distrito.h"
#include "Cargo.h"
#include "DataAccess.h"

using namespace std;

void ejecutar_test();

int main(int argc, char *argv[]){

        ejecutar_test(); //Adentro de esta funcion hay prueba de los metodos para crear los archivos
        //con cada entidad y sirve de ejemplo de como hay q usarlo


 /*       Menu *menu = Menu::getMenu();
        if (argc != 2){
                // Numero incorrecto de parametros
                cout << "Uso: voto_electronico -h\n";
                return 0;
        }

        if ( !(strcmp(argv[1],"-h")) || !(strcmp(argv[1],"--help")) ) {
                // La funcionalidad deseada es acceder a la ayuda del programa.
                menu->mostrar_ayuda();
                return 0;
        }

        if ( !(strcmp(argv[1],"-a")) || !(strcmp(argv[1],"--admin")) ) {

                cout << "Ingreso como administrador. \n(para salir ingrese \"salir\" en alguno de los campos) \n";
                // La funcionalidad deseada es acceder como administrador
                // Se pide y verifica usuario y contraseña
                do {
                        menu->pedir_usuario();
                        menu->pedir_contrasena();
                } while (!menu->acceder_admin());

                return 0;
        }
        if ( !(strcmp(argv[1],"-u")) || !(strcmp(argv[1],"--user")) ) {

                cout << "Ingreso como usuario. \n(para salir ingrese \"salir\" en alguno de los campos) \n";
                // La funcionalidad deseada es acceder como usuario
                // Se pide y verifica usuario y contraseña
                do {
                        menu->pedir_usuario();
                        menu->pedir_contrasena();
                } while (!menu->acceder_usuario());

                return 0;
        }

        cout << "Uso: voto_electronico -h\n";   // Mal uso de las opciones

        return 0;*/
}

void ejecutar_test(){
        ///CODIGO DE PRUEBA MARTIN
        DataAccess dataAccess;

        Distrito distrito1("Lanus");
        distrito1.setId(45);

        Distrito distrito2("Cordoba");
        distrito2.setId(50);

        Distrito distrito3("Santa Fe");
        distrito3.setId(55);

        Distrito distrito4("Pehuajo");
        distrito4.setId(60);

        Distrito distrito5("Olivos");
        distrito5.setId(65);

        Distrito distrito6("Springfield");
        distrito6.setId(70);

        distrito1.Imprimir();
        distrito2.Imprimir();
        distrito3.Imprimir();
        distrito4.Imprimir();
        distrito5.Imprimir();
        distrito6.Imprimir();

        unsigned long int offset1, offset2, offset3, offset4, offset5, offset6;

        offset1 = dataAccess.Guardar(distrito1);
        cout << "Offset de Lanus: " << offset1 << endl;
        offset2 = dataAccess.Guardar(distrito2);
        cout << "Offset de Cordoba: " << offset2 << endl;
        offset3 = dataAccess.Guardar(distrito3);
        cout << "Offset de Santa Fe: " << offset3 << endl;
        offset4 = dataAccess.Guardar(distrito4);
        cout << "Offset de Pehuajo: " << offset4 << endl;
        offset5 = dataAccess.Guardar(distrito5);
        cout << "Offset de Olivos: " << offset5 << endl;
        offset6 = dataAccess.Guardar(distrito6);
        cout << "Offset de Springfield: " << offset6 << endl;

        dataAccess.Leer(distrito1,93);
        dataAccess.Leer(distrito2,75);
        dataAccess.Leer(distrito3,56);
        dataAccess.Leer(distrito4,36);
        dataAccess.Leer(distrito5,17);
        dataAccess.Leer(distrito6,0);

        distrito1.Imprimir();
        distrito2.Imprimir();
        distrito3.Imprimir();
        distrito4.Imprimir();
        distrito5.Imprimir();
        distrito6.Imprimir();
}

/* Ejemplo de uso del hash
 *
 *
 * Crear hash:
 *
 * //recibe como parámetros las rutas del archivo de bloques, el archivo de bloques libres y el archivo con la tabla de dispersion
 * hash_extensible *hash = new hash_extensible("archBloques", "archBloqLibres", "tablaDispersion");
 *
 * Obtener distrito:
 *
 * //crear un registro con la clave del distrito que se quiere obtener (el offset no importa asi que lo pongo en 0)
 * RegistroIndice registro("Avellaneda", 0);
 *
 * //pasar el registro al hash y crear otro registro para que tome el valor de retorno
 * RegistroIndice *otroRegistro = NULL;
 * otroRegistro = hash_extensible->buscar(&registro);
 *
 * //OJO: después de hacer eso no hagan "delete otroRegistro" porque se pudre todo, y tira segmentation fault.
 * //No se por qué pasa, si lo puedo arreglar aviso, igual no jode mucho.
 *
 * //Ahora haciendo otroRegistro->getOffset() se puede obtener el offset de ese distrito para buscarlo
 * //en su archivo. Si no estaba en el hash, buscar devuelve NULL.
 *
 * //Los métodos guardar y borrar se usan de la misma forma
 */
