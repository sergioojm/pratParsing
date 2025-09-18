#include "Lexer.h"
#include "Expression.h"
#include "Token.h"
#include <cstdlib>
#include <iostream>

using namespace std;

#define ASSERT_LEXER(x, m) if (!x) { std::cout << "Invalid token -> " << m << std::endl; exit(0); }

Lexer::Lexer()
{
  this->tokens = ListaEnlazada();
}

Lexer::~Lexer()
{
  this->tokens.~ListaEnlazada();
}


void Lexer::parse(const string input)
{

  char* p = (char*)input.c_str();

  while (*p != '\0')
  {
    if (*p == ' ') { p++; }

    if (*p >= '0' && *p <= '9')
    {
      float num = 0.0;
      num += atof(p);
      this->tokens.insertar(this->tokens.getN(), new Token(num));

      while (*p >= '0' && *p <= '9') { p++; }
    }

    if (*p == '+' || 
        *p == '-' ||
        *p == '*' ||
        *p == '/')
    {
      this->tokens.insertar(this->tokens.getN(), new Token(*p));
      p++;
    }

    p++;
  }

  this->tokens.insertar(this->tokens.getN(), new Token('\0'));
}

Expression* Lexer::execute(float r_binding_power)
{

  Token* lhs_token = this->tokens.next();
  ASSERT_LEXER(lhs_token->isNum(), lhs_token->getNum() << " lhs is not a number");

  Expression* lhs = new Expression();
  lhs->value = lhs_token;

  while (true)
  {

    Token* op = this->tokens.peek();
    if (op->getOperador() == '\0') { break; }

    float* weights = this->getWeightBinding(op->getOperador());   
    if (weights[0] < r_binding_power) { break; }


    this->tokens.next(); // consumimos el operador

    Expression* expr = new Expression();
    expr->left = lhs;
    expr->operador = op;
    expr->right = this->execute(weights[1]);

    lhs = expr;
  }

  return lhs;
}

void Lexer::printExpr(Expression* expr)
{

  if (!expr) return;

  if (expr->value)
  {
    cout << expr->value->getNum();
  }
  else
  {
    cout << "(";
    printExpr(expr->left);
    cout << " " << expr->operador->getOperador() << " ";
    printExpr(expr->right);
    cout << ")";
  }
}


float* Lexer::getWeightBinding(char operador)
{


  float* result = new float[2];
  result[0] = 0.0; 
  result[1] = 0.0; 

  if (operador == '\0') return result;
 

  if (operador == '+' || operador == '-')
  {
    result[0] = 1.0;
    result[1] = 1.1;
  }

  if (operador == '*' || operador == '/')
  {
    result[0] = 2.0;
    result[1] = 2.1;
  }

  return result;
}
