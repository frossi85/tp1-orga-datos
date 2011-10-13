/*
 * ArbolBMas.cpp
 *
 *  Created on: 08/10/2011
 *      Author: facundo
 */

#include "ArbolBMas.h"

ArbolBMas::ArbolBMas() {
	// TODO Auto-generated constructor stub
	//Creo q habria q hacer lo del StreamControler
	root_ = 0;
	//maxCacheSize_ = 0;
	
	maxCacheSize_ = 512; //deberia settearlo con un setter probar como funciona con 0 tambien
	rootAddr_ = 0;

}

ArbolBMas::~ArbolBMas() {
	close();
}

//	===================================================================
bool ArbolBMas::agregar( const string &key, const long &offset )
{
	if ( !isOpen() ) return false;
	
	if ( !root_ )
	{
		int addr = rootAddr();
		if ( !addr )
		{
			root_ = newnodo();
			root_->flags_ = Nodo::NodoCambiado;
			rootAddr( root_->addr_ );
		}
		else
		{
			if ( !loadnodo( &root_, addr ) )
			{
				cout<<"ERROR: No estaba cargada ni se pudo cargar la raiz al insertar"<<endl;
				return false;
			}
		}
	}

	if ( !root_ ) return false;

	// Busco el nodo destino
	bool econtrado = false;
	string copyKey(key);
	long copyData(offset);
	int retIndex = -1, padreIndex = 0;

	Nodo *nodo = findnodo( root_, copyKey, retIndex, padreIndex, econtrado );

	if ( econtrado || !nodo )
	{
		//cout<<"clave duplicada"<<endl;
		
		// No se permiten claves duplicadas
		releaseCache();
		return false;
	}

	if ( !nodo->estaLleno() )
	{
		// Lo agrego al nodo, ya q no esta lleno	
		nodo->agregarRegistro( copyKey, copyData );	
		//ImprimirCache();
		releaseCache();
		return true;
	}
	else
	{		
		//Si el nodo esta lleno tengo q partirlo en dos, mitades
		//Tener contador de cantidad de registros en el nodo
		RegistroArbol median(key,offset);
		Nodo *nodoDerecho = 0;
		Nodo *padre = 0;
		if ( !loadnodo( &padre, nodo->padre_ ) )
		{
			releaseCache();
			return false;
		}

		// Parto el nodo y obtengo el intermedio (median)
		if ( !splitnodo( nodo, median, &nodoDerecho ) )
		{
			releaseCache();
			return false;
		}

		while ( 0 != padre )
		{
			// Agrego el intermedio al padre
			//Lo repito hasta que el padre no necesite ser particionado
			if ( padre->estaLleno() )
			{
				if ( !splitnodo( padre, median, &nodoDerecho ) )
				{
					releaseCache();
					return false;
				}

				nodo = padre;

				// Move Up
				if ( !loadnodo( &padre, padre->padre_ ) )
				{
					releaseCache();
					return false;
				}
			}
			else
			{
				padre->agregarRegistro( median );
				padre->flags_ = Nodo::NodoCambiado;
				nodoDerecho->padre_ = padre->addr_;
				nodoDerecho->flags_ = Nodo::NodoCambiado;
				break;
			}
		}

		//Si la raiz se partio, entonces creo una nueva raiz q tenga un elemento y dos punteros
		if ( !padre )
		{
			// El nodo raiz!
			root_ = newnodo();
			rootAddr( root_->addr_ );
			nodo->padre_ = root_->addr_;
			nodo->flags_ = Nodo::NodoCambiado;
			nodoDerecho->padre_ = root_->addr_;
			nodoDerecho->flags_ = Nodo::NodoCambiado;

			root_->agregarRegistro( median.clave, median.offset );
			root_->elems_[ 0 ]->link_ = nodoDerecho->addr_;
			root_->less_ = nodo->addr_;
		}
	}

	releaseCache();
	return true;
}

void ArbolBMas::ImprimirCache()
{
	cout<<"/////////////Comienza imprecion de cache//////////////"<<endl;
	
	for(int i=0; i<cache_.size(); i++)
	{
		cache_[i]->Imprimir();
		cout<<endl;
	}
		
	cout<<"/////////////Fin imprecion de cache//////////////"<<endl;
		
	getchar();
}

//	===================================================================
bool ArbolBMas::remove( const string &key )
{
//	if ( !root_ )
//	{
//		return false;
//	}
//
//	// Find targeted nodo
//	bool econtrado = false;
//	int retIndex = -1, padreIndex = 0;
//
//	Nodo *nodo = findnodo( root_, key, retIndex, padreIndex, econtrado );
//
//	if ( !econtrado || !nodo )
//	{
//		// Key not econtrado
//		releaseCache();
//		return false;
//	}
//
//	if ( !nodo->hasChilds() )
//	{
//		nodo->removeAt( retIndex );
//		if ( !rebalance( nodo, padreIndex ) )
//		{
//			releaseCache();
//			return false;
//		}
//	}
//	else
//	{
//		if ( !pullOut( nodo, retIndex ) )
//		{
//			releaseCache();
//			return false;
//		}
//	}
//
//	releaseCache();
	return true;
}

