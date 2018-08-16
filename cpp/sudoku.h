#pragma once

class Sudoku {

public:

	void Representa();

	int Escribe();

	int Resuelve();

	int Inicializa();

	int Posicionfinal();

	int Posicioninicial();

	int Abrefichero();

	int Guardafichero();

	int CandidatoExclusivo(int candidatos[9][9][9], int* aux, int* posible);

	int Suponer(int candidatos[9][9][9], int aux, int posible);

	int Fallo(int candidatos[9][9][9]);

private:

	int sudokuData[9][9] = { { 0 } };

};