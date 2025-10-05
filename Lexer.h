#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include "Expression.h"
#include "Token.h"
#include "ListaEnlazada.h"

using namespace std;

class Lexer
{

  ListaEnlazada tokens;


  public:
    Lexer();
    ~Lexer();

    float* getWeightBinding(char operador);
    void parse(const string input);
    Token* peek();
    Token* next();

    void printExpr(Expression* expr);
    double resolve(Expression* expr);
    Expression* execute(float r_binding_power = 0.0f);

};

#endif
