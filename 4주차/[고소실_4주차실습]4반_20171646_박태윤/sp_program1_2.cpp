#include "my_solver.h"

extern float (*_sp_f)(float);
extern float (*_sp_fp)(float);

/*********************************************
  Secant Method
**********************************************/
void sp_program1_2(FILE* fp) {
	float x0, x1, temp;
	int n = 0;

	if (fp == NULL)
		return;

	printf("Single Secant Method : ");
	scanf_s("%f %f", &x0, &x1);

	fprintf(fp, "<<<  Single Secant Method  >>>\n");
	fprintf(fp, "i\t\t\txn1\t\t\t|f(xn1)|\n");

	fprintf(fp, "%d\t\t\t%.10e\t\t%.10e\n", n, x0, fabs(_sp_f(x0)));

	while (1) {
		n++;

		fprintf(fp, "%d\t\t\t%.10e\t\t%.10e\n", n, x1, fabs(_sp_f(x1)));

		if (fabs(x1 - x0) < EPSILON || fabs(_sp_f(x1)) < DELTA || n == Nmax)
			break;

		temp = x1 - _sp_f(x1) * ((x1 - x0) / (_sp_f(x1) - _sp_f(x0)));

		if (n != 0) {
			x0 = x1;
			x1 = temp;
		}
	}

	printf("Single root : %.10e\n", x1);
}
