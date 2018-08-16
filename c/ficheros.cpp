/*FICHEROS.C para el manejo de ficheros*/
#include "stdafx.h"
#include "funciones.h"
#include "ficheros.h"

int Posicionfinal(int sudoku[9][9]) {

	/*Funcion que guarda la posicion inicial del fichero. Devuelve un 0 si todo
	*ha ido bien y un 1 si se ha producido un fallo*/

	/*Dos variables auxiliares para la toma de decisiones*/
	char aux1, aux2;

	printf("Desea guardar la posicion final en un fichero?(S/N)\n");
	fflush(stdin);
	scanf(" %c", &aux1);

	/*Si no se desea guardar nada, se acaba el programa sin errores*/
	if (aux1 == 'N' || aux1 == 'n') return 0;

	/*Si se desea guardar algo, se llama a la funcion guardafichero, que me devuelve un
	*1 si se ha producido algun error guardando el archivo y un 0 si todo ha ido bien.
	*Se da la oportunidad de volver a repetir el proceso si ha ocurrido algun fallo*/
	else if (aux1 == 'S' || aux1 == 's') {
		while (Guardafichero(sudoku)) {
			printf("Error abriendo archivo. Desea repetir?(S/N)\n");
			fflush(stdin);
			scanf(" %c", &aux2);

			if (aux2 == 'N' || aux2 == 'n') return 0;
			else if (aux2 != 'S' || aux2 != 's') {
				printf("Error: Caracter no valido\n");
				return 1;
			}
		}
	}

	/*Si no se reconoce lo leido, se devuelve un codigo de error*/
	else {
		printf("Error: Caracter no valido\n");
		return 1;
	}

	return 0;
}


int Posicioninicial(int sudoku[9][9]) {

	/*Funcion que guarda la posicion inicial del fichero. Devuelve un 0 si todo
	*ha ido bien y un 1 si se ha producido un fallo*/

	/*Dos variables auxiliares para la toma de decisiones*/
	char aux1, aux2;

	printf("Desea guardar la posicion inicial en un fichero?(S/N)\n");
	fflush(stdin);
	scanf(" %c", &aux1);

	/*Si no se desea guardar nada, se acaba la funcion y se continua con el programa
	*sin errores*/
	if (aux1 == 'N' || aux1 == 'n') return 0;

	/*Si se desea guardar algo, se llama a la funcion guardafichero, que me devuelve un
	*1 si se ha producido algun error guardando el archivo y un 0 si todo ha ido bien.
	*Se da la oportunidad de volver a repetir el proceso si ha ocurrido algun fallo*/
	else if (aux1 == 'S' || aux1 == 's') {
		while (Guardafichero(sudoku)) {
			printf("Error abriendo archivo. Desea repetir?(S/N)\n");
			fflush(stdin);
			scanf(" %c", &aux2);

			if (aux2 == 'N' || aux2 == 'n') return 0;
			else if (aux2 != 'S' || aux2 != 's') {
				printf("Error: Caracter no valido\n");
				return 1;
			}
		}
	}

	/*Si no se reconoce lo leido, se devuelve un codigo de error*/
	else {
		printf("Error: Caracter no valido\n");
		return 1;
	}

	return 0;
}


int Abrefichero(int sudoku[9][9]) {

	/*Funcion que coge los valores del sudoku desde un fichero que contenga 81 numeros
	*El 0 se indica para que esa posicion del sudoku es a priori desconocida.
	*La funcion devuelve un 0 si todo ha ido correctamente y un 1 si se ha producido un
	*fallo. */

	/*Puntero a estructura FILE que me permite abrir el archivo*/
	FILE *fich;
	int i, j, aux;
	char nombrefich[30];

	printf("Escriba el nombre del fichero\n");
	fflush(stdin);
	scanf(" %s", nombrefich);

	/*Abro el fichero pedido. Si se produce algun error al abrir el fichero, salgo de la
	*funcion devolviendo un 1.*/
	if (!(fich = fopen(nombrefich, "r"))) return 1;

	/*Me aprovecho de que siempre hay 81 posiciones en un sudoku para leer el fichero mediante
	*bucles for y no mediante un while(fscanf())*/
	for (i = 0; i<9; i++) {
		for (j = 0; j<9; j++) {
			fscanf(fich, "%d", &aux);
			if (aux >= 0 && aux <= 9) sudoku[i][j] = aux;
			else return 1;
		}
	}

	/*Cierro el fichero*/
	fclose(fich);
	return 0;
}


int Guardafichero(int sudoku[9][9]) {

	/*Funcion que guarda los valores del sudoku en un fichero. El contenido final del fichero
	*seran 81 numeros en 9 columnas, en aspecto usual de un sudoku.
	*El 0 indica que esa posicion del sudoku es a priori desconocida.
	*La funcion devuelve un 0 si todo ha ido correctamente y un 1 si se ha producido un
	*fallo. */

	FILE *fich;
	int i, j;
	char nombrefichero[30];

	printf("Escriba el nombre del fichero\n");
	fflush(stdin);
	scanf(" %s", nombrefichero);

	/*Abro el fichero pedido. Si se produce algun error al abrir el fichero, salgo de la
	*funcion devolviendo un 1.*/
	if (!(fich = fopen(nombrefichero, "w"))) {
		printf("Error abriendo fichero para escritura\n");
		return 1;
	}

	/*Escribo en el fichero los 81 numeros del sudoku*/
	for (i = 0; i<9; i++) {
		for (j = 0; j<9; j++) {
			fprintf(fich, "%d\t", sudoku[i][j]);
			if (j == 8) fprintf(fich, "\n");
		}
	}

	/*Cierro el fichero*/
	fclose(fich);
	return 0;
}

