#include "my_solver.h"

#define SOLNUMS 4
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001


void proj3_2(int* n, double* x, double* fvec, double* fjac, int* ldfjac, int* iflag)
{
	// origin function F(x)
	if (*iflag == 1) {
		/********************************/
		fvec[0] = x[0] + 10.0 * x[1] + 9.0;
		fvec[1] = sqrt(5.0) * (x[2] - x[3]) - 2.0 * sqrt(5.0);
		fvec[2] = pow(x[1] - 2.0 * x[2], 2) - 9.0;
		fvec[3] = sqrt(10.0) * pow(x[0] - x[3], 2) - 2.0 * sqrt(10.0);
		/********************************/
	}
	// Jacobi matrix J(x)
	else if (*iflag == 2) {
		/********************************/
		fjac[0] = 1.0;		fjac[4] = 10.0;		fjac[8] = 0.0;		fjac[12] = 0.0;
		fjac[1] = 0.0;		fjac[5] = 0.0;		fjac[9] = sqrt(5.0);		fjac[13] = -1.0 * sqrt(5.0);
		fjac[2] = 0.0;		fjac[6] = 2.0 * x[1];		fjac[10] = -4.0 * x[2];		fjac[14] = 0.0;
		fjac[3] = 2.0 * sqrt(10.0) * x[0];		fjac[7] = 0.0;		fjac[11] = 0.0;		fjac[15] = -1.0 * sqrt(10.0) * x[3];
		/********************************/
	}
}

void program3_2(void) {
	int n = SOLNUMS;
	double x[SOLNUMS] = { 0.9, -0.9, 1.25, -1.25 };	//need to initilize x0
	double fvec[SOLNUMS], fjac[MATCOLS * MATROWS];
	int ldfjac = SOLNUMS;
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (SOLNUMS + 13)) / 2;

	/********************************/

	printf("<<<   HYBRJ1   >>>\n\n");

	FILE* fp_w = fopen("roots_found_3-2.txt", "w");

	hybrj1_(proj3_2, &n, x, fvec, fjac, &ldfjac, &tol, &info, wa, &lwa);

	printf("\tRoot\t\tFunc\n");
	fprintf(fp_w, "\tRoot\t\tFunc\n");

	for (int i = 0; i < 4; i++) {
		printf("%15lf	%15f\n", x[i], fvec[i]);
		fprintf(fp_w, "%15lf	%15f\n", x[i], fvec[i]);
	}

	printf("\n\n");
	fprintf(fp_w, "\n\n");
	fclose(fp_w);
}


