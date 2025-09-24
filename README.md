# PRAT PARSING TOOL


¡Hola! Este repositorio es una herramienta para analizar expresiones matematicas simples
utilizando el algoritmo de prat parsing implementado en c++.


## Operaciones soportadas:
- Suma (+)
- Resta (-)
- Multiplicación (*)
- División (/)
- Paréntesis para agrupar operaciones


[!warning]
Esta herramienta está diseñada para analizar expresiones matemáticas simples y puede no manejar casos complejos, errores de sintaxes o números no enteros.

## Para compilar:

```bash
g++ main.cpp Lexer.cpp ListaEnlazada.cpp Token.cpp -o prat_parser
```

```bash
./prat_parser 
```

[!tip] 
Utiliza "exit" para salir del programa.



