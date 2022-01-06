#define _USE_MATH_DEFINES
#include <math.h>

float _sp_f_comp(float x) {
	return log(x)-1;
}

float _sp_fp_comp(float x) {
	return 1.0/x;
}
