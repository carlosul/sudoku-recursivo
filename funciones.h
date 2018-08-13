#pragma once
/*FUNCIONES.H*/

#ifndef SUDOKU_FUNCIONES_H_
#define SUDOKU_FUNCIONES_H_

#include <stdio.h>
#include <stdlib.h>

void Representa(int sudoku[9][9]);

int Escribe(int sudoku[9][9]);

int Resuelve(int sudoku[9][9]);

int Inicializa(int sudoku[9][9]);

int CandidatoExclusivo(int sudoku[9][9], int candidatos[9][9][9], int* aux, int* posible);

int Suponer(int sudoku[9][9], int candidatos[9][9][9], int aux, int posible);

int Fallo(int candidatos[9][9][9], int sudoku[9][9]);

#endif