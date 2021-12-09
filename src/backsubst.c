#include "backsubst.h"
/**
 * Zwraca 0 - wsteczne podstawienie zakonczone sukcesem
 * Zwraca 1 - błąd dzielenia przez 0 (element na diagonali = 0)
 * Zwraca 2 - błąd nieprawidłowych rozmiarów macierzy
 */

int backsubst(Matrix* x, Matrix* mat, Matrix* b) {

	int i, j;
	double roznica, suma_iloczynow;

	suma_iloczynow = 0;
	i = mat->c;
	j = x->r;

	if (i != j) return 2;

	for (i = (x->r) - 1; i >= 0; i--) {

		if (mat->data[i][i] == 0.0) return 1;

		if (i == (x->r) - 1) suma_iloczynow = 0;

		else
		{
			for (j = i + 1; j < x->r; j++) {
				suma_iloczynow += (x->data[j][0]) * (mat->data[i][j]);
			}
		}

		roznica = b->data[i][0] - suma_iloczynow;

		x->data[i][0] = roznica / (mat->data[i][i]);

		suma_iloczynow = 0;
	}

	return 0;
}

