#include "my_solver.h"

#define SOLNUMS 2
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

void fcn3_7(int* n, double* x, double* fvec, int* iflag)
{
	/********************************/
	fvec[0] = 2.0 * pow(x[0], 3) - 12.0 * x[0] - x[1] - 1.0;
	fvec[1] = 3.0 * pow(x[1], 2) - 6.0 * x[1] - x[0] - 3.0;
	/********************************/
}

void practice3_7(void)
{
	int n = SOLNUMS;
	double x[SOLNUMS] = { -4.0, 5.0 };	//need to initilize x0

	double rootComp[100][SOLNUMS];
	int compIdx = 0;

	double fvec[SOLNUMS];
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (3 * SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (3 * SOLNUMS + 13)) / 2;

	FILE* fp_w = fopen("roots_3-7.txt", "w");
	if (fp_w == NULL) {
		printf("%s file open error...\n", "roots_3-7.txt");
		return;
	}

	/********************************/
	for (float i = -4; i <= 4; i += 0.5)
	{
		for (float j = -5; j <= 5; j += 0.5)
		{
			x[0] = i;
			x[1] = j;
			hybrd1_(fcn3_7, &n, x, fvec, &tol, &info, wa, &lwa);

			if (thereIsRoot(x, rootComp, compIdx) == true)
				continue;

			rootComp[compIdx][0] = x[0]; rootComp[compIdx][1] = x[1];
			compIdx++;

			printf("\tRoot\t\tFunc\n");
			fprintf(fp_w, "\tRoot\t\tFunc\n");

			for (int i = 0; i < 2; i++) {
				printf("%15lf	%15f\n", x[i], fvec[i]);
				fprintf(fp_w, "%15lf	%15f\n", x[i], fvec[i]);
			}

			printf("\n\n");
			fprintf(fp_w, "\n");
		}
	}

	/********************************/

	fclose(fp_w);
}