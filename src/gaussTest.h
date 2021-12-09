#ifndef _GAUSSTEST_H_
#define _GAUSSTEST_H_

#include "mat_io.h"

void assert(int expr);
int areEqual(Matrix* a, Matrix* b);
Matrix* readFromFileEx(FILE* file);
#endif


