#include "my_solver.h"

#define SOLNUMS 4
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

double C, b;
double arr[4][5];

void proj3_1(int* n, double* x, double* fvec, double* fjac, int* ldfjac, int* iflag)
{
	// origin function F(x)
	if (*iflag == 1) {
		/********************************/
		fvec[0] = pow(x[0] - arr[0][0], 2) + pow(x[1] - arr[0][1],2) + pow(x[2] - arr[0][2], 2) - pow(C * (arr[0][4] + x[3] - arr[0][3]), 2);
		fvec[1] = pow(x[0] - arr[1][0], 2) + pow(x[1] - arr[1][1], 2) + pow(x[2] - arr[1][2], 2) - pow(C * (arr[1][4] + x[3] - arr[1][3]), 2);
		fvec[2] = pow(x[0] - arr[2][0], 2) + pow(x[1] - arr[2][1], 2) + pow(x[2] - arr[2][2], 2) - pow(C * (arr[2][4] + x[3] - arr[2][3]), 2);
		fvec[3] = pow(x[0] - arr[3][0], 2) + pow(x[1] - arr[3][1], 2) + pow(x[2] - arr[3][2], 2) - pow(C * (arr[3][4] + x[3] - arr[3][3]), 2);

		/********************************/
	}
	// Jacobi matrix J(x)
	else if (*iflag == 2) {
		/********************************/
		fjac[0] = 2.0 * (x[0] - arr[0][0]);		fjac[4] = 2.0 * (x[1] - arr[0][1]);		fjac[8] = 2.0 * (x[2] - arr[0][2]);		fjac[12] = -2.0 * pow(C, 2) * (arr[0][4] + x[3] - arr[0][3]);
		fjac[1] = 2.0 * (x[0] - arr[1][0]);		fjac[5] = 2.0 * (x[1] - arr[1][1]);		fjac[9] = 2.0 * (x[2] - arr[1][2]);		fjac[13] = -2.0 * pow(C, 2) * (arr[1][4] + x[3] - arr[1][3]);
		fjac[2] = 2.0 * (x[0] - arr[2][0]);		fjac[6] = 2.0 * (x[1] - arr[2][1]);		fjac[10] = 2.0 * (x[2] - arr[2][2]);		fjac[14] = -2.0 * pow(C, 2) * (arr[2][4] + x[3] - arr[2][3]);
		fjac[3] = 2.0 * (x[0] - arr[3][0]);		fjac[7] = 2.0 * (x[1] - arr[3][1]);		fjac[11] = 2.0 * (x[2] - arr[3][2]);		fjac[15] = -2.0 * pow(C, 2) * (arr[3][4] + x[3] - arr[3][3]);
		/********************************/
	}
}

void prod3_1(int* n, double* x, double* fvec, int* iflag)
{
	/********************************/
	fvec[0] = pow(x[0] - arr[0][0], 2) + pow(x[1] - arr[0][1], 2) + pow(x[2] - arr[0][2], 2) - pow(C * (arr[0][4] + x[3] - arr[0][3]), 2);
	fvec[1] = pow(x[0] - arr[1][0], 2) + pow(x[1] - arr[1][1], 2) + pow(x[2] - arr[1][2], 2) - pow(C * (arr[1][4] + x[3] - arr[1][3]), 2);
	fvec[2] = pow(x[0] - arr[2][0], 2) + pow(x[1] - arr[2][1], 2) + pow(x[2] - arr[2][2], 2) - pow(C * (arr[2][4] + x[3] - arr[2][3]), 2);
	fvec[3] = pow(x[0] - arr[3][0], 2) + pow(x[1] - arr[3][1], 2) + pow(x[2] - arr[3][2], 2) - pow(C * (arr[3][4] + x[3] - arr[3][3]), 2);
	/********************************/
}