//	===================================================================
bool ArbolBMas::remove( const string &key, long &data )
{
//	if ( !root_ )
//	{
//		return false;
//	}
//
//	// Find targeted nodo
//	bool econtrado = false;
//	int retIndex = -1, padreIndex = 0;
//
//	Nodo *nodo = findnodo( root_, key, retIndex, padreIndex, econtrado );
//
//	if ( !econtrado || !nodo )
//	{
//		// Key not econtrado
//		releaseCache();
//		return false;
//	}
//	else
//	{
//		data = nodo->elems_[ retIndex ].data_;
//	}
//
//	if ( !nodo->hasChilds() )
//	{
//		nodo->removeAt( retIndex );
//		if ( !rebalance( nodo, padreIndex ) )
//		{
//			releaseCache();
//			return false;
//		}
//	}
//	else
//	{
//		if ( !pullOut( nodo, retIndex ) )
//		{
//			releaseCache();
//			return false;
//		}
//	}
//
//	releaseCache();
	return true;
}

//	===================================================================
//Creo q busca si esta y nada mas
bool ArbolBMas::buscar( const string &key, long &data )
{
	if ( !root_ )
	{
		return false;
	}

	int index = 0, padreIndex = 0;
	bool econtrado = false;
	Nodo *nodo = findnodo( root_, key, index, padreIndex, econtrado );

	if ( !nodo || index < 0 )
	{
		releaseCache();
		return false;
	}

	if ( econtrado )
	{
		// Clave econtrada
		data = nodo->elems_[ index ]->getOffset();
		releaseCache();
		return true;
	}

	releaseCache();

	// Key not econtrado
	return false;
}

//	===================================================================
//bool ArbolBMas::search(TContainer &retList, const string &startKey, bool preciseSearch, TChecker &condition )
//{
//	retList.clear();
//
//	// Find targeted nodo
//	bool econtrado = false;
//	int retIndex = -1, padreIndex = 0;
//	Nodo *nodo = findnodo( root_, startKey, retIndex, padreIndex, econtrado );
//
//	if ( ( preciseSearch && !econtrado ) || !nodo )
//	{
//		releaseCache();
//		return false;
//	}
//
//	if ( !allKeys( nodo, retList, retIndex, startKey, condition ) )
//	{
//		releaseCache();
//		return false;
//	}
//
//	releaseCache();
//	return true;
//}

//	===================================================================
//TODO: Creo q TConteiner es una especie de Lista
//bool ArbolBMas::getAll( TContainer &retList )
//{
//	if ( !allKeys( root_, retList ) )
//	{
//		releaseCache();
//		return false;
//	}
//
//	releaseCache();
//	return true;
//}

//	===================================================================
//	BTreeAlgorithms< nodoSize, string, long, TController >::changeData

//void ArbolBMas::changeData( const string &key, const long &newData )
//{
//	if ( !root_ )
//	{
//		return;
//	}
//
//	int index = 0, padreIndex = 0;
//	bool econtrado = false;
//	Nodo *nodo = findnodo( root_, key, index, padreIndex, econtrado );
//
//	if ( !nodo || index < 0 )
//	{
//		releaseCache();
//		return;
//	}
//
//	if ( econtrado )
//	{
//		// Key econtrado
//		nodo->elems_[ index ].data_ = newData;
//		nodo->flags_ = Nodo::NodoCambiado;
//		releaseCache();
//		return;
//	}
//
//	releaseCache();
//}

//	===================================================================
//bool ArbolBMas::allKeys(Nodo *nodo, TContainer &retList, int elemIndex, const string &startKey, TChecker &condition )
//{
//	if ( !nodo ) return true;
//
//	if ( -1 == elemIndex )
//	{
//		nodo->find( startKey, elemIndex );
//		if ( -1 == elemIndex )
//		{
//			return false;
//		}
//	}
//
//	int i = elemIndex;
//	//if ( i > 0 ) i--;
//
//	while ( i < nodo->size_ )
//	{
//		if ( condition.satisfy( nodo->elems_[ i ].key_ ) )
//		{
//			retList.push_back( TContainer::ElemType( nodo->elems_[ i ] ) );
//
//			if ( nodo->elems_[ i ].link_ )
//			{
//				// Examine each child item
//				Nodo *child = 0;
//				bool wasInCache = nodoInCache( nodo->elems_[ i ].link_ );
//				if ( !loadnodo( &child, nodo->elems_[ i ].link_ ) ) return false;
//				allKeys( child, retList, condition );
//				if ( child && !wasInCache ) releasenodo( child->addr_ );
//			}
//		}
//		else
//		{
//			break;
//		}
//
//		// Move to nodo end
//		i++;
//	}
//
//	if ( !nodo->padre_ )
//	{
//		// End of search has reached
//		return true;
//	}
//
//	// Move to up
//	Nodo *padre = 0;
//	bool wasInCache = nodoInCache( nodo->padre_ );
//	if ( !loadnodo( &padre, nodo->padre_ ) )
//	{
//		return false;
//	}
//
//	bool ret = allKeys( padre, retList, -1, startKey, condition );
//	if ( padre && !wasInCache ) releasenodo( padre->addr_ );
//	return ret;
//}

