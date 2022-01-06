#include "my_solver.h"

extern double (*_f)(double);
extern double (*_fp)(double);

/*********************************************
  Bisection Method -- HOMEWORK
**********************************************/
void program1_3(FILE *fp)
{
	double a0, b0, x0, x1 , temp;
	double x_arr[4];
	int n = 0;

	printf("ssss\n");

	if (fp == NULL)
		return;

	_f = _f3;
	_fp = _fp3;

	for(int i = 0; i < 4; i++)
		scanf_s("%lf", &x_arr[i]);

	printf("i\t\t\txn1\t\t\t|f(xn1)|\n");

	for (int i = 0; i < 4; i++) {

		x0 = x_arr[i];

		while (1) {

			printf("%d\t\t\t%e\t\t%e\n", n, x0, _f(x0));


			x1 = x0 - _f(x0) / _fp(x0);

			n++;

			if (fabs(x1 - x0) < EPSILON || fabs(_f(x1)) < DELTA || n == Nmax)
				break;

			if (n != 0)
				x0 = x1;

		}
	}

	printf("end\n");
}