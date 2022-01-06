#include "my_solver.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>

double cal_remain(double mid, int idx, double arr_x[], double arr_y[], double cdf[]) {

	return (arr_y[idx] + (arr_y[idx + 1] - arr_y[idx]) / (arr_x[idx + 1] - arr_x[idx]) * (mid - arr_x[idx]) * 0.5) * (mid - arr_x[idx]);
}

void program2_2()
{
	FILE* fp_r, *fp_w;

	fp_r = fopen("pdf_table.txt", "r");
	fp_w = fopen("random_event_table.txt", "w");

	/***************************************************/

	double num, x;

	fscanf(fp_r, "%lf %lf", &num, &x);

	double* arr_x = (double*)malloc(sizeof(double) * num);
	double* arr_y = (double*)malloc(sizeof(double) * num);

	for (int i = 0; i < num; i++)
		fscanf(fp_r, "%lf %lf", &arr_x[i], &arr_y[i]);

	double* cdf = (double*)malloc(sizeof(double) * num);
	double sum = 0.0;

	for (int i = 0; i < num; i++)
		cdf[i] = 0.0;

	cdf[0] = arr_y[0] * x * 0.5;

	for (int i = 1; i < num; i++) {
		cdf[i] = x * (arr_y[i - 1] + arr_y[i]) * 0.5 + cdf[i - 1];

	}

	//for (int i = 0; i < num; i++)
		//printf("%lf\n", cdf[i]);

	int rd_num;

	printf("input random number : ");
	scanf("%d", &rd_num);

	fprintf(fp_w, "%d\n", rd_num);

	unsigned int iseed = (unsigned int)time(NULL);
	srand(iseed);

	for (int i = 0; i < rd_num; i++) {
		double U = (rand() % 10000) / 10000.0;
		//printf("%lf\n", U);
		double start = arr_x[0];
		double end = arr_x[(int)num - 1];
		double last = 0.0;
		int count = 0;

		while (1) {
			int idx = 0;
			double mid = (start + end) * 0.5;

			for (int j = 0; j < num; j++) {
				if (mid >= arr_x[j] && mid <= arr_x[j + 1]) {
					idx = j;
					break;
				}
			}

			double res = cdf[idx] + cal_remain(mid, idx, arr_x, arr_y, cdf);

			if (res - U < 0) {
				start = mid;
			}
			else {
				end = mid;
			}

			if (fabs(res - U) < DELTA || count >= Nmax || fabs(mid - last) < EPSILON) {
				fprintf(fp_w, "%.15lf\n", mid);
				break;
			}


			last = mid;

			count++;

		}
	}

	free(arr_x);
	free(arr_y);
	free(cdf);

	/***************************************************/

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);
}