void program3_1(void) {
	int n = SOLNUMS;
	double x[SOLNUMS] = { 0.0, 0.0, 0.0, 0.0 };	//need to initilize x0
	double backup_x[SOLNUMS];
	double fvec[SOLNUMS], fjac[MATCOLS * MATROWS];
	int ldfjac = SOLNUMS;
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (SOLNUMS + 13)) / 2;


	char readfile[500];
	char writefile[500];

	/********************************/

	printf("input: ");
	scanf("%lf %lf %lf", &x[0], &x[1], &x[2]);

	printf("<<<   HYBRJ1   >>>\n\n");
	for (int i = 0; i < 3; i++)
		backup_x[i] = x[i];

	for (int i = 0; i < 3; i++) {
		int n = SOLNUMS;
		//double x[SOLNUMS] = { 0.0, 0.0, 0.0, 0.0 };	//need to initilize x0
		double fvec[SOLNUMS], fjac[MATCOLS * MATROWS];
		int ldfjac = SOLNUMS;
		double tol = TOLERANCE;
		int info;
		double wa[(SOLNUMS * (SOLNUMS + 13)) / 2];
		int lwa = (SOLNUMS * (SOLNUMS + 13)) / 2;

		sprintf(readfile, "GPS_signal_%d.txt", i);
		sprintf(writefile, "GPS_position_3-1_%d.txt", i);

		FILE* fp_r = fopen(readfile, "r");
		FILE* fp_w = fopen(writefile, "w");

		fscanf(fp_r, "%lf %lf", &C, &b);


		for (int row = 0; row < 4; row++) {
			for (int col = 0; col < 5; col++) {
				fscanf(fp_r, "%lf", &arr[row][col]);
			}
		}

		x[3] = b;

		hybrj1_(proj3_1, &n, x, fvec, fjac, &ldfjac, &tol, &info, wa, &lwa);

		printf("\tRoot\t\tFunc\n");
		fprintf(fp_w, "\tRoot\t\tFunc\n");

		for (int i = 0; i < 4; i++) {
			printf("%15lf	%15f\n", x[i], fvec[i]);
			fprintf(fp_w, "%15lf	%15f\n", x[i], fvec[i]);
		}

		printf("\n\n");
		fclose(fp_r);
		fprintf(fp_w, "\n\n");
		fclose(fp_w);
	}


	/********************************/

	printf("<<<   HYBRD1   >>>\n\n");

	for (int i = 0; i < 3; i++)
		x[i] = backup_x[i];

	for (int i = 0; i < 3; i++) {
		int n = SOLNUMS;
		//double x[SOLNUMS] = { 0.0, 0.0, 0.0, 0.0 };	//need to initilize x0
		double fvec[SOLNUMS];
		double tol = TOLERANCE;
		int info;
		double wa[(SOLNUMS * (3 * SOLNUMS + 13)) / 2];
		int lwa = (SOLNUMS * (3 * SOLNUMS + 13)) / 2;

		

		sprintf(readfile, "GPS_signal_%d.txt", i);
		sprintf(writefile, "GPS_position_3-2_%d.txt", i);

		FILE* fp_r = fopen(readfile, "r");
		FILE* fp_w = fopen(writefile, "w");

		fscanf(fp_r, "%lf %lf", &C, &b);


		for (int row = 0; row < 4; row++) {
			for (int col = 0; col < 5; col++) {
				fscanf(fp_r, "%lf", &arr[row][col]);
			}
		}

		x[3] = b;

		hybrd1_(prod3_1, &n, x, fvec, &tol, &info, wa, &lwa);

		printf("\tRoot\t\tFunc\n");
		fprintf(fp_w, "\tRoot\t\tFunc\n");

		for (int i = 0; i < 4; i++) {
			printf("%15lf	%15f\n", x[i], fvec[i]);
			fprintf(fp_w, "%15lf	%15f\n", x[i], fvec[i]);
		}

		printf("\n\n");
		fclose(fp_r);
		fprintf(fp_w, "\n\n");
		fclose(fp_w);
	}
	
}
