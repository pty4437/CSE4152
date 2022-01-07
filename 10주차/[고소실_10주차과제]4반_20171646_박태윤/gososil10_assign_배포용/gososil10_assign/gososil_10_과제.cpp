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
float compute_time1, compute_time2;


#define MATDIM 1024
#define HW1_N 1000000
//float *hw1_x, hw1_E, hw1_var1, hw1_var2;
//float hw2_a, hw2_b, hw2_c, hw2_naive_ans[2], hw2_pre_ans[2];

float* hw1_x, hw1_E, hw1_var1, hw1_var2;
float hw2_a, hw2_b, hw2_c, hw2_naive_ans[2], hw2_pre_ans[2];

/* hw1 */
void init_hw1(int fixed);
void hw1_calc_e();
void hw1_calc_var1();
void hw1_calc_var2();
/* hw2 */
void hw2_naive();
void hw2_safe();
float hw2_verify(float x);
/* hw3 */
void if_not_break();
void if_break();
void divide();
void shift_divide();
void not_bit();
void bit();
void loop();
void not_loop();
void func();
void not_func();
int sum(int, int);


void main(void)
{
	srand((unsigned)time(NULL));

	/* hw1 */
	puts("====== hw1 ======");
	init_hw1(1);
	hw1_calc_e();
	CHECK_TIME_START;
	hw1_calc_var1();
	CHECK_TIME_END(compute_time);
	compute_time1 = compute_time;
	printf("hw1_calc_var1 = %f ms\n", compute_time);
	printf("hw1_calc_var1 value = %.15lf\n", hw1_var1);


	CHECK_TIME_START;
	hw1_calc_var2();
	CHECK_TIME_END(compute_time);
	compute_time2 = compute_time;
	printf("hw1_calc_var2 = %f ms\n", compute_time);
	printf("hw1_calc_var2 value = %.15lf\n", hw1_var2);
	puts("");
	
	/* hw2 */
	puts("====== hw2 ======");
	printf("a, b, c : ");
	scanf("%f %f %f", &hw2_a, &hw2_b, &hw2_c);
	hw2_naive();
	hw2_safe();
	printf("naive result    : %.15lf, %.15lf\n", hw2_naive_ans[0], hw2_naive_ans[1]);
	printf("advanced result : %.15lf, %.15lf\n", hw2_pre_ans[0], hw2_pre_ans[1]);
	puts("");
	//hw2_verify(hw2_naive_ans[0]);
	//hw2_verify(hw2_naive_ans[1]);
	printf("Verifying naive ans    : %.15lf, %.15lf\n", hw2_verify(hw2_naive_ans[0]), hw2_verify(hw2_naive_ans[1]));
	printf("Verifying advanced ans : %.15lf, %.15lf\n", hw2_verify(hw2_pre_ans[0]), hw2_verify(hw2_pre_ans[1]));
	puts("");

	/* hw3 */
	
	//(1) : 조건문 쪼개기
	CHECK_TIME_START;
	if_not_break();
	CHECK_TIME_END(compute_time);
	printf("if_not_break = %f ms\n", compute_time);

	CHECK_TIME_START;
	if_break();
	CHECK_TIME_END(compute_time);
	printf("if_break = %f ms\n\n", compute_time);

	//(2) : shift 나눗셈
	CHECK_TIME_START;
	divide();
	CHECK_TIME_END(compute_time);
	printf("divide = %f ms\n", compute_time);

	CHECK_TIME_START;
	shift_divide();
	CHECK_TIME_END(compute_time);
	printf("shift_divide = %f ms\n\n", compute_time);

	//(3) : bit연산
	CHECK_TIME_START;
	not_bit();
	CHECK_TIME_END(compute_time);
	printf("not bit = %f ms\n", compute_time);

	CHECK_TIME_START;
	bit();
	CHECK_TIME_END(compute_time);
	printf("bit = %f ms\n\n", compute_time);

	//(4) : loop최적화
	CHECK_TIME_START;
	loop();
	CHECK_TIME_END(compute_time);
	printf("loop = %f ms\n", compute_time);

	CHECK_TIME_START;
	not_loop();
	CHECK_TIME_END(compute_time);
	printf("not_loop = %f ms\n\n", compute_time);

	//(5) : 함수 최적화
	CHECK_TIME_START;
	func();
	CHECK_TIME_END(compute_time);
	printf("func = %f ms\n", compute_time);

	CHECK_TIME_START;
	not_func();
	CHECK_TIME_END(compute_time);
	printf("not_func = %f ms\n\n", compute_time);
}

