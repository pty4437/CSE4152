#include "my_solver.h"

extern double (*_f)(double);
extern double (*_fp)(double);

/*********************************************
  Bisection Method -- HOMEWORK
**********************************************/
void program1_3(FILE *fp)
{
	double x0, x1, temp;
	int n = 0;
	int flag;

	if (fp == NULL)
		return;

	printf("Bisection Method : ");
	scanf_s("%lf %lf", &x0, &x1);

	//증가함수
	if (_f(x0) < _f(x1)) {
		flag = 1;
	}
	//감소함수
	else {
		flag = -1;
	}

	fprintf(fp, "<<<  Bisection Method  >>>\n");
	fprintf(fp, "i\t\t\txn1\t\t\t|f(xn1)|\n");

	fprintf(fp, "%d\t\t\t%.10e\t\t%.10e\n", n, x0, fabs(_f(x0)));

	while (1) {
		n++;

		//fprintf(fp, "%d\t\t\t%.10e\t\t%.10e\n", n, x1, fabs(_f(x1)));

		if (fabs(x1 - x0) < EPSILON || fabs(_f(x1)) < DELTA || n == Nmax)
			break;

		temp = (x0 + x1) / 2.0;

		//작은 경우
		if (_f(temp) < 0) {
			//증가함수
			if (flag == 1) {
				x0 = temp;
			}
			//감소함수
			else {
				x1 = temp;
			}
		}

		//큰 경우
		else {
			//증가함수
			if (flag == 1) {
				x1 = temp;

			}
			//감소함수
			else {
				x0 = temp;
			}

		}

		fprintf(fp, "%d\t\t\t%.10e\t\t%.10e\n", n, temp, fabs(_f(temp)));

		/*
		if (n != 0) {
			x0 = x1;
			x1 = temp;
		}*/
	}

	printf("root : %.10e\n", x1);
}