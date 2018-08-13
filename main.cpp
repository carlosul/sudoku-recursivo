/*Programa principal Sudoku*/

#include "stdafx.h"
#include "funciones.h" /* Para el manejo del Sudoku*/
#include "ficheros.h" /* Para el manejo de ficheros*/

int main()
{
	/*Guardamos el sudoku en una matriz de 9*9 enteros*/
	int sudoku[9][9] = { { 0 } };

	/*Variable para la toma de decisiones*/
	char aux;

	/*Variable que vale 0 si se quiere volver a empezar con el programa cuando
	*se llega al final, o 1 si se desea finalizar*/
	int termina_programa = 0;


	/*El programa es un bucle infinito*/

	while (!termina_programa) {
		/*Se inicializa el sudoku mediante la funcion inicializa, que devuelve un 1
		*si algo ha fallado y un 0 si no ha habido problemas. Se da la oportunidad de
		*volver a intentar inicializar el sudoku las veces que deseemos mediante un
		*while.*/

		while (Inicializa(sudoku)) {
			printf("Desea salir?(S/N)\n");
			fflush(stdin);
			scanf(" %c", &aux);
			if (aux == 'S' || aux == 's') return 0;
		}

		/*Se da a elegir guardar la posicion inicial en el fichero mediante la funcion
		*posicioninicial.
		*Esta devuelve un 1 si algo ha fallado y un 0 si no ha habido problemas.
		*Si se produce algun error, el programa es robusto y vuelve a preguntar*/

		while (Posicioninicial(sudoku)) {
			printf("Desea salir?(S/N)\n");
			fflush(stdin);
			scanf(" %c", &aux);
			if (aux == 'S' || aux == 's') return 0;
		}

		/* sacamos por pantalla la posicion inicial del sudoku que queremos resolver*/
		printf("\n Sudoku inicial a resolver: \n");
		Representa(sudoku);


		/*Con la funcion resuelve se resuelve el sudoku anteriormente introducido.
		*Esta funcion devuelve un 0 si todo ha ido bien y un 1 si ha fallado.
		*Si falla en la resolucion del sudoku, se termina el programa, devolviendo
		*como cadigo de error un 1*/

		if (!Resuelve(sudoku)) {
			printf("\n Solucion hallada:\n");
			Representa(sudoku);
		}
		else {
			printf("\n Solucion no encontrada");
			return 1;
		}

		/*Con la funcion posicionfinal podemos almacenar en un fichero el sudoku resuelto.
		*La funcion devuelve un 0 si todo ha ido bien y un 1 si ha habido algun fallo.
		*Da la opcion de volver a intentar guardarlo en el fichero si se ha producido el
		*error.*/

		while (Posicionfinal(sudoku)) {
			printf("Desea salir?(S/N)\n");
			fflush(stdin);
			scanf(" %c", &aux);
			if (aux == 'S' || aux == 's') return 0;
		}

		do {
			/* variable para guardar la decision de acabar el programa*/
			int decide;
			printf("Programa terminado. Desea salir (1) o volver al inicio (0)?\n");
			fflush(stdin);
			scanf_s(" %d", &decide);
			if (decide == 1 || decide == 0) termina_programa = decide;
		} while (termina_programa != 0 && termina_programa != 1);

	}


	return 0;
}




