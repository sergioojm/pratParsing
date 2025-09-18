#pragma once


#include "Token.h"

struct Expression 
{
  Token *operador;
  Expression *left;
  Expression *right;
  Token *value;

  Expression() : operador(nullptr), left(nullptr), right(nullptr), value(nullptr) {}
};

