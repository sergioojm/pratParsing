#include <string>


#ifndef TOKEN_H
#define TOKEN_H



using namespace std;


class Token
{
  float num;
  char operador;

  public:
    Token(float num);
    Token(char operador);

    float getNum();
    char getOperador();

    bool isNum();
    bool isOperador();

};

#endif 