void init_hw1(int fixed)
{
	float *ptr;
	hw1_x = (float *)malloc(sizeof(float)*HW1_N);

	if (fixed)
	{
		float tmp = HW1_N;
		for (int i = 0; i < HW1_N; i++)
		{
			if( i & 1) tmp -= 0.0001;
			hw1_x[i] = tmp;
		}
	}
	else
	{
		srand((unsigned)time(NULL));
		ptr = hw1_x;
		for (int i = 0; i < HW1_N; i++)
			*ptr++ = ((float)rand() / (float)RAND_MAX) * 2;
	}
}
void hw1_calc_e()
{
	hw1_E = 0.0f;

	for (int i = 0; i < HW1_N; i++) {
		hw1_E += hw1_x[i];
	}

	hw1_E = hw1_E / HW1_N;
}
void hw1_calc_var1()
{
	hw1_var1 = 0.0f;
	float val = 0.0;
	float tmp = 0.0;

	for (int i = 0; i < HW1_N; i++) {
		tmp = hw1_x[i] - hw1_E;
		hw1_var1 += pow(tmp, 2.0);
	}

	hw1_var1 = hw1_var1 / (HW1_N - 1.0);
}
void hw1_calc_var2()
{
	hw1_var2 = 0.0;
	float tmp1 = 0.0, tmp2 = 0.0;

	for (int i = 0; i < HW1_N; i++) {
		tmp1 += pow(hw1_x[i], 2.0);
		tmp2 += hw1_x[i];
	}

	hw1_var2 = (HW1_N * tmp1 - pow(tmp2, 2.0)) / (HW1_N * (HW1_N - 1.0));
}


/* hw2 */
void hw2_naive()
{
	hw2_naive_ans[0] = ((-1.0) * hw2_b + sqrt(pow(hw2_b, 2.0) - (4 * hw2_a * hw2_c))) / (2 * hw2_a);
	hw2_naive_ans[1] = ((-1.0) * hw2_b - sqrt(pow(hw2_b, 2.0) - (4 * hw2_a * hw2_c))) / (2 * hw2_a);
}
void hw2_safe()
{
	hw2_pre_ans[0] = (-2.0 * hw2_c) / (sqrt(pow(hw2_b, 2.0) - 4.0 * hw2_a * hw2_c) + hw2_b);

	float tmp = hw2_pre_ans[0] * 2.0 * hw2_a;

	hw2_pre_ans[1] = (2.0 * hw2_c) / tmp;

}
float hw2_verify(float x)
{
	return hw2_a * x * x + hw2_b*x + hw2_c;
}


void if_not_break() {
	int num = 99;

	for (int i = 0; i < 1000000000; i++) {
		if (num < 10) {}
		else if (num < 20) {}
		else if (num < 30) {}
		else if (num < 40) {}
		else if (num < 50) {}
		else if (num < 60) {}
		else if (num < 70) {}
		else if (num < 80) {}
		else if (num < 90) {}
		else if (num < 100) {}
	}
}

void if_break() {
	int num = 99;

	for (int i = 0; i < 1000000000; i++) {		
		if (num < 50) {
			if (num < 30) {
				if(num < 10){}
				else {}
			}
			else {
				if(num < 40){}
				else {}
			}
		}
		else {
			if (num < 80) {
				if (num < 60) {}
				else {}
			}
			else {
				if(num < 90){}
				else{}
			}
		}
	}
}

void divide() {
	int res;

	for (int i = 0; i < 1000000; i++) {
		res = i / 4;
	}
}

void shift_divide() {
	int res;

	for (int i = 0; i < 1000000; i++) {
		res = i >> 2;
	}
}

void not_bit() {
	int num = 3;

	for (int i = 0; i < 100000000; i++) {
		if (num % 2 == 1) {}
		else if (num % 2 == 0) {}
	}
}

void bit() {
	int num = 3;

	for (int i = 0; i < 100000000; i++) {
		if (num & 1) {}
		else if (!(num & 1)) {}
	}
}

void loop() {
	int res = 0;

	for (int i = 0; i <= 500000; i++)
		res += i;

	printf("loop res : %d\n", res);
}

void not_loop() {
	int res = 0;
	int num = 500000;

	res = (num * (num + 1)) / 2;

	printf("not_loop res : %d\n", res);
}

int sum(int a, int b) {
	return a + b;
}

void func() {
	int res = 0;

	for (int i = 0; i < 1000000; i++) {
		res += sum(1, 2);
	}

	printf("func : %d\n", res);
}

void not_func() {
	int res = 0;

	for (int i = 0; i < 1000000; i++) {
		res += (1 + 2);
	}

	printf("not_func : %d\n", res);
}