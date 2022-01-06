#include "my_solver.h"

#define SOLNUMS 2
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

void fcn3_6(int* n, double* x, double* fvec, double* fjac, int* ldfjac, int* iflag) {
	// origin function F(x)
	if (*iflag == 1) {
		/********************************/
		fvec[0] = 3 * pow(x[0], 2) - 2 * pow(x[1], 2) - 1;
		fvec[1] = pow(x[0], 2) - 2 * x[0] + pow(x[1], 2) + 2 * x[1] - 8;
		/********************************/
	}
	// Jacobi matrix J(x)
	else if (*iflag == 2) {
		/********************************/
		fjac[0] = 6 * x[0];				fjac[2] = -4 * x[1];
		fjac[1] = 2 * x[0] - 2;			fjac[3] = 2 * x[1] + 2;
		/********************************/
	}
}

bool thereIsRoot(double* x, double rootComp[][2], int idx) {
	for (int i = 0; i < idx; i++) {
		if (int(x[0]*1000000) == int(rootComp[i][0] * 1000000) || int(x[1] * 1000000) == int(rootComp[i][1] * 1000000))
			return true;
	}

	return false;
}

void practice3_6(void)
{
	int n = SOLNUMS;
	double x[SOLNUMS] = { -4.0, 5.0 };	//need to initilize x0

	double rootComp[100][SOLNUMS];
	int compIdx = 0;

	double fvec[SOLNUMS], fjac[MATCOLS * MATROWS];
	int ldfjac = SOLNUMS;
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (SOLNUMS + 13)) / 2;

	FILE* fp_w = fopen("roots_3-6.txt", "w");
	if (fp_w == NULL) {
		printf("%s file open error...\n", "roots_3-6.txt");
		return;
	}

	/********************************/
	for (float i = -4; i <= 4; i += 0.5)
	{
		for (float j = -5; j <= 5; j += 0.5)
		{
			x[0] = i;
			x[1] = j;
			hybrj1_(fcn3_6, &n, x, fvec, fjac, &ldfjac, &tol, &info, wa, &lwa);

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