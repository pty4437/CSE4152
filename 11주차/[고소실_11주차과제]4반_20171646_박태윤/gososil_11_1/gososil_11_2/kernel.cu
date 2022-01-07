#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include <Windows.h>
#include <time.h>
#include <assert.h>

#define CUDA_CALL(x) { const cudaError_t a = (x); if(a != cudaSuccess) { printf("\nCuda Error: %s (err_num=%d) at line:%d\n", cudaGetErrorString(a), a, __LINE__); cudaDeviceReset(); assert(0);}}
typedef float TIMER_T;

#define USE_CPU_TIMER 1
#define USE_GPU_TIMER 1

#if USE_CPU_TIMER == 1
__int64 start, freq, end;
#define CHECK_TIME_START { QueryPerformanceFrequency((LARGE_INTEGER*)&freq); QueryPerformanceCounter((LARGE_INTEGER*)&start); }
#define CHECK_TIME_END(a) { QueryPerformanceCounter((LARGE_INTEGER*)&end); a = (float)((float)(end - start) / (freq / 1000.0f)); }
#else
#define CHECK_TIME_START
#define CHECK_TIME_END(a)
#endif

#if USE_GPU_TIMER == 1
cudaEvent_t cuda_timer_start, cuda_timer_stop;
#define CUDA_STREAM_0 (0)

void create_device_timer()
{
    CUDA_CALL(cudaEventCreate(&cuda_timer_start));
    CUDA_CALL(cudaEventCreate(&cuda_timer_stop));
}

void destroy_device_timer()
{
    CUDA_CALL(cudaEventDestroy(cuda_timer_start));
    CUDA_CALL(cudaEventDestroy(cuda_timer_stop));
}

inline void start_device_timer()
{
    cudaEventRecord(cuda_timer_start, CUDA_STREAM_0);
}

inline TIMER_T stop_device_timer()
{
    TIMER_T ms;
    cudaEventRecord(cuda_timer_stop, CUDA_STREAM_0);
    cudaEventSynchronize(cuda_timer_stop);

    cudaEventElapsedTime(&ms, cuda_timer_start, cuda_timer_stop);
    return ms;
}

#define CHECK_TIME_INIT_GPU() { create_device_timer(); }
#define CHECK_TIME_START_GPU() { start_device_timer(); }
#define CHECK_TIME_END_GPU(a) { a = stop_device_timer(); }
#define CHECK_TIME_DEST_GPU() { destroy_device_timer(); }
#else
#define CHECK_TIME_INIT_GPU()
#define CHECK_TIME_START_GPU()
#define CHECK_TIME_END_GPU(a)
#define CHECK_TIME_DEST_GPU()
#endif

#define BLOCK_SIZE 32
#define DATA_SIZE (1 << 20)

TIMER_T compute_time = 0;
TIMER_T device_time = 0;

int N;
float* A, * B, * C;
float* X0, * X1;
float* FX0, * FX1;
float* gpu_X0, * gpu_X1;
float* gpu_FX0, * gpu_FX1;


cudaError_t find_roots_GPU(float* A, float* B, float* C, float* gpu_X0, float* gpu_X1, float* gpu_FX0, float* gpu_FX1);

__global__ void find_roots_Kernel(float* d_A, float* d_B, float* d_C, float* d_X0, float* d_X1, float* d_FX0, float* d_FX1)
{
    float a, b, c, d, x0, x1, tmp;
    int idx = threadIdx.x + blockDim.x * blockIdx.x;

    a = d_A[idx]; b = d_B[idx]; c = d_C[idx];
    d = sqrtf(b * b - 4.0f * a * c);
    tmp = 1.0f / (2.0f * a);
    d_X0[idx] = x0 = (-b - d) * tmp;
    d_X1[idx] = x1 = (-b + d) * tmp;
    d_FX0[idx] = (a * x0 + b) * x0 + c;
    d_FX1[idx] = (a * x1 + b) * x1 + c;

}


