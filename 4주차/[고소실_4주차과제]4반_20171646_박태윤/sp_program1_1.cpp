#include "my_solver.h"

extern float (*_sp_f)(float);
extern float (*_sp_fp)(float);

/*********************************************
  Newton-Rapson Method
**********************************************/
void sp_program1_1(FILE* fp) {
	float x0 = 0.0, x1 = 0.0;
	int n = 0;

	if (fp == NULL)
		return;

	printf("Single Newton-Raphson Method : ");
	scanf_s("%f", &x0);

	fprintf(fp, "<<<  Single Newton-Raphson Method  >>>\n");
	fprintf(fp, "i\t\t\txn1\t\t\t|f(xn1)|\n");

	while (1) {

		fprintf(fp, "%d\t\t\t%.10e\t\t%.10e\n", n, x0, fabs(_sp_f(x0)));


		x1 = x0 - _sp_f(x0) / _sp_fp(x0);

		n++;

		if (fabs(x1 - x0) < EPSILON || fabs(_sp_f(x1)) < DELTA || n == Nmax) {
			fprintf(fp, "%d\t\t\t%.10e\t\t%.10e\n", n, x1, fabs(_sp_f(x1)));
			break;
		}

		if (n != 0)
			x0 = x1;

	}

	printf("Single root : %.10e\n", x1);

}
