/*FUNCIONES.C Para el manejo del sudoku*/

/*#define VERBOSE*/
#include "stdafx.h"
#include "ficheros.h"
#include "funciones.h"


int Inicializa(int sudoku[9][9]) {

	/*Función que permite inicializar el sudoku. Devuelve un 0 si todo ha
	*ido bien y un 1 si ha habido algun fallo*/

	/*Se utiliza una variable auxiliar para la toma de decisiones*/
	char aux;

	/*Se da a elegir si inicializar desde el teclado o desde un fichero*/
	printf("Que desea?\n");
	printf("Introducir los numeros desde el teclado? (1)\n");
	printf("Introducir los numeros desde un fichero? (2)\n");
	fflush(stdin);
	scanf(" %c", &aux);

	if (aux == '1') {
		/*Si lee el 1, inicializa desde el teclado mediante la función escribe
		*Si esta función funciona correctamente, devuelve un 0, y mi sudoku
		*contendra todos los valores necesarios, si no imprime un mensaje de
		*error y devuelve un 1*/

		if (!Escribe(sudoku)) printf("Sudoku correctamente inicializado\n");
		else {
			printf("Error al inicializar sudoku\n");
			return 1;
		}
	}
	else if (aux == '2') {
		/*Si lee el 2, inicializa el sudoku desde un fichero mediante la función
		*abrefichero.
		*Si esta función funciona correctamente, devuelve un 0, y mi sudoku
		*contendra todos los valores necesarios, si no imprime un mensaje de
		*error y devuelve un 1*/

		if (!Abrefichero(sudoku)) printf("Fichero abierto correctamente\n");
		else {
			printf("Error al abrir el fichero\n");
			return 1;
		}
	}
	/*Si lee cualquier otra cosa, devuelve un 1*/
	else return 1;
	return 0;
}

void Representa(int sudoku[9][9]) {

	/*Función que representa el sudoku. Se utilizan los caracteres - y | para
	*poder visualizar mejor los diferentes cuadros del sudoku*/

	int i, j;
	printf("\n");

	for (i = 0; i<9; i++) {

		if (i == 3 || i == 6) {
			/*Cuando llevamos 3 y 6 iteraciones imprimimos 11 guiones y cambiamos
			*de linea, es decir, sacamos por pantalla una linea vertical*/
			for (j = 0; j<11; j++) printf("- ");
			printf("\n");
		}

		for (j = 0; j<9; j++) {
			/*Imprimimos una fila del sudoku.*/
			printf("%d ", sudoku[i][j]);
			/*Cuando llega a j=2 y j=5, imprime ademas una barra | que al final del bucle
			*forma dos lineas verticales*/
			if (j == 2 || j == 5) printf("| ");
		}
		printf("\n");
	}
}


int Escribe(int sudoku[9][9]) {

	/*Función que escribe los elementos del sudoku uno a uno.
	*Si esta función funciona correctamente, devuelve un 0, y mi sudoku
	*contendra todos los valores necesarios, si no imprime un mensaje de
	*error y devuelve un 1.*/

	int i, j, aux;

	printf("Introduzca un numero entero del 1 al 9. ");
	printf("Si se desconoce el numero escriba un 0\n");

	for (i = 0; i<9; i++) {

		printf("Introduzca los elementos de la fila %d\n", i);

		for (j = 0; j<9; j++) {

			printf("Columna %d: ", j);
			fflush(stdin);
			scanf(" %d", &aux);
			/*Se utiliza el 0 para indicar que la posición del sudoku es a priori
			*desconocida.*/
			if (aux >= 0 && aux <= 9) sudoku[i][j] = aux;
			else return 1;
		}
	}
	return 0;
}




