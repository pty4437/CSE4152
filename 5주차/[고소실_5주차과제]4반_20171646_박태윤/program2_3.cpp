#include "my_solver.h"
#include <math.h>
#include <time.h>

double inverse_func(double y, double L) {
	return -(log(1 - y) / L);
}

// HOMEWORK
void program2_expon()
{
	int rd_num;
	double lambda;

	printf("input random number : ");
	scanf("%d", &rd_num);

	for (int k = 0; k < 3; k++) {
		printf("input lambda : ");
		scanf("%lf", &lambda);

		double* arr = (double*)malloc(sizeof(double) * rd_num);

		unsigned int iseed = (unsigned int)time(NULL);
		double sum = 0.0;
		srand(iseed);

		for (int i = 0; i < rd_num; i++) {
			double U = (rand() % 10000) / 10000.0;
			//printf("%lf\n", U);

			arr[i] = inverse_func(U, lambda);
			sum += arr[i];
		}

		double avg = sum / (float)rd_num;
		double var = 0.0;

		for (int i = 0; i < rd_num; i++) {
			arr[i] = arr[i] - avg;
		}

		double pyun = 0.0;

		for (int i = 0; i < rd_num; i++) {
			pyun += pow(arr[i], 2);
		}

		var = pyun / (double)rd_num;

		printf("theory : %lf %lf\n", 1.0 / lambda, 1.0 / pow(lambda, 2));

		printf("calculate : %lf %lf\n\n", avg, var);

		free(arr);
	}
}

double cal_remain2(double mid, int idx, double arr_x[], double arr_y[], double cdf[]) {

	return (arr_y[idx] + (arr_y[idx + 1] - arr_y[idx]) / (arr_x[idx + 1] - arr_x[idx]) * (mid - arr_x[idx]) * 0.5) * (mid - arr_x[idx]);
}

void program2_3() {
	FILE* fp_r, * fp_r2;
	FILE* fp_w;

	fp_r = fopen("pdf_table.txt", "r");
	fp_r2 = fopen("random_event_table.txt", "r");
	fp_w = fopen("histogram.txt", "w");

	/***************************************************/

	float x;
	int num;

	fscanf(fp_r, "%d %f", &num, &x);

	double* arr_x = (double*)malloc(sizeof(double) * num);
	double* arr_y = (double*)malloc(sizeof(double) * num);

	int arrange[100];

	for (int i = 0; i < 100; i++)
		arrange[i] = 0;

	for (int i = 0; i < num; i++)
		fscanf(fp_r, "%lf %lf", &arr_x[i], &arr_y[i]);

	double sum = 0.0;
	int num_of_nan = 0;

	fscanf(fp_r2, "%d", &num_of_nan);

	double* ran_event = (double*)malloc(sizeof(double) * num_of_nan);

	for (int i = 0; i < num_of_nan; i++) {
		fscanf(fp_r2, "%lf", &ran_event[i]);

	}


	for (int i = 0; i < num_of_nan; i++) {
			int mok = ran_event[i] * 100;

			arrange[mok]++;
	}

	for (int i = 0; i < 100; i++)
		fprintf(fp_w, "%d\n", arrange[i]);

	free(arr_x);
	free(arr_y);
	free(ran_event);

	/***************************************************/

	if (fp_r != NULL) fclose(fp_r);
	if (fp_r2 != NULL) fclose(fp_r2);
	if (fp_w != NULL) fclose(fp_w);
}