void find_roots_CPU(float* A, float* B, float* C, float* X0, float* X1, float* FX0, float* FX1, int n) {
    int i;
    float a, b, c, d, x0, x1, tmp;
    for (i = 0; i < n; i++) {
        a = A[i]; b = B[i]; c = C[i];
        d = sqrtf(b * b - 4.0f * a * c);
        tmp = 1.0f / (2.0f * a);
        X0[i] = x0 = (-b - d) * tmp;
        X1[i] = x1 = (-b + d) * tmp;
        FX0[i] = (a * x0 + b) * x0 + c;
        FX1[i] = (a * x1 + b) * x1 + c;
    }
}

void init_bin_file(int size) {
    srand((unsigned)time(NULL));
    printf("***Binary File init Start!!\n");
    FILE* fp_a = fopen("A.bin", "wb");
    FILE* fp_b = fopen("B.bin", "wb");
    FILE* fp_c = fopen("C.bin", "wb");


    fwrite(&size, sizeof(int), 1, fp_a);

    float random_num;
    for (int i = 0; i < size; i++) {
        random_num = (float)(rand() % 10) - 5.0f;
        if (random_num == 0.0f)
            random_num = 1.0f;
        fwrite(&random_num, sizeof(float), 1, fp_a);
    }

    fclose(fp_a);

    fwrite(&size, sizeof(int), 1, fp_b);
    random_num = 0.0f;

    for (int i = 0; i < size; i++) {
        random_num = (float)(rand() % 10) + 30.0f;
        if (random_num == 0.0f)
            random_num = 4.0f;
        fwrite(&random_num, sizeof(float), 1, fp_b);
    }

    fclose(fp_b);

    fwrite(&size, sizeof(int), 1, fp_c);

    for (int i = 0; i < size; i++) {
        random_num = (float)(rand() % 10) - 5.0f;
        if (random_num == 0.0f)
            random_num = 2.0f;
        fwrite(&random_num, sizeof(float), 1, fp_c);
    }

    fclose(fp_c);


    printf("***Binary File init End!!\n\n");
}

void read_bin_file()
{
    printf("***Binary File Read Start!!\n");
    FILE* fp = fopen("A.bin", "rb");
    /*Todo*/

    fread(&N, sizeof(int), 1, fp);

    A = new float[N]; B = new float[N]; C = new float[N];
    X0 = new float[N]; X1 = new float[N];
    FX0 = new float[N]; FX1 = new float[N];
    gpu_X0 = new float[N]; gpu_X1 = new float[N];
    gpu_FX0 = new float[N]; gpu_FX1 = new float[N];

    fread(A, sizeof(float), N, fp);
    

    fclose(fp);

    fp = fopen("B.bin", "rb");
    fread(&N, sizeof(int), 1, fp);
    fread(B, sizeof(float), N, fp);
    fclose(fp);

    fp = fopen("C.bin", "rb");
    fread(&N, sizeof(int), 1, fp);
    fread(C, sizeof(float), N, fp);
    fclose(fp);

    printf("***Binary File Read End!!\n\n");
}

