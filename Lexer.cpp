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
    // se pueden eliminar los continue utilizando else if 


    if (*p == ' ') { p++; }

    if (*p >= '0' && *p <= '9')
    {
      float num = 0.0;
      num += atof(p);
      this->tokens.insertar(this->tokens.getN(), new Token(num));

      while (*p >= '0' && *p <= '9') { p++; }
      continue;
    }

    if (*p == '+' || 
        *p == '-' ||
        *p == '*' ||
        *p == '/' ||
        *p == '(' ||
        *p == ')')
    {
      this->tokens.insertar(this->tokens.getN(), new Token(*p));
      p++;
      continue;
    }
  
    cout << "Invalid character: " << *p << endl;
    p++;
  }

  this->tokens.insertar(this->tokens.getN(), new Token('\0'));
}

Expression* Lexer::execute(float r_binding_power)
{

  Expression* lhs = new Expression();
  
  Token* lhs_token = this->tokens.next();
 
  if (lhs_token->isNum())
  {
    lhs->value = lhs_token;
  }
  else if (lhs_token->getOperador() == '(') 
  {
    lhs = this->execute(0.0);
    lhs_token = this->tokens.next();

    if (lhs_token->getOperador() != ')') 
    { 
      cout << "bad token" << endl; 
      return nullptr; 
    }
  }

  while (true)
  {
    Token* op = this->tokens.peek();
    if (op->getOperador() == '\0') { break; }
    if (op->getOperador() == ')') { break; }

    float* weights = this->getWeightBinding(op->getOperador());   
    if (weights[0] < r_binding_power) { break; }


    this->tokens.next(); // consumimos el operador

    Expression* expr = new Expression();
    expr->left = lhs;
    expr->operador = op;
    expr->right = this->execute(weights[1]);

    delete [] weights;

    lhs = expr;
  }

  return lhs;
}

double Lexer::resolve(Expression* expr)
{
  if (!expr) return 0.0;

  if (expr->value)
  {
    return expr->value->getNum();
  }
  else if (!expr->left && !expr->right)
  {
    cout << "nodo no tiene nada" << endl;
    return 0.0;
  }
  else
  {
    double left = resolve(expr->left);
    double right = resolve(expr->right);
    char op = expr->operador->getOperador();

    switch (op)
    {
      case '+': return left + right;
      case '-': return left - right;
      case '*': return left * right;
      case '/': 
        if (right == 0.0)
        {
          cout << "division by 0" << endl;
          return 0.0;
        }
        return left / right;
      case '(': return 0.0;
      case ')': return 0.0;
      default:
        cout << "Unknown operator: " << op << endl;
        return 0.0;
    }
  }
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