// HOMEWORK
void program2_2_a()
{
	__int64 start, freq, end;
	float resultTime = 0;

	FILE* fp_r, * fp_w;

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

	int rd_num;

	printf("input random number : ");
	scanf("%d", &rd_num);

	fprintf(fp_w, "%d\n", rd_num);

	CHECK_TIME_START;

	unsigned int iseed = (unsigned int)time(NULL);
	srand(iseed);

	for (int i = 0; i < rd_num; i++) {
		double U = (rand() % 10000) / 10000.0;
		double start2 = arr_x[0];
		double end2 = arr_x[(int)num - 1];
		double last = 0.0;
		int count = 0;

		while (1) {
			int idx = 0;
			double mid = (start2 + end2) * 0.5;

			for (int j = 0; j < num; j++) {
				if (mid >= arr_x[j] && mid <= arr_x[j + 1]) {
					idx = j;
					break;
				}
			}

			double res = cdf[idx] + cal_remain2(mid, idx, arr_x, arr_y, cdf);

			if (res - U < 0) {
				start2 = mid;
			}
			else {
				end2 = mid;
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

	CHECK_TIME_END(resultTime);

	printf("The program2_2_a run time is %f(ms)..\n", resultTime * 1000.0);
}

double cal_remain3(double mid, int idx, double arr_x[], double arr_y[], double cdf[], double u) {

	return cdf[idx] + (arr_y[idx] + (arr_y[idx + 1] - arr_y[idx]) / (arr_x[idx + 1] - arr_x[idx]) * (mid - arr_x[idx]) * 0.5) * (mid - arr_x[idx]) - u;
}


void program2_2_b()
{
	__int64 start, freq, end;
	float resultTime = 0;

	FILE* fp_r, * fp_w;

	fp_r = fopen("pdf_table.txt", "r");
	fp_w = fopen("random_event_table.txt", "w");

	/***************************************************/

	//float x;
	//int num;
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


	int rd_num;

	printf("input random number : ");
	scanf("%d", &rd_num);

	fprintf(fp_w, "%d\n", rd_num);

	CHECK_TIME_START;

	unsigned int iseed = (unsigned int)time(NULL);
	srand(iseed);

	for (int i = 0; i < rd_num; i++) {
		double U = (rand() % 10000) / 10000.0;
		double start2 = arr_x[0];
		double end2 = arr_x[(int)num - 1];
		double last = 0.0;
		int count = 0;
		double mid = 0.0;


		//bisection
		
		for(int l = 0; l < 1; l++){
			int idx = 0;
			mid = (start2 + end2) * 0.5;

			for (int j = 0; j < num; j++) {
				if (mid >= arr_x[j] && mid <= arr_x[j + 1]) {
					idx = j;
					break;
				}
			}

			double res = cdf[idx] + cal_remain2(mid, idx, arr_x, arr_y, cdf);

			if (res - U < 0) {
				start2 = mid;
			}
			else {
				end2 = mid;
			}

			last = mid;

		}


		double a = start2;
		double b = end2;
		double cal_arr[Nmax + 5];

		int idx_a = 0;
		int idx_b = 0;


		for (int j = 0; j < num; j++) {
			if (a >= arr_x[j] && a <= arr_x[j + 1]) {
				idx_a = j;
				break;
			}
		}

		for (int j = 0; j < num; j++) {
			if (b >= arr_x[j] && b <= arr_x[j + 1]) {
				idx_b = j;
				break;
			}
		}

		double f_b = cal_remain3(b, idx_b, arr_x, arr_y, cdf, U);
		double f_a = cal_remain3(a, idx_a, arr_x, arr_y, cdf, U);

		cal_arr[0] = f_a;
		cal_arr[1] = f_b;

		//secant
		while(1){
			
			int idx_tmp = 0;

			double tmp = b - cal_arr[count+1] * ((b - a) / (cal_arr[count + 1] - cal_arr[count]));

			for (int j = 0; j < num; j++) {
				if (tmp >= arr_x[j] && tmp <= arr_x[j + 1]) {
					idx_tmp = j;
					break;
				}
			}

			cal_arr[count + 2] = cal_remain3(tmp, idx_tmp, arr_x, arr_y, cdf, U);

			if (fabs(cal_arr[count+2]) < DELTA || count >= Nmax || fabs(tmp - b) < EPSILON) {

				//printf("%.15lf %lf %lf\n", cal_arr[count+2], tmp, U);

				fprintf(fp_w, "%.15lf\n", tmp);
				break;
			}
		



			a = b;
			b = tmp;

			count++;
		}
	}

	free(arr_x);
	free(arr_y);
	free(cdf);

	/***************************************************/

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);

	CHECK_TIME_END(resultTime);

	printf("The program2_2_b run time is %f(ms)..\n", resultTime * 1000.0);
}

void program2_2_c()
{
	__int64 start, freq, end;
	float resultTime = 0;

	FILE* fp_r, * fp_w;

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

	int rd_num;

	printf("input random number : ");
	scanf("%d", &rd_num);

	fprintf(fp_w, "%d\n", rd_num);

	CHECK_TIME_START;

	unsigned int iseed = (unsigned int)time(NULL);
	srand(iseed);

	for (int i = 0; i < rd_num; i++) {
		double U = (rand() % 10000) / 10000.0;
		double start2 = arr_x[0];
		double end2 = arr_x[(int)num - 1];
		double last = 0.0;
		int count = 0;
		double mid = 0.0;
		int idx = num / 2.0;


		//bisection
		
		for (int l = 0; l < 2; l++) {
			idx = 0;
			mid = (start2 + end2) * 0.5;

			for (int j = 0; j < num; j++) {
				if (mid >= arr_x[j] && mid <= arr_x[j + 1]) {
					idx = j;
					break;
				}
			}

			double res = cdf[idx] + cal_remain2(mid, idx, arr_x, arr_y, cdf);

			if (res - U < 0) {
				start2 = mid;
			}
			else {
				end2 = mid;
			}

			last = mid;

		}


		double a = arr_x[idx];
		double cal_arr[Nmax + 5];

		int idx_a = 0;


		for (int j = 0; j < num; j++) {
			if (a >= arr_x[j] && a <= arr_x[j + 1]) {
				idx_a = j;
				break;
			}
		}

		double f_a = cal_remain3(a, idx_a, arr_x, arr_y, cdf, U);

		cal_arr[0] = f_a;

		//newton
		while (1) {
			//int idx_tmp = 0;

			double s = (a - arr_x[idx_a]) / (arr_x[idx_a + 1] - arr_x[idx_a]);
			double tmp = a - cal_arr[count] / ((1 - s) * arr_y[idx_a] + s * arr_y[idx_a + 1]);

			for (int j = 0; j < num; j++) {
				if (tmp >= arr_x[j] && tmp <= arr_x[j + 1]) {
					idx_a = j;
					break;
				}
			}
	
			cal_arr[count + 1] = cal_remain3(tmp, idx_a, arr_x, arr_y, cdf, U);

			if (fabs(cal_arr[count + 1]) < DELTA || count >= Nmax || fabs(tmp - a) < EPSILON) {

				fprintf(fp_w, "%.15lf\n", tmp);
				break;
			}



			a = tmp;
			//idx_a = idx_tmp;

			count++;

		}
	}

	free(arr_x);
	free(arr_y);
	free(cdf);

	/***************************************************/

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);

	CHECK_TIME_END(resultTime);

	printf("The program2_2_c run time is %f(ms)..\n", resultTime * 1000.0);
}