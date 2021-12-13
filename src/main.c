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
					freeMatrix(resultB);\
 					A = readFromFileEx(fileA);\
 					B = readFromFileEx(fileB);\
 					resultA = readFromFileEx(fileResult);\
 					resultB = readFromFileEx(fileResult)

#define RESETUP_BS	freeMatrix(Abs);\
 					freeMatrix(Bbs);\
					freeMatrix(Xbs);\
					freeMatrix(x);\
					Abs = readFromFileEx(fileAbs);\
					Bbs = readFromFileEx(fileBbs);\
					Xbs = readFromFileEx(fileXbs);\
					x = createMatrix(Bbs->r, 1)

void runTests(void)
{
	FILE* fileA = fopen("testA", "r");
	FILE* fileB = fopen("testB", "r");
	FILE* fileResult = fopen("result", "r");

	//test for matrix 1x1
 	Matrix* A = readFromFileEx(fileA);
 	Matrix* B = readFromFileEx(fileB);
 	Matrix* resultA = readFromFileEx(fileResult);
 	Matrix* resultB = readFromFileEx(fileResult);

 	//matrix 1x1
 	eliminate(A, B);
 	assert(areEqual(A, resultA));	//test 0
 	assert(areEqual(B, resultB));	//test 1

 	RESETUP;
 	// 2x1 matrix 
 	eliminate(A, B);
 	assert(areEqual(A, resultA));	//test 2
 	assert(areEqual(B, resultB));	//test 3

 	RESETUP;
 	// 1x2 matrix 
 	eliminate(A, B);
 	assert(areEqual(A, resultA));	//test 4
 	assert(areEqual(B, resultB));	//test 5

 	RESETUP;
 	// 2x2 singular matrix, but too small to trigger 0 division
 	eliminate(A, B);
 	assert(areEqual(A, resultA));	//test 6
 	assert(areEqual(B, resultB));	//test 7

 	RESETUP;
 	// 2x2 matrix 
 	eliminate(A, B);
 	assert(areEqual(A, resultA));	//test 8
 	assert(areEqual(B, resultB));	//test 9

 	RESETUP;
 	// 2x2 matrix only with 0 
 	assert(eliminate(A, B) == 1);	//test 10

 	RESETUP;
 	// 3x3 matrix only with 0s 
 	assert(eliminate(A, B) == 1);	//test 11

 	RESETUP;
 	// 3x3 random matrix 
 	eliminate(A, B);
 	assert(areEqual(A, resultA));	//test 12
 	assert(areEqual(B, resultB));	//test 13

 	RESETUP;
 	// 2x2 matrix unresolvable without pivot 
 	eliminate(A, B);
 	assert(areEqual(A, resultA));	//test 14
 	assert(areEqual(B, resultB));	//test 15

 	freeMatrix(A); 
 	freeMatrix(B); 
	freeMatrix(resultA);

	fclose(fileA);
	fclose(fileB);
	fclose(fileResult);
}

void runTestsBS(void)
{
	FILE* fileAbs = fopen("testAbs", "r");
	FILE* fileBbs = fopen("testBbs", "r");
	FILE* fileXbs = fopen("testXbs", "r");

	Matrix* x;
	Matrix* Abs = readFromFileEx(fileAbs);
	Matrix* Bbs = readFromFileEx(fileBbs);
	Matrix* Xbs = readFromFileEx(fileXbs);

	x = createMatrix(Bbs->r, 1);

	//1x1 matrix A, 1x1 matrix B 
	backsubst(x, Abs, Bbs);
	assert(areEqual(x, Xbs));	//test 16

	RESETUP_BS;
	//2x2 matrix A, 2x1 matrix B 
	backsubst(x, Abs, Bbs);
	assert(areEqual(x, Xbs));	//test 17
	
	RESETUP_BS;
	//3x3 matrix A, 3x1 matrix B 
	backsubst(x, Abs, Bbs);
	assert(areEqual(x, Xbs));	//test 18

	RESETUP_BS;
	//2x2 matrix A, 2x1 matrix B, both only with 0s 
	assert(backsubst(x, Abs, Bbs) == 1);	//test 19

	RESETUP_BS;
	//3x2 matrix A, 3x1 matrix B 
	assert(backsubst(x, Abs, Bbs) == 2);	//test 20

	RESETUP_BS;
	//1x2 matrix A, 1x2 matrix B 
	assert(backsubst(x, Abs, Bbs) == 2);	//test 21

	freeMatrix(Abs); 
	freeMatrix(Bbs); 
	freeMatrix(Xbs);

	fclose(fileAbs);
	fclose(fileBbs);
	fclose(fileXbs);
}
#endif

int main(int argc, char ** argv)
{
#ifdef RUN_TESTS
	runTests();
	runTestsBS();

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