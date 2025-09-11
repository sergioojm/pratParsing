#pragma once

#include "Token.h"

struct Nodo
{
	Token *elemento; 
  Nodo *siguienteNodo;

  Nodo() : elemento(nullptr), siguienteNodo(nullptr) {}

};