//	===================================================================
//bool ArbolBMas::allKeys(Nodo *nodo, TContainer &retList, TChecker &condition )
//{
//	if ( !nodo ) return true;
//
//	if ( nodo->less_ )
//	{
//		Nodo *less = 0;
//
//		bool wasInCache = nodoInCache( nodo->less_ );
//		if ( !loadnodo( &less, nodo->less_ ) ) return false;
//		if ( !allKeys( less, retList ) )
//		{
//			// End of the condition had reached
//			return false;
//		}
//
//		if ( less && !wasInCache ) releasenodo( less->addr_ );
//	}
//
//	for ( int i = 0; i < nodo->size_; i++ )
//	{
//		// Apply condition
//		if ( !condition.satisfy( nodo->elems_[ i ].key_ ) )
//		{
//			// Stop key reached
//			return false;
//		}
//
//		retList.push_back( TContainer::ElemType( nodo->elems_[ i ] ) );
//
//		if ( nodo->elems_[ i ].link_ )
//		{
//			Nodo *kid = 0;
//			bool wasInCache = nodoInCache( nodo->elems_[ i ].link_ );
//			if ( !loadnodo( &kid, nodo->elems_[ i ].link_ ) ) return false;
//			if ( !allKeys( kid, retList ) )
//			{
//				// End of tree or condition had reached
//				return false;
//			}
//			if ( kid && !wasInCache ) releasenodo( kid->addr_ );
//		}
//	}
//
//	return true;
//}

//	===================================================================
//bool ArbolBMas::allKeys(Nodo *nodo, TContainer &retList )
//{
//	if ( !nodo ) return true;
//
//	if ( nodo->less_ )
//	{
//		Nodo *less = 0;
//
//		bool wasInCache = nodoInCache( nodo->less_ );
//		if ( !loadnodo( &less, nodo->less_ ) ) return false;
//		if ( !allKeys( less, retList ) ) return false;
//		if ( less && !wasInCache ) releasenodo( less->addr_ );
//	}
//
//	for ( int i = 0; i < nodo->count(); i++ )
//	{
//		retList.push_back( TContainer::ElemType( nodo->elems_[ i ] ) );
//
//		if ( nodo->elems_[ i ].link_ )
//		{
//			Nodo *kid = 0;
//
//			bool wasInCache = nodoInCache( nodo->elems_[ i ].link_ );
//			if ( !loadnodo( &kid, nodo->elems_[ i ].link_ ) ) return false;
//			if ( !allKeys( kid, retList ) ) return false;
//			if ( kid && !wasInCache ) releasenodo( kid->addr_ );
//		}
//	}
//
//	return true;
//}

//	===================================================================
void ArbolBMas::close()
{
	delete root_;
	root_ = 0;

	storage.close();
	closeController();
}

