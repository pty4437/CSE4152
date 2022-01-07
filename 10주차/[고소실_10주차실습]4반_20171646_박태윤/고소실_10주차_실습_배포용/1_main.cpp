#include <stdio.h>
#include <string.h>
#include <random>
#include <time.h>

#include <math.h>
#include <time.h>
#include <Windows.h>

__int64 start, freq, end;
#define CHECK_TIME_START QueryPerformanceFrequency((LARGE_INTEGER*)&freq); QueryPerformanceCounter((LARGE_INTEGER*)&start)
#define CHECK_TIME_END(a) QueryPerformanceCounter((LARGE_INTEGER*)&end); a = (float)((float)(end - start) / (freq / 1000.0f))
float compute_time;


#define MATDIM 1024
double *pMatA, *pMatB, *pMatC;
void MultiplySquareMatrices_1(double *pDestMatrix, double *pLeftMatrix, double *pRightMatrix, int MatSize);
void MultiplySquareMatrices_2(double *pDestMatrix, double *pLeftMatrix, double *pRightMatrix, int MatSize);
void MultiplySquareMatrices_3(double *pDestMatrix, double *pLeftMatrix, double *pRightMatrix, int MatSize);
void MultiplySquareMatrices_4(double *pDestMatrix, double *pLeftMatrix, double *pRightMatrix, int MatSize);

void init_MatMat(void);

void main(void)
{
	init_MatMat();

	CHECK_TIME_START;
	MultiplySquareMatrices_1(pMatC, pMatA, pMatB, MATDIM);
	//Sleep(500);
	CHECK_TIME_END(compute_time);
	printf("MultiplySquareMatrices_1 : %f ms\n", compute_time);

	CHECK_TIME_START;
	MultiplySquareMatrices_2(pMatC, pMatA, pMatB, MATDIM);
	//Sleep(500);
	CHECK_TIME_END(compute_time);
	printf("MultiplySquareMatrices_2 = %f ms\n", compute_time);

	CHECK_TIME_START;
	MultiplySquareMatrices_3(pMatC, pMatA, pMatB, MATDIM);
	//Sleep(500);
	CHECK_TIME_END(compute_time);
	printf("MultiplySquareMatrices_3 = %f ms\n", compute_time);

	CHECK_TIME_START;
	MultiplySquareMatrices_4(pMatC, pMatA, pMatB, MATDIM);
	//Sleep(500);
	CHECK_TIME_END(compute_time);
	printf("MultiplySquareMatrices_4 = %f ms\n", compute_time);
}

void MultiplySquareMatrices_1(double* pDestMatrix, double* pLeftMatrix, double* pRightMatrix, int MatSize)
{
	int i, j, k;
	for (i = 0; i < MATDIM; i++) {
		for (j = 0; j < MATDIM; j++) {
			double value = 0;
			for (k = 0; k < MATDIM; k++) {
				value += pLeftMatrix[i * MATDIM + k] * pRightMatrix[k * MATDIM + j];
			}
			pDestMatrix[i * MATDIM + j] = value;
		}
	}

}

void MultiplySquareMatrices_2(double* pDestMatrix, double* pLeftMatrix, double* pRightMatrix, int MatSize)
{
	int i, j, k;
	for (i = 0; i < MATDIM; i++) {
		for (j = 0; j < MATDIM; j++) {
			double left = pLeftMatrix[i * MATDIM + j];
			double value = 0;
			for (k = 0; k < MATDIM; k++) {
				value += left * pRightMatrix[j * MATDIM + k];
			}
			pDestMatrix[i * MATDIM + k] = value;
		}
	}
}

void MultiplySquareMatrices_3(double* pDestMatrix, double* pLeftMatrix, double* pRightMatrix, int MatSize)
{
	int i, j, k;
	for (i = 0; i < MATDIM; i++) {
		for (j = 0; j < MATDIM; j++) {
			double value = 0;
			for (k = 0; k < MATDIM; k += 16) {
				value += pLeftMatrix[i * MATDIM + k] * pRightMatrix[k + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 1)] * pRightMatrix[(k + 1) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 2)] * pRightMatrix[(k + 2) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 3)] * pRightMatrix[(k + 3) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 4)] * pRightMatrix[(k + 4) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 5)] * pRightMatrix[(k + 5) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 6)] * pRightMatrix[(k + 6) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 7)] * pRightMatrix[(k + 7) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 8)] * pRightMatrix[(k + 8) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 9)] * pRightMatrix[(k + 9) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 10)] * pRightMatrix[(k + 10) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 11)] * pRightMatrix[(k + 11) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 12)] * pRightMatrix[(k + 12) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 13)] * pRightMatrix[(k + 13) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 14)] * pRightMatrix[(k + 14) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 15)] * pRightMatrix[(k + 15) + MATDIM * j];
			}
			pDestMatrix[i * MATDIM + j] = value;
		}
	}
}

