#include "gauss.h"

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b){
	int i;
	for(i = 0; i < mat->c && i < mat->r; ++i)
	{
		int j;
		for(j = i + 1; j < mat->r; ++j)
		{
			int z;
			if(mat->data[i][i] == 0.0)
			{
				return 1;
			}
			double factor = mat->data[j][i]/mat->data[i][i];
			for(z = 0; z < mat->c; ++z)
			{
				mat->data[j][z] -= factor*mat->data[i][z];
			}
			b->data[j][0] -= factor*b->data[i][0];
		}
	}
	return 0;
}