//	===================================================================
//bool ArbolBMas::rebalance( Nodo *nodo, int padreIndex )
//{
//	int minimal = nodo->maxKeys >> 1;
//
//	if ( nodo->count() >= minimal )
//	{
//		// nodo is balanced
//		return true;
//	}
//
//	Nodo *padre = 0;
//	if ( !loadnodo( &padre, nodo->padre_ ) )
//	{
//		return false;
//	}
//
//	Nodo *leftnodo = 0, *Derechonodo = 0;
//	Nodo *combinednodo = 0;
//
//	if ( 0 == padreIndex - 1 )
//	{
//		if ( !loadnodo( &leftnodo, padre->less_ ) ) return false;
//	}
//	else if ( padreIndex >= 2 )
//	{
//		if ( !loadnodo( &leftnodo, padre->elems_[ padreIndex - 2 ].link_ ) ) return false;
//	}
//
//	if ( padre && padreIndex < padre->count() )
//	{
//		if ( !loadnodo( &Derechonodo, padre->elems_[ padreIndex ].link_ ) ) return false;
//	}
//
//	if ( leftnodo && leftnodo->count() > minimal )
//	{
//		// Check left
//		RegistroArbol< string, long > padreElem = padre->elems_[ padreIndex - 1 ];
//		padreElem.link_ = nodo->less_;
//		nodo->less_ = leftnodo->elems_[ leftnodo->count() - 1 ].link_;
//		nodo->add( padreElem );
//		nodo->flags_ = Nodo::nodoChanged;
//
//		if ( nodo->less_ )
//		{
//			Nodo *less = 0;
//			if ( !loadnodo( &less, nodo->less_ ) ) return false;
//			less->padre_ = nodo->addr_;
//			less->flags_ = Nodo::nodoChanged;
//		}
//
//		RegistroArbol< string, long > largest;
//		leftnodo->removeAt( leftnodo->count() - 1, largest );
//		padre->elems_[ padreIndex - 1 ].key_ = largest.key_;
//		padre->elems_[ padreIndex - 1 ].data_ = largest.data_;
//		padre->flags_ = Nodo::nodoChanged;
//	}
//	else if ( Derechonodo && Derechonodo->count() > minimal )
//	{
//		// Check Derecho
//		RegistroArbol< string, long > padreElem = padre->elems_[ padreIndex ];
//		padreElem.link_ = Derechonodo->less_;
//		nodo->add( padreElem );
//
//		if ( Derechonodo->less_ )
//		{
//			Nodo *less = 0;
//			if ( !loadnodo( &less, Derechonodo->less_ ) ) return false;
//			less->padre_ = nodo->addr_;
//			less->flags_ = Nodo::nodoChanged;
//		}
//
//		RegistroArbol< string, long > smallest;
//		Derechonodo->removeAt( 0, smallest );
//		Derechonodo->less_ = smallest.link_;
//		padre->elems_[ padreIndex ].key_ = smallest.key_;
//		padre->elems_[ padreIndex ].data_ = smallest.data_;
//		padre->flags_ = Nodo::nodoChanged;
//	}
//	else
//	{
//		// Combine nodos
//		if ( leftnodo )
//		{
//			int index = leftnodo->add( padre->elems_[ padreIndex - 1 ].key_,
//				padre->elems_[ padreIndex - 1 ].data_ );
//			leftnodo->elems_[ index ].link_ = nodo->less_;
//			if ( nodo->less_ )
//			{
//				Nodo *less = 0;
//				if ( !loadnodo( &less, nodo->less_ ) ) return false;
//				less->padre_ = leftnodo->addr_;
//				less->flags_ = Nodo::nodoChanged;
//			}
//
//			if ( !combine( leftnodo, nodo ) ) return false;
//			combinednodo = leftnodo;
//			padre->removeAt( padreIndex - 1 );
//		}
//		else if ( Derechonodo )
//		{
//			int index = nodo->add( padre->elems_[ padreIndex ].key_,
//				padre->elems_[ padreIndex ].data_ );
//			nodo->elems_[ index ].link_ = Derechonodo->less_;
//
//			if ( Derechonodo->less_ )
//			{
//				Nodo *less = 0;
//				if ( !loadnodo( &less, Derechonodo->less_ ) ) return false;
//				less->padre_ = nodo->addr_;
//				less->flags_ = Nodo::nodoChanged;
//			}
//
//			if ( !combine( nodo, Derechonodo ) ) return false;
//			combinednodo = nodo;
//			padre->removeAt( padreIndex );
//		}
//
//		padreIndex = -1;
//
//		if ( padre && padre->padre_ )
//		{
//			// Find padre index
//			Nodo *pp = 0;
//			if ( !loadnodo( &pp, padre->padre_ ) ) return false;
//
//			if ( pp->less_ == padre->addr_ )
//			{
//				padreIndex = 0;
//			}
//			else
//			{
//				// Check padres padre
//				for ( int i = 0; i < pp->count(); i++ )
//				{
//					if ( pp->elems_[ i ].link_ == padre->addr_ )
//					{
//						padreIndex = i + 1;
//						break;
//					}
//				}
//			}
//
//			if ( padreIndex >= 0 )
//			{
//				if ( !rebalance( padre, padreIndex ) ) return false;
//			}
//		}
//		else
//		{
//			// It is root
//			if ( padre && padre->isEmpty() )
//			{
//				deletenodo( root_ );
//				root_ = combinednodo;
//				rootAddr( root_->addr_ );
//				combinednodo->padre_ = 0;
//				combinednodo->flags_ = Nodo::nodoChanged;
//			}
//		}
//	}
//
//	return true;
//}

//	===================================================================
//bool ArbolBMas::combine( Nodo *leftnodo, Nodo *Derechonodo )
//{
//	if ( leftnodo->count() + Derechonodo->count() > leftnodo->maxKeys )
//	{
//		// No space for combining
//		return true;
//	}
//
//	for ( int i = 0; i < Derechonodo->count(); i++ )
//	{
//		leftnodo->elems_[ leftnodo->count() ] = Derechonodo->elems_[ i ];
//
//		if ( Derechonodo->elems_[ i ].link_ )
//		{
//			Nodo *link = 0;
//			if ( !loadnodo( &link, Derechonodo->elems_[ i ].link_ ) ) return false;
//			link->padre_ = leftnodo->addr_;
//			link->flags_ = Nodo::nodoChanged;
//		}
//
//		leftnodo->size_++;
//		leftnodo->flags_ = Nodo::nodoChanged;
//	}
//
//	deletenodo( Derechonodo );
//	return true;
//}