int Resuelve(int sudoku[9][9]) {

	/*Función que resuelve el sudoku. Devuelve un 0 si todo va bien y 1 si no puede resolver*/
	int i, j, m, a, b, suma, aux, posible;
	while (1) {
		int candidatos[9][9][9] = { 0 };
		aux = 0;
		posible = 0;

		/*En la primera parte de la funcion Resuelve se hace una pasada rapida a las filas columnas y subcuadrados para rellener los candidatos de cada casilla.
		Si alguna casilla tiene un unico candidato se rellena con este.*/

		for (i = 0; i<9; i++) {
			for (j = 0; j<9; j++) {
#ifdef VERBOSE
				printf("  [%d][%d]  ", i, j);
#endif
				/*si la casilla contiene un numero pongo sus candidatos a 1 para indicar que no tiene ninguno posible*/
				if (sudoku[i][j]) {
					for (a = 0; a<9; a++) {
						candidatos[i][j][a] = 1;
					};
					aux++;
					continue;
				}
				/*para la casilla [i][j] busca en su fila los numeros escritos en el sudoku y los elimina de los candidatos (pone un 1)*/
				for (m = 0; m<9; m++)
					if (sudoku[m][j]) candidatos[i][j][sudoku[m][j] - 1] = 1;
				/*lo mismo que antes para la columna de la casilla [i][j]*/
				for (m = 0; m<9; m++)
					if (sudoku[i][m]) candidatos[i][j][sudoku[i][m] - 1] = 1;
				/*lo mismo que antes pero para el subcuadrado al que pertenece la casilla [i][j]*/
				for (a = 0; a<3; a++)
					for (b = 0; b<3; b++)
						if (sudoku[i - i % 3 + a][j - j % 3 + b]) candidatos[i][j][sudoku[i - i % 3 + a][j - j % 3 + b] - 1] = 1;

				/*suma los candidatos eliminados para la casilla, si la suma es 8 entonces es que solo queda un candidato posible para esa casilla
				por lo que debe introducirlo*/
				for (m = 0, suma = 0; m<9; m++) suma += candidatos[i][j][m];

				if (suma == 8) {
					for (m = 0; m<9; m++) {
						if (candidatos[i][j][m] == 0) {
							sudoku[i][j] = m + 1;
							aux++;
							posible++;
							break;
						}
					}
				}/*fin del if(suma==8)*/

			}/*fin del for(j=0; j<9; j++)*/

		}/*fin del for(i=0; i<9; i++)*/

		 /*Si en una pasada no ha sido capaz de resolver nada, (posible==0) la funcion CandidatoExclusivo comprueba para cada
		 candidato de cada casilla si es exclusivo para su fila/columna/subcuadrado, en el caso de que lo sea debe introducir ese numero
		 La funcion devuelve un 0 si ha podido introducir un numero y un 1 en caso contrario*/

		if (!posible) CandidatoExclusivo(sudoku, candidatos, &aux, &posible);

#ifdef VERBOSE
		printf("posible %d  ", posible);
		printf("\n----aux %d-----\n  ", aux);
#endif
		/*si la variable aux==81 se ha completado el sudoku, Resolver devuelve un 0*/
		if (aux == 81) return 0;

		/* La funcion fallo comprueba que no haya ninguna casilla sin posibles candidatos, en ese caso se ha introducido algun numero incorrecto*/
		if (Fallo(candidatos, sudoku)) {
#ifdef VERBOSE
			printf("\n vuelvo atras, me ha dado FALLO\n");
#endif
			return 1;
		};

		/*si aun no se puede resolver pasamos a metodo recursivo:*/
		if (!posible) {
#ifdef VERBOSE
			printf("suponiendo...........\n");
			Representa(sudoku);
#endif
			if (!Suponer(sudoku, candidatos, aux, posible)) return 0;
			else return 1;
		}

	}

}

int CandidatoExclusivo(int sudoku[9][9], int candidatos[9][9][9], int* aux, int* posible) {
	int i, j;
	for (i = 0; i<9; i++) {
		for (j = 0; j<9; j++) {
#ifdef VERBOSE
			printf("casilla [%d] [%d] \n", i, j);
#endif
			/*si la casilla ya esta rellenada, pasa a la siguiente*/
			if (sudoku[i][j])continue;
			/* la variable cand se utiliza para barrer los posibles candidatos*/
			int t, s, cand;

			/*Comprueba si algun candidato es exclusivo para la fila*/
			for (cand = 0; cand<9; cand++) {
#ifdef VERBOSE
				printf("fila %d  ", cand);
#endif
				if (!(candidatos[i][j][cand])) {
					s = 0;
					for (t = 0; t<9; t++) if (candidatos[t][j][cand])s++;
					/*si esa fila el candidato unicamente se encuentra en esa casilla entonces s habra acumulado una suma de 8*/
					if (s == 8) {
						/*asigno a la casilla el valor de cantidato*/
						sudoku[i][j] = cand + 1;
						(*aux)++;
						(*posible)++;
						/* al haber introducido un numero en la casilla no se comprueban los demas candidatos, la funcion CandidatoExclusivo devuelve un 0*/
						return 0;
					}
				}

			}

			/*Comprueba si algun candidato es exclusivo para la columna*/

			for (cand = 0; cand<9; cand++) {
#ifdef VERBOSE
				printf("columna %d  ", cand);
#endif
				if (!(candidatos[i][j][cand])) {
					s = 0;
					for (t = 0; t<9; t++)
						if (candidatos[i][t][cand])s++;
					if (s == 8) {
						sudoku[i][j] = cand + 1;
						(*aux)++;
						(*posible)++;
						return 0;
					}

				}
			}


			/*Comprueba si algun candidato es exclusivo para el subcuadrado*/
			int a = 0, b = 0;
			for (cand = 0; cand<9; cand++) {
#ifdef VERBOSE
				printf("cuadrado %d", cand);
#endif
				if (!(candidatos[i][j][cand])) {
					s = 0;
					for (a = 0; a<3; a++)
						for (b = 0; b<3; b++)
							if (candidatos[i - i % 3 + a][j - j % 3 + b][cand]) s++;
					if (s == 8) {
						sudoku[i][j] = cand + 1;
						(*aux)++;
						(*posible)++;
						return 0;
					}

				}
			}

		}/*fin del bucle de las filas*/

	}/* fin del bucle de las columnas*/
	 /*Una vez fuera de los bucles for ha barrido todas las casillas sin encontrar ningun candidato exclusivo por lo que devuelve un 1*/
	return 1;
}


