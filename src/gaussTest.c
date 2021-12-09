#include <stdio.h>

#include "gaussTest.h"

static int testCounter = 0;

void assert(int expr)
{
	if (!expr)
	{
		fprintf(stderr, "Test %d failed\n", testCounter);
	}
	else
	{
		fprintf(stderr, "Test %d passed\n", testCounter);
	}
	++testCounter;
}

int areEqual(Matrix* a, Matrix* b)
{
	if (a->c != b->c || a->r != b->r)
	{
		return 0;
	}
	int i;
	for (i = 0; i < a->r; i++)
	{
		int j;
		for (j = 0; j < a->c; j++)
		{
			if (a->data[i][j] != b->data[i][j])
			{
				return 0;
			}
		}
	}
	return 1;
}

Matrix* readFromFileEx(FILE* file)
{
	int r, c;
	int ir, ic;
	Matrix* mat = NULL;

	if (file != NULL) {
		fscanf(file, "%d %d", &r, &c);
		mat = createMatrix(r, c);
		if (mat != NULL) {
			for (ir = 0; ir < r; ir++)
				for (ic = 0; ic < c; ic++)
					fscanf(file, "%lf", &(mat->data[ir][ic]));
		}
		else {
			fprintf(stderr, "Wyst¹pi³ problem podczas tworzenia macierzy o rozmiarach %d x %d dla danych z pliku: %s\n", r, c, file);
		}

	}
	else {
		fprintf(stderr, "Nie mogê otworzyæ pliku o nazwie: %s\n", file);
	}

	return mat;
}