//	===================================================================
//bool ArbolBMas::pullOut( Nodo *nodo, int itemIndex )
//{
//	Nodo *leftSubtree = 0, *DerechoSubtree = 0;
//
//	// Get subtrees
//	if ( 0 == itemIndex )
//	{
//		if ( !loadnodo( &leftSubtree, nodo->less_ ) ) return false;
//	}
//	else
//	{
//		if ( !loadnodo( &leftSubtree, nodo->elems_[ itemIndex - 1 ].link_ ) ) return false;
//	}
//
//	if ( !loadnodo( &DerechoSubtree, nodo->elems_[ itemIndex ].link_ ) ) return false;
//	if ( !leftSubtree || !DerechoSubtree ) return false;
//
//	if ( leftSubtree->count() > DerechoSubtree->count() )
//	{
//		// Left subtree is greater
//		if ( leftSubtree->hasChilds() )
//		{
//			string largestKey;
//			long largestData;
//			Nodo *largestnodo = DerechoMost( leftSubtree, largestKey, largestData );
//			nodo->elems_[ itemIndex ].key_ = largestKey;
//			nodo->elems_[ itemIndex ].data_ = largestData;
//			nodo->flags_ = Nodo::nodoChanged;
//			largestnodo->removeAt( largestnodo->count() - 1 );
//
//			Nodo *largestpadre = 0;
//			if ( !loadnodo( &largestpadre, largestnodo->padre_ ) ) return false;
//			if ( !rebalance( largestnodo, largestpadre->count() ) ) return false;
//		}
//		else
//		{
//			nodo->elems_[ itemIndex ].key_ = leftSubtree->elems_[ leftSubtree->count() - 1 ].key_;
//			nodo->elems_[ itemIndex ].data_ = leftSubtree->elems_[ leftSubtree->count() - 1 ].data_;
//			nodo->flags_ = Nodo::nodoChanged;
//			leftSubtree->removeAt( leftSubtree->count() - 1 );
//			if ( !rebalance( leftSubtree, itemIndex ) ) return false;
//		}
//	}
//	else
//	{
//		// Derecho subtree is greater
//		if ( DerechoSubtree->hasChilds() )
//		{
//			string smallestKey;
//			long smallestData;
//			Nodo *smallestnodo = leftMost( DerechoSubtree, smallestKey, smallestData );
//			nodo->elems_[ itemIndex ].key_ = smallestKey;
//			nodo->elems_[ itemIndex ].data_ = smallestData;
//			nodo->flags_ = Nodo::nodoChanged;
//			smallestnodo->removeAt( 0 );
//			if ( !rebalance( smallestnodo, 0 ) ) return false;
//		}
//		else
//		{
//			nodo->elems_[ itemIndex ].key_ = DerechoSubtree->elems_[ 0 ].key_;
//			nodo->elems_[ itemIndex ].data_ = DerechoSubtree->elems_[ 0 ].data_;
//			nodo->flags_ = Nodo::nodoChanged;
//			DerechoSubtree->removeAt( 0 );
//			if ( !rebalance( DerechoSubtree, itemIndex + 1 ) ) return false;
//		}
//	}
//
//	return true;
//}

//	===================================================================
//	BTreeAlgorithms< nodoSize, string, long, TController >::DerechoMost

//Nodo* ArbolBMas::DerechoMost( Nodo *subtree, string &largestKey, long &largestData )
//{
//	if ( subtree->elems_[ subtree->count() - 1 ].link_ )
//	{
//		Nodo *DerechoMostLink = 0;
//		if ( !loadnodo( &DerechoMostLink, subtree->elems_[ subtree->count() - 1 ].link_ ) )
//		{
//			return 0;
//		}
//
//		return DerechoMost( DerechoMostLink, largestKey, largestData );
//	}
//	else
//	{
//		largestKey = subtree->elems_[ subtree->count() - 1 ].key_;
//		largestData = subtree->elems_[ subtree->count() - 1 ].data_;
//		return subtree;
//	}
//}

//	===================================================================
//Nodo* ArbolBMas::leftMost( Nodo *subtree, string &smallestKey, long &smallestData )
//{
//	if ( subtree->less_ )
//	{
//		Nodo *leftMostLink = 0;
//		if ( !loadnodo( &leftMostLink, subtree->less_ ) )
//		{
//			return 0;
//		}
//
//		return leftMost( leftMostLink, smallestKey, smallestData );
//	}
//	else
//	{
//		smallestKey = subtree->elems_[ 0 ].key_;
//		smallestData = subtree->elems_[ 0 ].data_;
//		return subtree;
//	}
//}

