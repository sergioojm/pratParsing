#include "Expression.h"
#include "Lexer.h"
#include <iostream>

#define CONSOLE_INPUT ">> "

using namespace std;

int main()
{

  string expresion = "";

  while (expresion.compare("exit") != 0)
  {

    cout << CONSOLE_INPUT;
    getline(cin, expresion);
    cout << endl;

    if (expresion.compare("exit") == 0 || expresion.empty())
    {
      cout << "Exiting..." << endl;
      return 0;
    }

    Lexer* lex = new Lexer();

    lex->parse(expresion);
    Expression* expr = lex->execute();
    lex->printExpr(expr);
    cout << " -> " << lex->resolve(expr);
    cout << endl;
    expresion = "";
  }

// conchi  

  return 0;
}
