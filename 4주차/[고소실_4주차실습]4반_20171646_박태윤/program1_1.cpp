#include "my_solver.h"

extern double (*_f)(double);
extern double (*_fp)(double);

/*********************************************
  Newton-Rapson Method
**********************************************/
void program1_1(FILE* fp) {
	double x0 = 0.0, x1 = 0.0;
	int n = 0;

	if (fp == NULL)
		return;

	printf("Newton-Raphson Method : ");
	scanf_s("%lf", &x0);

	fprintf(fp, "<<<  Newton-Raphson Method  >>>\n");
	fprintf(fp, "i\t\t\txn1\t\t\t|f(xn1)|\n");

	while (1) {

		fprintf(fp, "%d\t\t\t%.10e\t\t%.10e\n", n, x0, fabs(_f(x0)));


		x1 = x0 - _f(x0) / _fp(x0);

		n++;

		if (fabs(x1 - x0) < EPSILON || fabs(_f(x1)) < DELTA || n == Nmax) {
			fprintf(fp, "%d\t\t\t%.10e\t\t%.10e\n", n, x1, fabs(_f(x1)));
			break;
		}

		if (n != 0)
			x0 = x1;

	}

	printf("root : %.10e\n", x1);
}
