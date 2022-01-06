#include "my_solver.h"

void practice3_2() {
	char readfile[256];
	char writefile[256];

	int NCOEF, DEGREE;

	double* poly;
	double* zeror, * zeroi;
	double* tmp;
	double* real_tmp;
	double* imag_tmp;
	long int fail;

	/// <summary>
	double real = 0.0;
	double imaginary = 0.0;
	/// </summary>

	for (int t = 1; t <= 6; t++) {

		sprintf(readfile, "polynomial_3-2_%d.txt", t);
		sprintf(writefile, "roots_3-2_%d.txt", t);

		FILE* fp_r = fopen(readfile, "r");
		if (fp_r == NULL) {
			printf("%s file open error...\n", readfile);
			return;
		}

		FILE* fp_w = fopen(writefile, "w");
		if (fp_w == NULL) {
			printf("%s file open error...\n", writefile);
			return;
		}

		fscanf(fp_r, "%d", &DEGREE);
		NCOEF = DEGREE + 1;

		poly = (double*)malloc(sizeof(double) * NCOEF);
		zeror = (double*)malloc(sizeof(double) * DEGREE);
		zeroi = (double*)malloc(sizeof(double) * DEGREE);
		real_tmp = (double*)malloc(sizeof(double) * DEGREE);
		imag_tmp = (double*)malloc(sizeof(double) * DEGREE);
		tmp = (double*)malloc(sizeof(double) * DEGREE);


		/********************************/

		printf("<<<   %d   >>>\n", t);
		for (int i = 0; i < NCOEF; i++) {
			fscanf(fp_r, "%lf", &poly[i]);
		}

		rpoly_(poly, &DEGREE, zeror, zeroi, &fail);
		if (fail) {
			printf("It failed...\n\n");
			fprintf(fp_w, "It failed...");
			continue;
		}

		for (int i = 0; i < DEGREE; i++) {
			real = 0.0;
			imaginary = 0.0;

			real_tmp[0] = zeror[i];
			imag_tmp[0] = zeroi[i];

			for (int j = 0; j < DEGREE - 1; j++) {
				real_tmp[j + 1] = zeror[i] * real_tmp[j] - zeroi[i] * imag_tmp[j];
				imag_tmp[j + 1] = zeroi[i] * real_tmp[j] + zeror[i] * imag_tmp[j];
			}

			for (int j = 0; j < DEGREE; j++) {
				real += poly[j] * real_tmp[DEGREE - (j+1)];
				imaginary += poly[j] * imag_tmp[DEGREE - (j+1)];
			}

			real = real + poly[DEGREE];
			tmp[i] = fabs(sqrt(real * real + imaginary * imaginary));
		}

		printf("\t실수부		허수부		|f(n)|\n");
		fprintf(fp_w,"\t실수부		허수부		|f(n)|\n");

		for (int i = 0; i < DEGREE; i++) {
			printf("%15lf	%15lf	%15lf\n", zeror[i], zeroi[i], tmp[i]);
			fprintf(fp_w, "%15lf	%15lf	%15lf\n", zeror[i], zeroi[i], tmp[i]);
		}

		printf("\n\n");
		real = 0.0;
		imaginary = 0.0;

		/********************************/

		free(real_tmp); free(imag_tmp); free(tmp);
		free(zeroi);
		free(zeror);
		free(poly);

		if (fp_r != NULL) fclose(fp_r);
		if (fp_w != NULL) fclose(fp_w);
	}
}