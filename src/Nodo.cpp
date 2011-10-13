/*
 * Nodo.cpp
 *
 *  Created on: 02/10/2011
 *      Author: martin
 */

#include "Nodo.h"

Nodo::Nodo()
{
	this->addr_ = 0;
	less_ = 0 ;
	size_ = 0;
	padre_ = 0;
	flags_ = 0;
}

Nodo::~Nodo() {
	// TODO Auto-generated destructor stub
}

int Nodo::agregarRegistro( const string &key, const long &data )
{
	bool fueAgregado = false;
	RegistroArbol * registro = new RegistroArbol(key, data);
	
	//TODO: Buscar en los archios originales para q es less_ y usarlo en
	//esta clase, creo q son los hijos

	int i = 0;
	for ( i = 0; i < size_; i++ )
	{
		if ( elems_[ i ]->getClave() > key )
		{
			// Inserto en entre medio de uno menor y uno mayor q la clave
			//pasaron como parametro
			//Ver si aca tengo q corroborar q no sea duplicado
			elems_.insert( elems_.begin( ) + i, registro);		
			elems_[ i ]->link_ = 0;
			fueAgregado = true;
			break;
		}
	}

	if ( !fueAgregado )
	{
		//Si no fue insertado entre medio lo meto al final
		elems_.push_back(registro);
		i = size_;
	}

	size_++;
	flags_ = Nodo::NodoCambiado;
	return i;
}

int Nodo::agregarRegistro( RegistroArbol & elem )
{
	int posicion = agregarRegistro( elem.getClave(), elem.getOffset() );
	elems_[ posicion ]->link_ = elem.link_;
	return posicion;
}

int Nodo::agregarRegistroAlFinal( RegistroArbol & elem )
{
	//RegistroArbol * registro = new RegistroArbol(elem.getClave(), elem.getOffset());
	//Ver si aca tengo q corroborar q no sea duplicado

	elems_.push_back(&elem);

	size_++;
	flags_ = Nodo::NodoCambiado;
	return (size_ - 1);
}

////	===================================================================
void Nodo::Guardar(fstream &ofs)
{
	//Situar el stream en la posicion absoluta addr_
	ofs.seekp(addr_);
	unsigned int capacidadEnBytesAux = capacidadEnBytes;
	
	//ofs.write(reinterpret_cast<char *>(&capacidadEnBytesAux), sizeof(capacidadEnBytesAux));
	//ofs.write(reinterpret_cast<char *>(&tamanioEnBytesOcupados), sizeof(tamanioEnBytesOcupados));
	//ofs.write(reinterpret_cast<char *>(&addr_), sizeof(addr_));
	//ofs.write(reinterpret_cast<char *>(&less_), sizeof(less_));
	//ofs.write(reinterpret_cast<char *>(&size_), sizeof(size_));
	//ofs.write(reinterpret_cast<char *>(&padre_), sizeof(padre_));
	
	
	ofs<<capacidadEnBytesAux<<"|";
	ofs<<size_<<"|";
	ofs<<addr_<<"|";
	ofs<<less_<<"|";
	ofs<<padre_<<"|";

	for(unsigned int i = 0; i < elems_.size(); i++)
	{
		elems_[i]->Guardar(ofs);
	}
	//Hago un seek para dejarlo en los proximos 512bytes??
	ofs<<"||";
	long posicionStream = ofs.tellp();
	long cantidadALimpiar = capacidadEnBytes - (posicionStream - addr_);
	
	for(long i = 0; i<cantidadALimpiar; i++)
	{
		ofs<<" ";
	}
}

//El arbol ya deja situado al fstream en la posicion correcta para
//leer el nodo
Nodo * Nodo::Leer(fstream &ifs)
{
	unsigned int capacidadEnBytesAux = 0;
	Nodo * nodo = new Nodo();
	
	//ifs.read(reinterpret_cast<char *>(&(capacidadEnBytesAux)), sizeof((capacidadEnBytesAux)));
	//ifs.read(reinterpret_cast<char *>(&(nodo->tamanioEnBytesOcupados)), sizeof((nodo->tamanioEnBytesOcupados)));
	//ifs.read(reinterpret_cast<char *>(&(nodo->addr_)), sizeof((nodo->addr_)));
	//ifs.read(reinterpret_cast<char *>(&(nodo->less_)), sizeof((nodo->less_)));
	//ifs.read(reinterpret_cast<char *>(&(nodo->size_)), sizeof((nodo->size_)));
	//ifs.read(reinterpret_cast<char *>(&(nodo->padre_)), sizeof((nodo->padre_)));

	char delimitador;
	
	ifs>>(capacidadEnBytesAux)>>delimitador;
	ifs>>(nodo->size_)>>delimitador;
	ifs>>(nodo->addr_)>>delimitador;
	ifs>>(nodo->less_)>>delimitador;
	ifs>>(nodo->padre_)>>delimitador;
	
	//TODO: cuando capacidadEnBytesAux deje de ser constante tendria q 
	//settearlo aca o en el ifs.read()

	for(int i = 0; i < nodo->size_; i++)
	{
		
		nodo->elems_.push_back(RegistroArbol::Leer(ifs));
	}
	
	ifs>>delimitador>>delimitador;
	
	return nodo;
}

//Agregados Facundo
////void removeAt( int index )
void Nodo::removerEnPosicion(int indice){
	elems_.erase(elems_.begin() + indice);
	size_--;
	flags_ = NodoCambiado;
}
//void  removeAt( int index, ElemType &removed )
void Nodo::removerEnPosicion(int indice, RegistroArbol & removido ){
	//Antes de remover dvuelve por parametro una referencia al elemento 
	//q quiero borrar en esa posicion
	removido = 	*elems_[indice];
	removerEnPosicion(indice);
}

void Nodo::clear()
{
	size_ = 0;
	flags_ = 0;

	RegistroArbol * registro;
	
	while(!elems_.empty())
	{
		registro = elems_.back();
		elems_.pop_back();
		delete registro;
	}
}

//////	===============================================================
////bool find( const string & key, int &index ) const
//Busqueda binaria por clave en un vector, devuelve true si lo encontro
//Por ahiora lo hago secuencial despues veo de implementarlo c binaria
bool Nodo::find( const string &clave, int &index ) const
{
	int lb = 0, ub = size_ - 1;

	while( lb <= ub )
	{
		index = ( lb + ub ) >> 1;

		if( clave < elems_[ index ]->getClave() )
		{
			ub = index - 1;
		}
		else
		{
			if( clave > elems_[ index ]->getClave() )
			{
				lb = index + 1;
			}
			else
			{
				return true;
			}
		}
	}

	index = lb;
	return false;
}

bool Nodo::tieneHijos() const
{
	return less_ != 0;
}

bool Nodo::estaVacio() const
{
	return size_ == 0;
}

bool Nodo::estaLleno() const
{
	return size_ == maxKeys;
}

int Nodo::count() const
{
	return size_;
}

void Nodo::Imprimir()
{
	cout << "Capacidad en bytes: " << capacidadEnBytes << endl;
	cout << "Cantidad de Registros: " << size_ << endl;
	cout << "Address: " << addr_ << endl;

	cout << "Registros del Nodo: " << endl;
	for(unsigned int i = 0; i < elems_.size(); i++)
	{
		cout << "Registro Nro" << i+1 << endl;
		elems_[i]->Imprimir();
		cout<< endl;
	}
	
	//addr_;
	//less_;
	//size_;
	//padre_;
	//flags_;
}
