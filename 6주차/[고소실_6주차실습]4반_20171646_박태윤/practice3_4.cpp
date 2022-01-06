#include "my_solver.h"

#define SOLNUMS 3
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

void fcn3_4(int* n, double* x, double* fvec, double* fjac, int* ldfjac, int* iflag)
{
	// origin function F(x)
	if (*iflag == 1) {
		/********************************/
		fvec[0] = x[0] + x[1] + x[2] - 3.0;
		fvec[1] = pow(x[0], 2) + pow(x[1], 2) + pow(x[2], 2) - 5.0;
		fvec[2] = exp(x[0]) + x[0] * x[1] - x[0] * x[2] - 1.0;
		/********************************/
	}
	// Jacobi matrix J(x)
	else if (*iflag == 2) {
		/********************************/
		fjac[0] = 1.0;							fjac[3] = 1.0;					fjac[6] = 1.0;
		fjac[1] = 2.0 * x[0];					fjac[4] = 2.0 * x[1];			fjac[7] = 2.0 * x[2];
		fjac[2] = exp(x[0]) + x[1] - x[2];		fjac[5] = x[0];					fjac[8] = -x[0];
		/********************************/
	}
}

void practice3_4(void) {
	int n = SOLNUMS;
	double x[SOLNUMS] = { 0.1, 1.2, 2.5 };	//need to initilize x0
	double fvec[SOLNUMS], fjac[MATCOLS * MATROWS];
	int ldfjac = SOLNUMS;
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (SOLNUMS + 13)) / 2;

	FILE* fp_w = fopen("roots_3-4.txt", "w");
	if (fp_w == NULL) {
		printf("%s file open error...\n", "roots_3-4.txt");
		return;
	}

	/********************************/

	hybrj1_(fcn3_4, &n, x, fvec, fjac, &ldfjac, &tol, &info, wa, &lwa);

	printf("<<<   First   >>>\n\n");

	printf("\tRoot\t\tFunc\n");
	fprintf(fp_w, "\tRoot\t\tFunc\n");

	for (int i = 0; i < 3; i++) {
		printf("%15lf	%15f\n", x[i], fvec[i]);
		fprintf(fp_w, "%15lf	%15f\n", x[i], fvec[i]);
	}

	printf("\n\n");
	fprintf(fp_w, "\n\n");

	/////////////////////////////
	x[0] = 1.0; x[1] = 0.0; x[2] = 1.0;
	/// ////////////////////////


	hybrj1_(fcn3_4, &n, x, fvec, fjac, &ldfjac, &tol, &info, wa, &lwa);

	printf("<<<   Second   >>>\n\n");

	printf("\tRoot\t\tFunc\n");
	fprintf(fp_w, "\tRoot\t\tFunc\n");

	for (int i = 0; i < 3; i++) {
		printf("%15lf	%15f\n", x[i], fvec[i]);
		fprintf(fp_w, "%15lf	%15lf\n", x[i], fvec[i]);
	}

	printf("\n\n");
	fprintf(fp_w, "\n\n");

	/********************************/

	fclose(fp_w);
}
