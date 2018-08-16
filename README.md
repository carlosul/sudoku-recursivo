# sudoku-recursivo
 
Este programa utiliza un algoritmo recursivo para resolver cualquier sudoku. Primero se utiliza una metodología de descarte para hallar todos los valores posibles. En segundo lugar mediante un algoritmo recursivo se itera entre todos los valores posibles para hallar la solución correcto.

Fue parte de una trabajo de clase en los cursos de programación de la universidad. El trabajo fue desarrollado en C y posteriormente se transformó a OOP como proyecto personal.

Hay dos versiones disponibles que se encuentran en distintas carpetas:
- sudoku-recursivo/c/ : programa en C
  contiene
    ficheros.cpp: gestiona la lectura y escritura de los archivos
    ficheros.h: archivo cabecera de ficheros.cpp
    funciones.cpp: funciones principales para la resolución del sudoku
    funciones.h: archivo cabecera de funciones.cpp
    main.cpp: programa principal
- sudoku-recursivo/cpp/ : programa en C++
  contiene
    sudoku.cpp: clase Sudoku que contiene todas las funciones de cálculo y gestion de archivos
    sudoku.h: cabecera de sudoku.cpp
    main.cpp: programa principal

El programa se ejecuta en la consola, por donde se van recibiendo las instrucciones. 
Se tiene la opción de introducir los valores del sudoku mediante teclado o gargando un archivo. A continuacion el programa reselve el sudoku y muestra por consola el resultado. Se da la posibilidad de guardar la solución obtenida así como el sudoku inicial.