/* Suponer utiliza metodos recursivos para hallar la solucion del sudoku cuando los demas metodos han fallado.
La funcion suponer devuelve un 1 cuando han fallado todos los candidatos de una casilla y un 0 cuando se ha encontrado una solucion.
*/

int Suponer(int sudoku[9][9], int candidatos[9][9][9], int aux, int posible) {
	int auxsudoku[9][9];/* Se utiliza para guardar el estado de sudoku[][] cuando entra en la funcion suponer, y poder recuperarlo en el
						caso de haber supuesto mal*/
	int a = 0, b;
	int suma; /*almacena la suma de los candidatos de un unico hueco*/
	int *casilla_supuesta = NULL; /*almacena la direccion del hueco del sudoku que contiene una cantidad menor de numeros posibles */
	int columna_supuesta = 0;
	int fila_supuesta = 0;
	int i, j, m;
	for (i = 0; i<9; i++) { /* Busca la casilla candidato con menos posibles numeros para luego asignarle un valor supuesto */
		for (j = 0; j<9; j++) {
			suma = 0;
			for (m = 0; m<9; m++) suma += candidatos[i][j][m];
			if (suma >= a && suma<9) {
				a = suma;
				casilla_supuesta = &(sudoku[i][j]);
				fila_supuesta = i;
				columna_supuesta = j;
			}
		}
	}

#ifdef VERBOSE
	printf("\n suponiendo en casilla: [%d] [%d] \n", i + 1, j + 1);
#endif

	/*guardo el sudoku en uno auxiliar para volver a el en el caso de haber supuesto mal el valor a la casilla candidato*/
	for (a = 0; a<9; a++)
		for (b = 0; b<9; b++) auxsudoku[a][b] = sudoku[a][b];

	//asignamos un valor a la casilla candidato
	for (m = 0; m<9; m++) {
		if (!candidatos[fila_supuesta][columna_supuesta][m]) {
			*casilla_supuesta = m + 1;
#ifdef VERBOSE
			Representa(sudoku);
#endif
			//se intenta resolver el sudoku con el valor supuesto en la casilla candidato
			//se entra dentro de un bucle recursivo, en caso de llegar a un sudoku sin solución se retrocede un paso y se asigna otro valor posible al candidato
			if (!Resuelve(sudoku)) return 0;
			for (a = 0; a<9; a++)
				for (b = 0; b<9; b++) sudoku[a][b] = auxsudoku[a][b];
		}
	}
	return 1;
}


/*La funcion Fallo comprueba que no haya ninguna casilla del sudoku en la que no se pueda poner ningun numero.
*Si da Fallo es que se ha rellenado algun numero mal y la funcion devuelve un 1.*/

int Fallo(int candidatos[9][9][9], int sudoku[9][9]) {
#ifdef VERBOSE
	printf("\n prueba fallo \n");
#endif
	int aux, i, j;
	for (i = 0; i<9; i++) {
		for (j = 0; j<9; j++) {
			if (sudoku[i][j]) continue; /*Si la casilla ya contiene un numero no lo comprueba.*/
			for (aux = 0; aux<9; aux++) if (!(candidatos[i][j][aux])) break;
			/* aux habra acumulado una suma de 9 si la casilla vacia no tiene ningun candidato, por lo que se da el Fallo y la funcion devuelve un 1*/
			if (aux == 9)  return 1;
		}
	}
	/*si se han recorrido todas las casillas sin ningun fallo entonces podemos seguir resolviendo el sudoku, la funcion Fallo devuelve un 0*/
	return 0;
}


