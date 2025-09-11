#pragma once
#include "Nodo.h"

class ListaEnlazada
{
	Nodo *lista;
	int n;
	Nodo * getNodo (int posicion);

public:

	ListaEnlazada();

	Token* getValor(int posicion);
	void setValor(int posicion, Token* nuevoValor);
	int getN(); 
	void insertar (int posicion, Token* nuevoValor);
	void eliminar (int posicion);
	void imprimir();
  Token* peek();
  Token* next();

	~ListaEnlazada();
};







