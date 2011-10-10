/** @mainpage Voto Electrónico
*
* @authors Grupo Furlong:
* - Facundo Rossi (padrón xx.xxx - frossi85@gmail.com)
* - Leandro Miguenz (padrón 90.649 - leandro.v.059@gmail.com)
* - Martín Lucero (padrón 89.630 - don_pipa182@yahoo.com)
* - Miguel Torres (padrón xx.xxx - mat1204@hotmail.com)
* - Pablo Arlia (padrón xx.xxx - pablo.arlia@gmail.com)\n
* <hr>
*
* @section imple Implementación
*
* Debido a que la problemática que presentan las distintas entidades del dominio son diferentes, se utilizaran distintos tipo de organizaciones
* y estructuras de datos de acuerdo a la entidad.
* \n\n
*
* Aparte del ID de cada entidad, se introducirá uno numérico (entero). De esta manera se lograra una mejor performance en búsquedas, y una implementación
* mas sencilla de los algoritmos de las estructuras de archivos.\n
* Además solucionaría problemas de tamaño de almacenamiento dados por almacenar entidades enteras dentro de otra entidad que las referencia, como es el
* caso de votante que contienen elecciones indefinidas.
* \n\n
*
* Tanto el ID que agregamos nosotros, como el identificador de la clase (x ej en votante el DNI), no podrán tener duplicados. Por eso al realizar cualquier
* alta o modificación, se deberá comprobar que sean únicos.
* \n\n
*
* Las bajas serán físicas y se deberán borrar todas las referencias hacia la instancia que estemos eliminando.\n
* Si se cambia el identificador (o parte de él) de una instancia particular de cualquier tipo de entidad, antes de eso se deberán actualizar los índices
* que relacionen la clave autonumerica con el identificador de la instancia, modificando este ultimo con el nuevo valor. Lo mismo si se borra una entidad,
* primero se actualizan los índices y luego se elimina.
*
* Como claves autonuméricas, usaremos los offsets de cada entidad en su correspondiente archivo.
*
*
* @section orga Organización
*
* Nueva definición de las entidades:\n\n
*
* - Distrito (id, (distrito)i)
* - Votante (id, (DNI)i, NombreyApellido, clave, domicilio, (idDistrito)ie, ((idEleccion)ie)*)
* - Eleccion (id, (fecha, (idCargo)ie)i, ((idDistrito)ie)+)
* - Lista (id, ((idEleccion)ie, nombre)i)
* - Conteo (id, ((idLista)ie, (idDistrito)ie, (idEleccion)ie)i, cantidad)
* - Candidato (id, ((idLista)ie, (idVotante)ie, (idCargo)ie)i)
* - Cargo (id, (cargo)i, (cargo)*)
* - Administrador (id, (usuario)i, clave)
*
*
* Del analisis de las anteriores entidades, llegamos a la conclucion de que existen dos grupos que utilizaran organizaciones de archivo diferentes.
* \n\n
*
* A continuación se enumeran las entidades separadas por grupo, y se caracterizan las organizaciones que usaran cada uno.
* \n\n
*
* Entidades que usaran Archivos con Registros de Tamaño Fijos: Lista,  Distrito, Conteo, Candidato y Administrador
* \n\n
*
* Los registros tendrán tamaño fijo, este tamaño fijo estará dado por la suma del tamaño de los campos fijos mas la de los máximos estipulados para los
* campos variables. Por ende el tamaño de registro será fijo pero dependerá del tipo de entidad.
* \n\n
*
* En este archivo se guardarán las entidades propiamente dichas, mientras que las búsquedas para altas, bajas y modificación estarán organizadas
* mediante un hash extensible como índice, en el que estarán almacenados las claves y los offsets de los registros.
*
* <hr>
*
* Entidades que usaran Archivos con Registros de Tamaño Variable: Cargo
* \n\n
*
* En este archivo se guardarán las entidades propiamente dichas, mientras que las búsquedas para altas, bajas y modificación estarán organizadas
* mediante un árbol B+ como índice, en el que estarán almacenados los offsets de los registros.
*
* <hr>
* Solo queda analizar las entidades Votante y Elección. Para estos se guardará una referencia a una posición dentro de un Archivo de
* VotanteEleccion/EleccionDistrito que tenga registros variables de elecciones/distritos. De esta manera Votante y Eleccion pasarían a ser guardados
* en archivo con registros de tamaño fijo usando Hash Extensible y VotanteEleccion/EleccionDistrito utilizarían Archivo de Registros con tamaño variables,
* usando índices B+.
* \n\n
*
* Votante (id, (DNI)i, NombreyApellido, clave, domicilio, (idDistrito)ie, ((idVotanteEleccion)ie)) \n
* VotanteEleccion (id, ((idEleccion)ie)*)
* \n\n
*
* Eleccion (id, (fecha, (idCargo)ie)i, ((idEleccionDistrito)ie)+) \n
* EleccionDistrito (id, ((idDistrito)ie)+)
* <hr>
*
* @section res Resumen:
*
* - Los datos (las entidades propiamente dichas) se guardaran en archivos de registros variables o fijos (según de qué entidad se trate).
* - La búsqueda de estos datos se realizará mediante índices implementados con un hash extensible y un árbol B+, que van a guardar un
*   par (clave autonumerica, offset en archivo).
* - El flujo del programa tendría esta forma:\n
* 1- el administrador ingresa un id.\n
* 2- el hash/árbol usado cómo índice recibe ese id, y devuelve un offset.\n
* 3- se accede a ese offset para obtener el registro deseado.\n
* 4- el administrador modifica el registro.\n
* 5 - Se persisten los cambios, y si es necesario, se modifica el offset en el hash/árbol índice.
* \n\n
* (Para altas, bajas y votaciones la estructura es similar).\n
* <hr>
* @section ind Índices
*
* @section hash Hash:
*
* - Función de hashing utilizada:\n\n
*
*@code unsigned int hash_extensible::funcion_hashing(RegistroIndice *registro){
*
*	string clave = registro->getClave();
*	unsigned int tam_tabla = obtener_tamanio_tabla();
*
*	int valor = 0;
*
*   for( int i = 0; i < clave.length() ; i++ )
*        valor = 37 * valor + clave.at( i );
*
*    valor %= tam_tabla;
*    if( valor < 0 )
*        valor += tam_tabla;
*
*    return valor + 1;
} @endcode
*
* En un principio usamos una función mucho más simple, que obtenía el valor ASCII de los caracteres de la clave, los sumaba, y luego calculaba
* el módulo de ese valor con el tamaño de la tabla de dispersión. Esa función dio malos resultados al intentar guardar grandes cantidades de registros
* en el hash, volviendo demasiado lenta y casi imposible la inserción de más de 500 registros, aproximadamente, debido a la cantidad de colisiones que se
* producían.
* \n\n
*
* Con la actual función de hashing los resultados fueron mucho mejores, y pudimos insertar hasta 1 millón de registros en un tiempo de ejecución razonable.
*
* - Tamaño de bloques:\n\n
*
* Para los bloques del hash elegimos un tamaño de 512 bytes, porque es un múltiplo de 512*2^n, al igual que los bloques en que está organizaod el disco,
* lo que permite aprovechar mejor el buffering del sistema.\n
* Además consideramos que es un tamaño adecuado a nuestras necesidades, ya que los bloques del hash almacenan objetos de la clase RegistroIndice,
* que una vez persistidos con sus metadatos, ocupan un estimado de entre 13 y 18 bytes cada uno, y por lo tanto en cada bloque caben más de 30 registros.
*
* @section arbol Árbol B+:
*
* <hr>
* @section bugs Bugs conocidos
*
* Hash: \n\n
*
* - Quedan algunas pérdidas de memoria sin resolver. Según las pruebas hechas, insertar 1 millón de registros de una vez consume 3 Gb de RAM.
* Sin embargo, para inserciones de menos de 300.000 elementos, la pérdida de memoria es mucho menor, y se pueden realizar sin problemas en una
* computadora con 2 o más Gb de RAM. Independientemente de la memoria del sistema, se puede guardar cualquier cantidad de registros, siempre
* y cuando no se los guarde a todos en una sola corrida (es decir, guardando algunos, cerrando el programa y guardando los que faltan).
* - Sí la cantidad de registros en el hash es demasiado alta (alrededor de 1 millón), el método imprimir no muestra correctamente la tabla de
* dispersión (se ve sólo una parte). Sin embargo la tabla en sí no tiene ninguna falla, por lo que el problema podría deberse a una limitación
* del editore de texto para escribir líneas demasiado largas.
*/
