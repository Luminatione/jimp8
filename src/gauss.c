#include "gauss.h"
 #include <math.h>

 /**
  * Zwraca 0 - elimnacja zakonczona sukcesem
  * Zwraca 1 - macierz osobliwa - dzielenie przez 0
  */

 void swap(double **x, double **y)
 {
 	double *temp = *x;
 	*x = *y; 
 	*y = temp;
 }

 void pivot(Matrix *mat, Matrix *b, int index)
 {
 	int i;
 	double max = mat->data[index][index];
 	int highest = index; //index of an element with highest fabs

 	for(i = index+1; i < mat->r; i++)
 	{
 		if(fabs(mat->data[i][index]) > max)
 		{
 			highest = i;
 			max = fabs(mat->data[i][index]);
 		}
 	}

 	swap(&mat->data[highest], &mat->data[index]);
 	swap(&b->data[highest], &b->data[index]);
 }

 int eliminate(Matrix *mat, Matrix *b){
 	int i;
 	for(i = 0; i < mat->c && i < mat->r; ++i)
 	{
 		int j;
 		pivot(mat, b, i);
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