//	===================================================================
//	BTreeAlgorithms< nodoSize, string, long, TController >::splitnodo
bool ArbolBMas::splitnodo( Nodo *nodo,	RegistroArbol &median, Nodo **nodoDerecho )
{
	RegistroArbol insertElem(median);

	int medianIndex = getMedian( nodo, median );

	Nodo nodoLeftTmp;
	*nodoDerecho = newnodo();

	// Replace element
	nodo->removerEnPosicion( medianIndex );
	nodo->agregarRegistro( insertElem );

	( *nodoDerecho )->less_ = median.link_;
	if ( median.link_ )
	{
		Nodo *link = 0;
		if ( !loadnodo( &link, median.link_ ) ) return false;
		link->padre_ = ( *nodoDerecho )->addr_;
		link->flags_ = Nodo::NodoCambiado;
	}
	nodoLeftTmp.less_ = nodo->less_;
	

	for ( int i = 0; i < nodo->size_; i++ )
	{
		if ( nodo->elems_[ i ]->getClave() < median.getClave() )
		{
			//nodoLeftTmp.elems_[ nodoLeftTmp.size_ ] = nodo->elems_[ i ];
			nodoLeftTmp.agregarRegistroAlFinal(*nodo->elems_[ i ]);
			//nodoLeftTmp.size_++;
		}
		else
		{
			//( *nodoDerecho )->elems_[ ( *nodoDerecho )->size_ ] = nodo->elems_[ i ];
			( *nodoDerecho )->agregarRegistroAlFinal(*nodo->elems_[ i ]);

			if ( nodo->elems_[ i ]->link_ )
			{
				Nodo *link = 0;

				bool estabaEnCache = nodoInCache( nodo->elems_[ i ]->link_ );
				if ( !loadnodo( &link, nodo->elems_[ i ]->link_ ) ) return false;
				link->padre_ = ( *nodoDerecho )->addr_;
				link->flags_ = Nodo::NodoCambiado;
				if ( link && !estabaEnCache ) releasenodo( link->addr_ );
			}
			
			//( *nodoDerecho )->size_++; //Esto lo hace mi insertar al final pero capaz lo puso aca por si fallaba lo anterior
		}
	}

	// Prepare result
	( *nodoDerecho )->padre_ = nodo->padre_;
	nodoLeftTmp.padre_ = nodo->padre_;
	nodoLeftTmp.addr_ = nodo->addr_;
	*nodo = nodoLeftTmp;

	( *nodoDerecho )->flags_ = Nodo::NodoCambiado;
	nodo->flags_ = Nodo::NodoCambiado;

	median.link_ = ( *nodoDerecho )->addr_;
	
	
	//cout<<"Impresion del nodo derecho en split()"<<endl;
	//(*nodoDerecho)->Imprimir();
	
	return true;
}

int ArbolBMas::getMedian( Nodo *nodo, RegistroArbol &elem )
{
	int medianRange = nodo->size_ >> 1;
	elem = *nodo->elems_[ medianRange ];
	return medianRange;
}

bool ArbolBMas::nodoInCache( int addr )
{
	return (buscarEnCache(addr) != NULL);
}

//	===================================================================
Nodo* ArbolBMas::findnodo( Nodo *nodo, const string &key, int &retIndex, int &padreIndex, bool &econtrado )
{
	if ( !nodo ) return 0;

	econtrado = false;
	retIndex = -1;

	if ( nodo->find( key, retIndex ) )
	{
		// Key econtrado
		econtrado = true;
		return nodo;
	}

	int link = 0;

	if ( retIndex > 0 )
	{
		link = nodo->elems_[ retIndex - 1 ]->link_;
	}
	else
	{
		link = nodo->less_;
	}

	if ( !link )
	{
		// No hay mas hijos
		return nodo;
	}
	else if ( link == nodo->addr_ )
	{
		// Simple cyclic traversal skip (in case of corrapted index)
		return 0;
	}

	Nodo *nextLink = 0;
	if ( !loadnodo( &nextLink, link ) ) return 0;

	padreIndex = retIndex;
	return findnodo( nextLink, key, retIndex, padreIndex, econtrado );
}




/////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
//Seccion stream controler
//////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////


//	===================================================================

bool ArbolBMas::open(string url)//( JStream *stor, guint maxCacheSize, JStream *journal )
{
	//storage.open(url.c_str(), ios::in | ios::out | ios::binary);
	storage.open(url.c_str(), ios::in | ios::out);
	

	if (!storage.is_open())
	{
		clearCache();		
		delete root_;
		root_ = 0;
		closeController();
		cout<<"NO SE PUDO ABRIR EL ARCHIVO DEL ARBOL"<<endl;

		return false;
	}

//Lo de abajo es para cargar en cache la raiz
//        if ( !checkJournal() )
//	{
//		int addr = rootAddr();
//		if ( addr )
//		{
//			if ( !loadNode( &root_, addr ) )
//			{
//				return false;
//			}
//		}
//
//		if ( !allocFreeSpace() ) return false;
//	}

	////1-Si el arbol esta vacio, creo un nodo raiz
	////2.-Si el arbol no esta vacio, cargo el nodo raiz
	////	2.1-Abro el archivo de nodos borrados o libres y me situo al principio
	if(storageSize() == 0)
	{	
		storage.seekp(0);	
		storage<<finCamposControl<<"|";	//Es la direccion cuando se crea por primera vez la raiz

		root_ = new Nodo();
		root_->addr_ = finCamposControl;
		rootAddr(root_->addr_);
		root_->flags_ = Nodo::NodoCambiado;

                cache_.push_back(root_);

//                int addr = finCamposControl;
//		if ( addr )
//		{
//			if ( !loadnodo( &root_, addr ) )
//			{
//				return false;
//			}
//		}
//                rootAddr(root_->addr_);
//		root_->flags_ = Nodo::NodoCambiado;

		//En realidad el for de abajo tengo q cambiarlo cuando en los primeros
		//512 escriba los datos de control y ahi completo con vacio los
		//espacios faltantes
		//Tengo q generar espacio en e; archivo si esta vacio para poder
		//hacer seekp sobre una posicion q no existe
		for(int i = 0; i < finCamposControl-4; i++) //finCamposControl-4 por q es modo texto sino va sin el 4
			storage<<" ";
		storage.seekp(0);
		
		//cout<<"ESTABA VACIO EL ARBOL CREO LA RAIZ AL ABRIR"<<endl;

		savenodo(root_);
	}
	else
	{
		//Cargar los nodos libres
		
		
		cout<<"EL ARBOL TENIA RAIZ AL ABRIR"<<endl;
		
		int addr = rootAddr();
		if ( addr )
		{
			if ( !loadnodo( &root_, addr ) )
			{
				cout<<"ERROR: No se cargo la raiz al abrir el arbol"<<endl;
				return false;
			}
		}
	}

	return true;
}

