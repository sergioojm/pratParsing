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
    lex->printExpr(lex->execute());
    cout << endl;
  }

// conchi  

  return 0;
}
