#include "my_solver.h"

#define SOLNUMS 2
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

void prod3_3(int* n, double* x, double* fvec, int* iflag)
{
	/********************************/
	// 기존 식
	//fvec[0] = ((sin(x[0] * x[1] + M_PI / 6.0) + sqrt(pow(x[0], 2) * pow(x[1], 2) + 1)) / cos(x[0] - x[1])) + 2.8;
	//fvec[1] = ((x[0] * exp(x[0] * x[1] + M_PI / 6.0) - sin(x[0] - x[1])) / sqrt(pow(x[0], 2) * pow(x[1], 2) + 1)) - 1.66;

	// 변형 식
	fvec[0] = sin(x[0] * x[1] + M_PI / 6.0) + sqrt(pow(x[0], 2) * pow(x[1], 2) + 1) + 2.8 * cos(x[0] - x[1]);
	fvec[1] = x[0] * exp(x[0] * x[1] + M_PI / 6.0) - sin(x[0] - x[1]) - 1.66 * sqrt(pow(x[0], 2) * pow(x[1], 2) + 1);
	/********************************/
}

void cal_func(double a, double b) {

	double x[2];
	double arr[2];
	double arr2[2];

	x[0] = a;
	x[1] = b;

	arr[0] = ((sin(x[0] * x[1] + M_PI / 6.0) + sqrt(pow(x[0], 2) * pow(x[1], 2) + 1)) / cos(x[0] - x[1])) + 2.8;
	arr[1] = ((x[0] * exp(x[0] * x[1] + M_PI / 6.0) - sin(x[0] - x[1])) / sqrt(pow(x[0], 2) * pow(x[1], 2) + 1)) - 1.66;

	arr2[0] = sin(x[0] * x[1] + M_PI / 6.0) + sqrt(pow(x[0], 2) * pow(x[1], 2) + 1) + 2.8 * cos(x[0] - x[1]);
	arr2[1] = x[0] * exp(x[0] * x[1] + M_PI / 6.0) - sin(x[0] - x[1]) - 1.66 * sqrt(pow(x[0], 2) * pow(x[1], 2) + 1);

	printf("<<<   기존 식   >>>\n");
	printf("%lf\t\t%lf\n", arr[0], arr[1]);

	printf("<<<   변형을 한 식   >>>\n");
	printf("%lf\t\t%lf\n", arr2[0], arr2[1]);
}

void program3_3(void)
{
	int n = SOLNUMS;
	double x[SOLNUMS] = { 20.0, 0.0 };	//need to initilize x0

	double fvec[SOLNUMS];
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (3 * SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (3 * SOLNUMS + 13)) / 2;

	FILE* fp_w = fopen("roots_found_3-3.txt", "w");
	if (fp_w == NULL) {
		printf("%s file open error...\n", "roots_found_3-3.txt");
		return;
	}

	/********************************/

	hybrd1_(prod3_3, &n, x, fvec, &tol, &info, wa, &lwa);

	printf("\tRoot\t\tFunc\n");
	fprintf(fp_w, "\tRoot\t\tFunc\n");

	for (int i = 0; i < 2; i++) {
		printf("%15lf	%15f\n", x[i], fvec[i]);
		fprintf(fp_w, "%15lf	%15f\n", x[i], fvec[i]);
	}

	printf("\n\n");
	fprintf(fp_w, "\n");
	
	cal_func(x[0], x[1]);

	/********************************/

	fclose(fp_w);
}