//	===================================================================
bool ArbolBMas::isOpen()
{
	return (storage.is_open());
}

int ArbolBMas::storageSize()
{
	storage.seekg(0, ios::end);  // position get-ptr 0 bytes from end
	int size = storage.tellg();  // get-ptr position is now same as file size
	
	//Si lo de abajo lo comento y funciona, borrarlo
	storage.seekg(0, ios::beg); //Ver q lo deje al principio del archivo
	
	return size;
}

//	===================================================================
//	StreamBTreeController< nodoSize, string, long >::newnodo
Nodo* ArbolBMas::newnodo()
{
	//TODO: ARBOL: Hacer q newnodo siempre cree un nodo vacio con su posicion al final del archivo sin usar los vacios??
	int addr = 0;

	//TODO: ARBOL: freeChunks creo q se refiere a los nodos liberados y q se guardan en una lista o algo asi
	if ( hayEspacioLibre() )
	{
		//freeChunks_.erase( freeChunks_.begin() );

		//addr = Obtener direccion de nodo libre del primero q esta en la lista o ultimo y borrarlo
	}
	else
	{
		//Actualizo el storageSize, esta bien hacerlo aca ya q si entro
		//aca es por q no habia nodos libres y se tiene q insertar
		//al final		
		addr = storageSize();
		//cout<<"El storage size es:" <<addr<<endl;	
	}

	Nodo *newnodo = new Nodo();
	newnodo->addr_ = addr;
	newnodo->flags_ = Nodo::NodoCambiado;

	//CacheData cacheData( newnodo );
	savenodo( newnodo );
	//cache_[ addr ] = cacheData;
	cache_.push_back(newnodo);

	return newnodo;
}

bool ArbolBMas::hayEspacioLibre(){
	return false;
}


//Guarda en el archivo de espacio libre, los espacios q se generan
//bool ArbolBMas::allocFreeSpace()
//{
//	gint64 fullSize = storage_->size() - sizeof( int )*3;
//	if ( !fullSize ) return true;
//
//	qint32 nodoCount = fullSize / sizeof( Nodo );
//	gint64 offset = sizeof( int )*3;
//
//	for ( int i = 0; i < nodoCount; i++ )
//	{
//		freeChunks_.insert( offset );
//		offset += sizeof( Nodo );
//	}
//
//	if ( !root_ ) return false;
//
//	if ( !readAllOffsets( root_ ) ) return false;
//	freeChunks_.erase( root_->addr_ );
//	releaseCache();
//	return true;
//}

//	===================================================================
//	StreamBTreeController< nodoSize, string, long >::readAllOffsets
//bool Stream::readAllOffsets(Nodo *nodo )
//{
//	if ( !nodo ) return true;
//
//	if ( nodo->less_ )
//	{
//		Nodo *less;
//		if ( !loadnodo( &less, nodo->less_ ) ) return false;
//		freeChunks_.erase( nodo->less_ );
//		readAllOffsets( less );
//		if ( less ) releasenodo( less->addr_ );
//
//		// Iterate other children if we have a less one
//		for ( int i = 0; i < nodo->count(); i++ )
//		{
//			Nodo *kid = 0;
//
//			if ( nodo->elems_[ i ].link_ )
//			{
//				if ( !loadnodo( &kid, nodo->elems_[ i ].link_ ) ) return false;
//			}
//			freeChunks_.erase( nodo->elems_[ i ].link_ );
//
//			if ( kid )
//			{
//				readAllOffsets( kid );
//				releasenodo( kid->addr_ );
//			}
//		}
//	}
//
//	return true;
//}

//	===================================================================
//void StreamBTreeController< nodoSize, string, long >::deletenodo( Nodo* nodo )
//{
//	typename ChunkCacheMap::iterator iter = cache_.find( nodo->addr_ );
//
//	if ( iter != cache_.end() )
//	{
//		cache_.erase( iter );
//	}
//
//	freeChunks_.insert( nodo->addr_ );
//	delete nodo;
//}

Nodo * ArbolBMas::buscarEnCache(int addr)
{
	for(unsigned int i = 0; i < cache_.size(); i++)
	{
		if(cache_[i]->addr_ == addr)
			return cache_[i];
	}
	
	return NULL;
}

Nodo * ArbolBMas::buscarEnCache(int addr, int &pos)
{
	pos = -1;
	for(unsigned int i = 0; i < cache_.size(); i++)
	{
		if(cache_[i]->addr_ == addr)
		{
			pos = i;
			return cache_[i];
		}
	}
	
	return NULL;
}

