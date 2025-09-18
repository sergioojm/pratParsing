#include "ListaEnlazada.h"
#include <stdlib.h>


using namespace std;

Nodo * ListaEnlazada::getNodo (int posicion) 
{
	Nodo* actual = this->lista;
	for (int i = 0; i < posicion; i++)
	{
		actual = actual->siguienteNodo;
	}
	
	return actual;
}

ListaEnlazada::ListaEnlazada() 
{
	this->lista = nullptr;
	this->n = 0;
}

Token* ListaEnlazada::getValor(int posicion) 
{
	return getNodo(posicion)->elemento;
}

Token* ListaEnlazada::peek() 
{
  if (this->n == 0) return nullptr;
  return this->lista->elemento;
}


Token* ListaEnlazada::next() 
{
  if (this->n == 0) return nullptr;

  if (this->n == 1)
  {
    Token* token = this->lista->elemento;
    delete this->lista;
    this->lista = nullptr;
    this->n = 0;
    return token;
  }
  else 
  {
    if (this->lista == nullptr) return nullptr;

    Nodo* nodoAnterior = this->lista;
    this->lista = this->lista->siguienteNodo;

    Token* token = nodoAnterior->elemento;
    delete nodoAnterior;

    this->n--;
    return token;
  }
}

void ListaEnlazada::setValor(int posicion, Token* nuevoValor) 
{
	getNodo(posicion)->elemento = nuevoValor;
}

int ListaEnlazada::getN() 
{
	return this->n;
}

void ListaEnlazada::insertar (int posicion, Token* nuevoValor) 
{
	if (posicion < 0) return;

  Nodo* nuevoNodo = new Nodo;
  nuevoNodo->elemento = nuevoValor;
	nuevoNodo->siguienteNodo = nullptr;

  if (posicion == 0)
	{
		nuevoNodo->siguienteNodo = this->lista;
		this->lista = nuevoNodo;
	}
	else
	{
		Nodo* nodoAnterior = getNodo(posicion - 1);
		
		nuevoNodo->siguienteNodo = nodoAnterior->siguienteNodo;
		nodoAnterior->siguienteNodo = nuevoNodo;
	}

	this->n++;
}


void ListaEnlazada::eliminar (int posicion) 
{
	if (posicion < 0) return;
	
	Nodo* paBorrar = nullptr;
	
	if (posicion == 0)
	{
		paBorrar = this->lista;
		this->lista = this->lista->siguienteNodo;
	}
	else
	{
		Nodo* nodoAnterior = getNodo(posicion - 1);
		
		paBorrar = nodoAnterior->siguienteNodo;
		nodoAnterior->siguienteNodo = paBorrar->siguienteNodo;
	}	
	
	this->n--;
	delete paBorrar;
}

ListaEnlazada::~ListaEnlazada() 
{
	this->n = 0;
	
	Nodo* actual = this->lista;
	
	while(actual != nullptr)
	{
		Nodo* temp = actual;
		actual = actual->siguienteNodo;
		delete temp;
	}
	
	delete actual;
}



