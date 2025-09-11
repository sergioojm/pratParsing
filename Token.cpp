#include "Token.h"



Token::Token(float num)
{
  this->num = num;
  this->operador = '\0';
}

Token::Token(char operador)
{
  this->operador = operador;
  this->num = 0.0f;
}

bool Token::isNum()
{
  return this->operador == '\0';
}

bool Token::isOperador()
{
  return this->operador != '\0' && this->num == 0.0f;
}

float Token::getNum()
{
  return this->num;
}

char Token::getOperador()
{
  return this->operador;
}



