#include <stdlib.h>
#include <stdio.h>

#include "gauss.h"
#include "backsubst.h"
#include "mat_io.h"
#include "gaussTest.h"


#define RUN_TESTS

#ifdef RUN_TESTS

#define RESETUP	freeMatrix(A);\
					freeMatrix(B);\
					freeMatrix(resultA);\
					A = readFromFileEx(fileA);\
					B = readFromFileEx(fileB);\
					resultA = readFromFileEx(fileResult)

void runTests(void)
{
	FILE* fileA = fopen("testA", "r");
	FILE* fileB = fopen("testB", "r");
	FILE* fileResult = fopen("result", "r");

	//test for matrix 1x1
	Matrix* A = readFromFileEx(fileA);
	Matrix* B = readFromFileEx(fileB);
	Matrix* resultA = readFromFileEx(fileResult);

	//matrix 1x1
	eliminate(A, B);
	assert(areEqual(A, resultA));

	RESETUP;
	// 2x1 matrix
	eliminate(A, B);
	assert(areEqual(A, resultA));
	
	RESETUP;
	// 1x2 matrix
	eliminate(A, B);
	assert(areEqual(A, resultA));

	RESETUP;
	// 2x2 singular matrix, but too small to trigger 0 division
	eliminate(A, B);
	assert(areEqual(A, resultA));

	RESETUP;
	// 2x2 matrix
	eliminate(A, B);
	assert(areEqual(A, resultA));

	RESETUP;
	// 2x2 matrix only with 0
	assert(eliminate(A, B) == 1);

	RESETUP;
	// 3x3 matrix only with 0s
	assert(eliminate(A, B) == 1);

	RESETUP;
	// 3x3 random matrix
	eliminate(A, B);
	assert(areEqual(A, resultA));

	RESETUP;
	// 2x2 matrix unresolvable without pivot
	
	assert(eliminate(A, B) == 0);

	freeMatrix(A); 
	freeMatrix(B); 
	freeMatrix(resultA);

	fclose(fileA);
	fclose(fileB);
	fclose(fileResult);
}
#endif

int main(int argc, char ** argv) {
#ifdef RUN_TESTS
	runTests();
#else
	int res;
	Matrix* A = readFromFile(argv[1]);
	Matrix* b = readFromFile(argv[2]);
	Matrix* x;

	if (A == NULL) return -1;
	if (b == NULL) return -2;
	printToScreen(A);
	printToScreen(b);

	res = eliminate(A, b);
	x = createMatrix(b->r, 1);
	if (x != NULL) {
		res = backsubst(x, A, b);

		printToScreen(x);
		freeMatrix(x);
	}
	else {
		fprintf(stderr, "Błąd! Nie mogłem utworzyć wektora wynikowego x.\n");
	}

	freeMatrix(A);
	freeMatrix(b);
#endif

	

	return 0;
}
