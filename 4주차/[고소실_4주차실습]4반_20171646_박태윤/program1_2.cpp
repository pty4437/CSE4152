#include "my_solver.h"

extern double (*_f)(double);
extern double (*_fp)(double);

/*********************************************
  Secant Method
**********************************************/
void program1_2(FILE* fp) {
	double x0, x1, temp;
	int n = 0;

	if (fp == NULL)
		return;

	printf("Secant Method : ");
	scanf_s("%lf %lf", &x0, &x1);

	fprintf(fp, "<<<  Secant Method  >>>\n");
	fprintf(fp, "i\t\t\txn1\t\t\t|f(xn1)|\n");

	fprintf(fp, "%d\t\t\t%.10e\t\t%.10e\n", n, x0, fabs(_f(x0)));

	while (1) {
		n++;

		fprintf(fp, "%d\t\t\t%.10e\t\t%.10e\n", n, x1, fabs(_f(x1)));

		if (fabs(x1 - x0) < EPSILON || fabs(_f(x1)) < DELTA || n == Nmax)
			break;
	
		temp = x1 - _f(x1) * ((x1 - x0) / (_f(x1) - _f(x0)));

		if (n != 0) {
			x0 = x1;
			x1 = temp;
		}
	}

	printf("root : %.10e\n", x1);
}
