#include "gauss.h"
#include <math.h>

void swap(double** a, double** b)
{
	double* c = *a;
	*a = *b;
	*b = c;
}
//diagonalElementIndex - index of element on diagonal below which only 0s should be placed
void setPivotOnFirstRow(Matrix* a, Matrix *b, int diagonalElementIndex)
{
	double max = -(double)(INFINITY - 1);
	int maxIndex = 0;
	int i;
	for (i = diagonalElementIndex; i < a->r; i++)
	{
		if(fabs(a->data[i][diagonalElementIndex]) > max)
		{
			max = fabs(a->data[i][diagonalElementIndex]);
			maxIndex = i;
		}
	}
	swap(&a->data[maxIndex], &a->data[diagonalElementIndex]);
	swap(&b->data[maxIndex], &b->data[diagonalElementIndex]);
}

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b){
	int i;
	for(i = 0; i < mat->c && i < mat->r; ++i)
	{
		int j;
		setPivotOnFirstRow(mat, b, i);
		for(j = i + 1; j < mat->r; ++j)
		{
			if(mat->data[i][i] == 0.0)
			{
				return 1;
			}
			double factor = mat->data[j][i]/mat->data[i][i];
			int z;
			for(z = 0; z < mat->c; ++z)
			{
				mat->data[j][z] -= factor*mat->data[i][z];
			}
			b->data[j][0] -= factor*b->data[i][0];
		}
	}
	return 0;
}