//	===================================================================
bool ArbolBMas::loadnodo(Nodo **nodo, int addr )
{
	if ( !addr )
	{
		*nodo = 0;
		return true;
	}

	if((*nodo = buscarEnCache(addr)) == NULL)
	{
		*nodo = new Nodo();
		storage.seekg( addr );
		*nodo = Nodo::Leer(storage);
		
		if ( addr == ( *nodo )->addr_ )
		{
			cache_.push_back(*nodo);
		}
	}

	if ( ( *nodo )->addr_ != addr )
	{
		// El storage esta corrupto!
		
		cout<<"El storage esta corrupto!"<<endl;
		return false;
	}

	return true;
}

//	===================================================================
void ArbolBMas::savenodo( Nodo *nodo )
{
	nodo->flags_ = 0;
	nodo->Guardar(storage);
}


//	===================================================================
void ArbolBMas::releasenodo( int addr )
{
	int posicionEnCache = -1;
	
	Nodo * nodo = buscarEnCache(addr, posicionEnCache);
	//typename ChunkCacheMap::iterator iter = cache_.find( addr );

	//if ( cache_.end() != iter )
	if( posicionEnCache > 0 )
	{
		if ( Nodo::NodoCambiado == nodo->flags_ )
		{
			flushChanges();
			releasenodo( addr );
			return;
		}

		//Ver como hacer este if, estaba asi pero no me da confianza
		if ( nodo != root_ )
		{
			delete nodo;
			//cache_.erase( iter );
			borrarDeCache(posicionEnCache);
		}
	}
}

void ArbolBMas::borrarDeCache(int indice)
{
	cache_.erase(cache_.begin() + indice);
}

//	===================================================================
int ArbolBMas::rootAddr()
{
	int addr = 0;
	//storage_->seek( sizeof( int ) );
	//storage_->read( ( char* ) &addr, sizeof( addr ) );

	//Servetto dijo q la raiz siempre la situemos a 512bytes para dejar lugar a los campos de control
	//Voy a escribir la posicion de la raiz al principio del archivo, si tengo lio ver el streamer donde lo hacia
	storage.seekg(0);
	//Aca despues tengo q usar read
	char delimitador;
	storage>>addr>>delimitador;
	
	cout<<"La direccion de la raiz en el disco es:"<<addr<<endl;
	
	return addr;
}

void ArbolBMas::rootAddr(int addr)
{
	//Abria q guardar el la nueva direccion de la raiz al principio??
	rootAddr_ = addr;
}


Nodo * ArbolBMas::getRaiz()
{
	return root_;
}



//	===================================================================
void ArbolBMas::closeController()
{
	//Usaba cache_.clear() pero tengo q eliminar los Nodos q tienen los punteros
	for(unsigned int i = 0; cache_.size(); i++)
	{
		delete cache_[i];
	}

//	if ( storage_ )
//	{
//		if ( !freeChunks_.empty() )
//		{
//			// Save removed nodos list
//			guint rlistAddr = storage_->size();
//			QByteArray rblock;
//			FreeChunksSet::const_iterator iter = freeChunks_.begin();
//			guint aaddr = 0;
//			for ( ; iter != freeChunks_.end(); iter++ )
//			{
//				aaddr = *iter;
//				rblock.resize( rblock.size() + sizeof( aaddr ) );
//				::memcpy( rblock.data() + rblock.size() - sizeof( aaddr ),
//					( char* ) &aaddr, sizeof( aaddr ) );
//			}
//			freeChunks_.clear();
//
//			storage_->seek( rlistAddr );
//			storage_->write( rblock.data(), rblock.size() );
//
//			storage_->seek( constRemovedAddr );
//			storage_->write( ( char* ) &rlistAddr, sizeof( rlistAddr ) );
//		}
//
//		storage->close();
//		storage_ = 0;
//	}
}


void ArbolBMas::flushChanges()
{
	if ( !isOpen() ) return;

	// Grabo los nodos en cache
	int tamanioCache = cache_.size();
	for (int i = 0; i < tamanioCache ;i++)
	{
		if ( Nodo::NodoCambiado == cache_[i]->flags_ )
		{
			// Save node
			savenodo( cache_[i] );
		}
	}

	// Write root
	if ( rootAddr_ )
	{
		storage.seekp(0); //posicion donde guardo direccion de la raiz
		//Aca despues tengo q usar write
		storage<<rootAddr_<<"|";
		rootAddr_ = 0; //Ver por q pone esto aca el original
	}
}

void ArbolBMas::releaseCache()
{
	//if ( cache_.size() > maxCacheSize_ )
	//{
		clearCache();
	//}
}

void ArbolBMas::clearCache()
{
	flushChanges();

        //Vacio la cache eliminando los nodos q no sean la raiz
	for(unsigned int i = 0; i <cache_.size(); i++)
	{
		//TODO: Guarda con las comparaciones estas
		if ( cache_[i] != root_ )
		{		
			delete cache_[i];
		}
	}

        //Limpio el vector cache de referencias invalidas
        cache_.clear();
	

        //Si la raiz esta en memoria la cargo a la cache
        if ( root_ )
	{
		cache_.push_back(root_);
	}
}

