#include "my_solver.h"
#include <stdlib.h>

void program2_1()
{
	FILE* fp_r, *fp_w;
	__int64 start, freq, end;
	float resultTime = 0;

	fp_r = fopen("sampling_table.txt", "r");
	if (fp_r == NULL) {
		printf("input file not found....\n");
		exit(0);
	}

	fp_w = fopen("pdf_table.txt", "w");

	/***************************************************/

	double sample, x;
	fscanf(fp_r, "%lf  %lf", &sample, &x);

	double* arr_x = (double*)malloc(sizeof(double) * sample);
	double* arr_y = (double*)malloc(sizeof(double) * sample);

	for (int i = 0; i < sample; i++) {
		fscanf(fp_r, "%lf %lf", &arr_x[i], &arr_y[i]);

	}

	//x정규화 [0, 1]
	for (int i = 0; i < sample; i++) {
		arr_x[i] = i * (1.0 / (sample - 1));
	}

	//y정규화
	double sum_height = 0;

	for (int i = 0; i < sample; i++) {
		sum_height += arr_y[i];
	}

	sum_height = sum_height * 2.0 - (arr_y[0] + arr_y[(int)sample - 1]);

	for (int i = 0; i < sample; i++) {
		arr_y[i] = arr_y[i] / (sum_height * (1.0 / (sample - 1)) * 0.5);
	}

	/*
	printf("%lf %lf\n", sample, x);

	for (int i = 0; i < sample; i++) {
		printf("%lf %lf\n", arr_x[i], arr_y[i]);
	}*/

	double result[4];

	for (int i = 0; i < 4; i++) {
		double cal = 0.0;

		for (int j = 0; j < sample; j++) {
			if (i * 0.25 <= arr_x[j] && arr_x[j] <= (i + 1) * 0.25)
				cal += arr_y[j];
			if (i * 0.25 < arr_x[j] && arr_x[j] < (i + 1) * 0.25)
				cal += arr_y[j];
		}

		cal = cal * (1.0 / (sample - 1)) * 0.5;

		result[i] = cal;
	}

	double sum_of_res = 0.0;

	for (int i = 0; i < 4; i++)
		sum_of_res += result[i];

	printf("*** Integrating the pdf from 0.0 to 1.0 = %lf\n", sum_of_res);

	printf("*** Integrating the pdf from 0.0 to 0.25 = %lf\n", result[0]);
	printf("*** Integrating the pdf from 0.25 to 0.5 = %lf\n", result[1]);
	printf("*** Integrating the pdf from 0.5to 0.75 = %lf\n", result[2]);
	printf("*** Integrating the pdf from 0.75 to 1.0 = %lf\n", result[3]);

	fprintf(fp_w, "%d %lf\n", (int)sample, (1.0 / (sample - 1)));

	for (int i = 0; i < sample; i++) {
		fprintf(fp_w, "%lf %lf\n", arr_x[i], arr_y[i]);
	}

	/***************************************************/

	free(arr_x);
	free(arr_y);

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);
}