void MultiplySquareMatrices_4(double* pDestMatrix, double* pLeftMatrix, double* pRightMatrix, int MatSize)
{
	int i, j, k;
	for (i = 0; i < MATDIM; i++) {
		for (j = 0; j < MATDIM; j++) {
			double value = 0;
			for (k = 0; k < MATDIM; k += 64) {
				value += pLeftMatrix[i * MATDIM + k] * pRightMatrix[k + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 1)] * pRightMatrix[(k + 1) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 2)] * pRightMatrix[(k + 2) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 3)] * pRightMatrix[(k + 3) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 4)] * pRightMatrix[(k + 4) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 5)] * pRightMatrix[(k + 5) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 6)] * pRightMatrix[(k + 6) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 7)] * pRightMatrix[(k + 7) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 8)] * pRightMatrix[(k + 8) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 9)] * pRightMatrix[(k + 9) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 10)] * pRightMatrix[(k + 10) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 11)] * pRightMatrix[(k + 11) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 12)] * pRightMatrix[(k + 12) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 13)] * pRightMatrix[(k + 13) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 14)] * pRightMatrix[(k + 14) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 15)] * pRightMatrix[(k + 15) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 16)] * pRightMatrix[(k + 16) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 17)] * pRightMatrix[(k + 17) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 18)] * pRightMatrix[(k + 18) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 19)] * pRightMatrix[(k + 19) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 20)] * pRightMatrix[(k + 20) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 21)] * pRightMatrix[(k + 21) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 22)] * pRightMatrix[(k + 22) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 23)] * pRightMatrix[(k + 23) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 24)] * pRightMatrix[(k + 24) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 25)] * pRightMatrix[(k + 25) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 26)] * pRightMatrix[(k + 26) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 27)] * pRightMatrix[(k + 27) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 28)] * pRightMatrix[(k + 28) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 29)] * pRightMatrix[(k + 29) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 30)] * pRightMatrix[(k + 30) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 31)] * pRightMatrix[(k + 31) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 32)] * pRightMatrix[(k + 32) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 33)] * pRightMatrix[(k + 33) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 34)] * pRightMatrix[(k + 34) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 35)] * pRightMatrix[(k + 35) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 36)] * pRightMatrix[(k + 36) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 37)] * pRightMatrix[(k + 37) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 38)] * pRightMatrix[(k + 38) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 39)] * pRightMatrix[(k + 39) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 40)] * pRightMatrix[(k + 40) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 41)] * pRightMatrix[(k + 41) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 42)] * pRightMatrix[(k + 42) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 43)] * pRightMatrix[(k + 43) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 44)] * pRightMatrix[(k + 44) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 45)] * pRightMatrix[(k + 45) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 46)] * pRightMatrix[(k + 46) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 47)] * pRightMatrix[(k + 47) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 48)] * pRightMatrix[(k + 48) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 49)] * pRightMatrix[(k + 49) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 50)] * pRightMatrix[(k + 50) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 51)] * pRightMatrix[(k + 51) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 52)] * pRightMatrix[(k + 52) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 53)] * pRightMatrix[(k + 53) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 54)] * pRightMatrix[(k + 54) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 55)] * pRightMatrix[(k + 55) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 56)] * pRightMatrix[(k + 56) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 57)] * pRightMatrix[(k + 57) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 58)] * pRightMatrix[(k + 58) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 59)] * pRightMatrix[(k + 59) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 60)] * pRightMatrix[(k + 60) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 61)] * pRightMatrix[(k + 61) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 62)] * pRightMatrix[(k + 62) + MATDIM * j];
				value += pLeftMatrix[i * MATDIM + (k + 63)] * pRightMatrix[(k + 63) + MATDIM * j];
			}
			pDestMatrix[i * MATDIM + j] = value;
		}
	}
}

void init_MatMat(void)
{
	double *ptr;
	pMatA = (double *)malloc(sizeof(double)*MATDIM*MATDIM);
	pMatB = (double *)malloc(sizeof(double)*MATDIM*MATDIM);
	pMatC = (double *)malloc(sizeof(double)*MATDIM*MATDIM);
	srand((unsigned)time(NULL));
	ptr = pMatA;
	for (int i = 0; i < MATDIM*MATDIM; i++)
		*ptr++ = (double)rand() / ((double)RAND_MAX);
	ptr = pMatB;
	for (int i = 0; i < MATDIM*MATDIM; i++)
		*ptr++ = (double)rand() / ((double)RAND_MAX);
}
