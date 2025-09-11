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

  Expression *expr = new Expression();
  expr->operando1 = new Token(0.0f);
  expr->operando2 = new Token(0.0f);
  expr->operador = new Token('\0');

  Token* lhs = this->tokens.next();
  ASSERT_LEXER(lhs->isNum(), lhs->getNum() << " lhs is not a number");

  expr->operando1 = lhs;

  int isEof = 0;

  while (isEof == 0 && this->tokens.getN() > 0)
  {

    Token* op = this->tokens.next();
    if (op->getOperador() == '\0') { isEof = 1; break; }
    ASSERT_LEXER(op->isOperador(), op->getOperador() << " is not an operator");

    expr->operador = op;
    float* weights = this->getWeightBinding(op->getOperador());
   
    if (weights[0] < r_binding_power)
    {
      break;
    }

    Expression* rhs = execute(weights[1]);
    ASSERT_LEXER(rhs->operando1->isNum(), rhs->operando1->getNum() << " rhs is not a number");
    expr->operando2 = rhs->operando1;
// rehacer la movida de la expression, en rhs te estas fumando el operando2
  }

  cout << expr->operando1->getNum() << " " 
       << expr->operador->getOperador() << " " 
       << (expr->operando2 ? expr->operando2->getNum() : 0.0f) << endl;

  return expr;
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






