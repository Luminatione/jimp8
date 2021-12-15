#include <stdlib.h>
#include <stdio.h>

#include "gauss.h"
#include "backsubst.h"
#include "mat_io.h"
#include "gaussTest.h"

#ifdef RUN_TESTS

#define RESETUP	freeMatrix(A);\
					freeMatrix(B);\
					freeMatrix(resultA);\
					freeMatrix(resultB);\
					A = readFromFileEx(fileA);\
					B = readFromFileEx(fileB);\
					resultA = readFromFileEx(fileResult);\
					resultB = readFromFileEx(fileResult);\
					if(A == NULL || B == NULL || resultA == NULL || resultB == NULL)\
						return
#define STANDARD_ASSERT_TEST eliminate(A, B);\
								assert(areEqual(A, resultA));\
								assert(areEqual(B, resultB))
#define RESETUP_BS	freeMatrix(Abs);\
 					freeMatrix(Bbs);\
					freeMatrix(Xbs);\
					freeMatrix(x);\
					Abs = readFromFileEx(fileAbs);\
					Bbs = readFromFileEx(fileBbs);\
					Xbs = readFromFileEx(fileXbs);\
					x = createMatrix(Bbs->r, 1);\
					if (Abs == NULL || Bbs == NULL || Xbs == NULL)\
						return;

void runEliminationTests(void)
{
	printf("Elimination tests: \n");
	FILE* fileA = fopen("../dane/testA", "r");
	FILE* fileB = fopen("../dane/testB", "r");
	FILE* fileResult = fopen("../dane/result", "r");

	//test for matrix 1x1
	Matrix* A = readFromFileEx(fileA);
	Matrix* B = readFromFileEx(fileB);
	Matrix* resultA = readFromFileEx(fileResult);
	Matrix* resultB = readFromFileEx(fileResult);

	//every test in function is separated into two cases to make identifying bugs easier; first is test of matrix A and second is test of matrix B
	//so if test 0 fails and test 1 passes, matrix B was properly computed, but there was error in matrix A for the same set of unknowns

	//matrix 1x1
	STANDARD_ASSERT_TEST;

	RESETUP;
	// 2x1 matrix
	STANDARD_ASSERT_TEST;

	RESETUP;
	// 1x2 matrix
	STANDARD_ASSERT_TEST;

	RESETUP;
	// 2x2 singular matrix, but too small to trigger 0 division
	STANDARD_ASSERT_TEST;

	RESETUP;
	// 2x2 matrix
	STANDARD_ASSERT_TEST;

	RESETUP;
	// 2x2 matrix only with 0
	assert(eliminate(A, B) == 1);

	RESETUP;
	// 3x3 matrix only with 0s
	assert(eliminate(A, B) == 1);

	RESETUP;
	// 4x4 random matrix
	STANDARD_ASSERT_TEST;

	RESETUP;
	// 2x2 matrix unresolvable without pivot
	STANDARD_ASSERT_TEST;

	RESETUP;
	// 3x3 random matrix
	STANDARD_ASSERT_TEST;

	freeMatrix(A);
	freeMatrix(B);
	freeMatrix(resultA);
	freeMatrix(resultB);

	fclose(fileA);
	fclose(fileB);
	fclose(fileResult);
}
void runBacksubstTests(void)
{
	printf("Backsubst tests: \n");
	FILE* fileAbs = fopen("../dane/testAbs", "r");
	FILE* fileBbs = fopen("../dane/testBbs", "r");
	FILE* fileXbs = fopen("../dane/testXbs", "r");

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

int main(int argc, char** argv) {
#ifdef RUN_TESTS
	runEliminationTests();
	runBacksubstTests();

#else
	Matrix* A = readFromFile(argv[1]);
	Matrix* b = readFromFile(argv[2]);
	Matrix* x;

	if (A == NULL) return -1;
	if (b == NULL) return -2;
	printToScreen(A);
	printToScreen(b);

	if (eliminate(A, b) == 0)
	{
		x = createMatrix(b->r, 1);
		if (x != NULL) {
			backsubst(x, A, b);

			printToScreen(x);
			freeMatrix(x);
		}
		else {
			fprintf(stderr, "Błąd! Nie mogłem utworzyć wektora wynikowego x.\n");
		}
	}
	freeMatrix(A);
	freeMatrix(b);
#endif
	return 0;

}