int main()
{
    int i;
    FILE* fp;

    init_bin_file(DATA_SIZE);
    read_bin_file();

    printf("==========================================\n");
    printf("N is %d.\n", N);
    printf("==========================================\n\n");

    printf("==========================================\n");
    printf("***find_roots_CPU Start!!\n");
    CHECK_TIME_START;
    find_roots_CPU(A, B, C, X0, X1, FX0, FX1, N);
    CHECK_TIME_END(compute_time);
    printf("***find_roots_CPU End!!\n");
    printf("CPU time = %.6f\n", compute_time);
    //printf("X0 : %f, FX0 : %f\n", X0[1], FX0[1]);
    //printf("X1 : %f, FX1 : %f\n", X1[1], FX1[1]);
    printf("==========================================\n\n");


    printf("==========================================\n");
    printf("***find_roots_GPU Start!!\n");
    find_roots_GPU(A, B, C, gpu_X0, gpu_X1, gpu_FX0, gpu_FX1);
    printf("***find_roots_GPU End!!\n");
    printf("GPU time = %.6f\n", device_time);
    //printf("X0 : %f, FX0 : %f\n", gpu_X0[1], gpu_FX0[1]);
    //printf("X1 : %f, FX1 : %f\n", gpu_X1[1], gpu_FX1[1]);
    printf("==========================================\n\n");

    fp = fopen("X0.bin", "wb");
    if (!fp) {
        fprintf(stderr, "Error: cannot open the output file...\n");
        exit(-1);
    }

    fwrite(&N, sizeof(int), 1, fp);

    for (i = 0; i < N; i++)
        fwrite(&gpu_X0[i], sizeof(float), 1, fp);

    fclose(fp);


    fp = fopen("X1.bin", "wb");
    if (!fp) {
        fprintf(stderr, "Error: cannot open the output file...\n");
        exit(-1);
    }

    fwrite(&N, sizeof(int), 1, fp);

    for (i = 0; i < N; i++)
        fwrite(&gpu_X1[i], sizeof(float), 1, fp);

    fclose(fp);

    fp = fopen("FX0.bin", "wb");

    fwrite(&N, sizeof(int), 1, fp);

    for (i = 0; i < N; i++)
        fwrite(&gpu_FX0[i], sizeof(float), 1, fp);

    fclose(fp);

    printf("end!!\n\n");

    fp = fopen("FX1.bin", "wb");

    fwrite(&N, sizeof(int), 1, fp);

    for (i = 0; i < N; i++)
        fwrite(&gpu_X0[i], sizeof(float), 1, fp);

    fclose(fp);


    return 0;
}


cudaError_t find_roots_GPU(float* A, float* B, float* C, float* gpu_X0, float* gpu_X1, float* gpu_FX0, float* gpu_FX1)
{
    CHECK_TIME_INIT_GPU();

    cudaError_t cudaStatus;
    cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
        goto Error;
    }

    float* d_A, * d_B, * d_C;
    float* d_X0, * d_X1;
    float* d_FX0, * d_FX1;
    dim3 dimBlock(BLOCK_SIZE, 1);
    dim3 dimGrid(N / dimBlock.x, 1);

    size_t size;

    size = N * sizeof(float);

    cudaMalloc(&d_A, size);
    cudaMalloc(&d_B, size);
    cudaMalloc(&d_C, size);
    cudaMalloc(&d_X0, size);
    cudaMalloc(&d_X1, size);
    cudaMalloc(&d_FX0, size);
    cudaMalloc(&d_FX1, size);

    cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_C, C, size, cudaMemcpyHostToDevice);   

    size = N;

    CHECK_TIME_START_GPU();

    find_roots_Kernel << < dimGrid, dimBlock >> > (d_A, d_B, d_C, d_X0, d_X1, d_FX0, d_FX1);

    CHECK_TIME_END_GPU(device_time);
    size = N * sizeof(float);

    cudaGetLastError();
    cudaDeviceSynchronize();

    cudaMemcpy(gpu_X0, d_X0, size, cudaMemcpyDeviceToHost);
    cudaMemcpy(gpu_X1, d_X1, size, cudaMemcpyDeviceToHost);
    cudaMemcpy(gpu_FX0, d_FX0, size, cudaMemcpyDeviceToHost);
    cudaMemcpy(gpu_FX1, d_FX1, size, cudaMemcpyDeviceToHost);

    CHECK_TIME_DEST_GPU();

Error:
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
    cudaFree(d_X0);
    cudaFree(d_X1);
    cudaFree(d_FX0);
    cudaFree(d_FX1);

    return cudaStatus;
}