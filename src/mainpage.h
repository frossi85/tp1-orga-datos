/** @mainpage Voto Electrónico
*
* @authors Grupo Furlong:
* - Facundo Rossi (padrón 86.707 - frossi85@gmail.com)
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
* Si se cambia el identificador (o parte de él) de una instancia particular de cualquier tipo de entidad, antes de eso se deberán actualizar los índices
* que relacionen la clave autonumerica con el identificador de la instancia, modificando este ultimo con el nuevo valor. Lo mismo si se borra una entidad,
* primero se actualizan los índices y luego se elimina.
*
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
* - Candidato (id, ((idLista)ie, (idVotante)ie, (idCargo)ie)i)
* - Cargo (id, (cargo)i, (cargo)*)
* - Administrador (id, (usuario)i, clave)
* - Conteo (((idLista)ie, (idDistrito)ie, (idEleccion)ie)i, cantidad) \n
* (Conteo no necesita id numérico ya que ninguna otra entidad tiene referencias a ella. Relacionamos directamente la clave con el offset en el archivo de conteos)
*
* Estructuras utilizadas:
*
* Estructuras del TP (cuando se usa la palabra id, se refiere a la clave autonumerica):
*
* 1- Hash Votante/id =  clave: DNI (pasar de int a string), dato: id del votante \n
* 2- Hash idVotante/offset =  clave: id_votante, dato: offset del votante en el archivo \n
*
* 3- Hash Distrito/id = clave: nombreDistrito (string), dato: id del distrito\n
* 4- Hash idDistrito/offset =  clave: id_distrito, dato: offset del distrito en el archivo \n
*
* 5- Hash Cargo/id = clave: cargoPrincipal (string), dato: id del cargo\n
* 6- Hash idCargo/offset: clave: id_cargo, dato: offset del cargo en el archivo \n
*
* 7- Arbol Candidato/id = clave: fecha$cargoPpal$nombreLista$DNI(string). dato: id del candidato\n
* 8- Hash Candidato = clave: id_candidato, dato: offset del candidato en el archivo \n
*
* 9- Arbol Lista/id = clave: fecha$cargoPpal$nombreLista. dato: id de la lista. (el $ es el símbolo que usamos para concatenar las cadenas)\n
* 10- Hash idLista/offset = clave: id_lista, dato: offset de la lista en el archivo \n
*
* 11- Arbol Eleccion/id = clave: fecha$cargoPrincipal . dato: id_eleccion.\n
* 12- Hash idEleccion/offset = clave: id_eleccion . dato: offset en el archivo \n
*
* 13- ARBOL REPORTE DISTRITO = clave: nom_distrito$fecha$cargoPrincipal$nom_lista. dato: offset del conteo en el archivo.\n
* 14- ARBOL REPORTE LISTA = clave: fecha$cargoPrincipal$nom_lista$nom_distrito. dato: offset del conteo en el archivo.\n
* 15- ARBOL REPORTE ELECCION = clave: fecha$cargoPrincipal$nom_distrito$nom_lista. dato: offset del conteo en el archivo.\n
*
*
* Todas las entidades se almacenan en archivos de registros de tamaño variable.\n
* En el caso de aquellas que implementan id numérico, se utiliza un hash para relacionar ese id con su correspondiente clave.\n
* Es decir que primero se le pasa su id a dicho hash para obtener la clave, y luego se le pasa esa clave al hash/árbol índice de
* esa entidad, para finalmente obtener el offset del registro en su archivo de registros variables.
* \n\n
*
* Para las entidades que tienen más de un campo como identificador (Elección, Lista y Candidato), se utilizan índices B+, para
* aprovechar la posibilidad de hacer búsquedas aproximadas que brinda esa estructura.
* Distrito, Votante, Cargo y Administrador usan índices de dispersión extensible modular.
*
* En el caso particular de Conteo, tiene tres índices B+, para posibilitar la recuperación de conteos por lista, distrito o
* elección, y usarlos para imprimir el reporte de resultados en base a alguno de esos tres criterios.
*
* <hr>
*
* @section res Resumen:
*
* - Los datos (las entidades propiamente dichas) se guardaran en archivos de registros variables o fijos (según de qué entidad se trate).
* - La búsqueda de estos datos se realizará mediante índices implementados con un hash extensible y un árbol B+, que van a guardar un
*   par (clave, offset en archivo).
* - El flujo del programa tendría esta forma:\n
* 1- el administrador ingresa una clave.\n
* 2- el hash/árbol usado cómo índice recibe ese id, y devuelve un offset.\n
* 3- se accede a ese offset para obtener el registro deseado.\n
* 4- el administrador modifica el registro.\n
* 5 - Se persisten los cambios, y si es necesario, se modifica el offset en el hash/árbol índice.
* \n\n
* (Para altas, bajas y votaciones la estructura es similar).\n
* <hr>
* @section notas Sobre el formato de las claves
*
* Aclaraciones:\n\n
*
* 1 - Cuando se guarda una clave en el hash o arbol, antes se llama a Utilidaes::formatearClave(clave)
* para reemplazar los espacios por '&'.\n
*
* 2 - Para las claves con fechas, tambien antes de guardarlas se le hace a la fecha Utilidades::indexarFecha(fecha)
* para llevarla al formato aaaammdd (la fecha original ingresada por el administrador debe ser del formato ddmmaaaa o dd/mm/aaaa. No es
* valido un formato d/m/aaaa, es decir, debe completarse con ceros si es menor a 10.\n
* 
* 3 - También cuando una clave es compuesta, se concatenan los strings con '$'.\n\n
*
* Ejemplo ilustrativo: el administrador habia insertado una lista con fecha "20/10/2011", cargo "Diputado Cordoba", nombre "UCR".
* El ABMentidades::altaLista inserta la clave en la forma "20111020$Diputado&Cordoba$UCR".\n\n
*
* - Distrito: "nombre_distrito" | Ejemplo: "Lanus"\n
* - Cargo: "nombre_cargo" | Ejemplo: "Intendente&Lanus"\n
* - Eleccion: "fecha$cargo" | Ejemplo: "20111020$Intendente&Lanus"\n
* - Lista: "fecha$cargo$nombreLista" | Ejemplo: "20111020$Intendente&Lanus$UCR"\n
* - Votante: "DNI" | Ejemplo: "34094150"\n
* - Candidato: "fecha$cargo$nombreLista$DNI" | Ejemplo: "20111020$Intendente&Lanus$UCR$34094150"\n
*
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
