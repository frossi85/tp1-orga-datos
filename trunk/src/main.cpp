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


        Menu *menu = Menu::getMenu();
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

        return 0;
}

void ejecutar_test(){
        ///CODIGO DE PRUEBA FACUNDO
        DataAccess dataAccess;

        Distrito distrito("Lanus");
        distrito.setId(45);

        dataAccess.Guardar(distrito);

        Distrito distrito2;

        dataAccess.getPorId(0, distrito2);

        dataAccess.Eliminar(distrito2);

        Cargo cargo("Presidente");
        cargo.setId(20);
        cargo.agregarCargoSecundario("Vice Presidente");
        cargo.agregarCargoSecundario("Gobernador");
        cargo.agregarCargoSecundario("Intendente");
        cargo.agregarCargoSecundario("Consejal");

        dataAccess.Guardar(cargo);

        Cargo cargo2;
        dataAccess.getPorId(0, cargo2);
}

/* Ejemplo de uso del hash
 *
 *
 * Crear hash:
 *
 * //recibe como parámetros las rutas del arcivo de bloques, el archivo de bloques libres y el archivo con la tabla de dispersion
 * hash_extensible *hash = new hash_extensible("archBloques", "archBloqLibres", "tablaDispersion");
 *
 * Obtener distrito:
 *
 * //crear un registro con la clave del distrito que se quiere obtener (el offset no importa asi que lo pongo en 0)
 * RegistroIndice registro("Avellaneda", 0);
 *
 * //pasar el registro al hash
 * hash_extensible->buscar(&registro);
 *
 * //Ahora haciendo registro.getOffset() se puede obtener el offset de ese distrito para buscarlo
 * //en su archivo. Si no estaba en el hash, buscar devuelve false
 *
 * //Los métodos guardar y borrar se usan de la misma forma
 */
