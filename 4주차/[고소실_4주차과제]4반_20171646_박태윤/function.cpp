#define _USE_MATH_DEFINES
#include <math.h>

double _f1(double x) {

	return pow(x,2)-4*x+4.0-log(x);
}

double _fp1(double x) {
	return 2*x-4.0-(1.0/x);
}

double _f2(double x) {
	return x+1.0-2*sin(M_PI*x);
}

double _fp2(double x) {
	return 1-2.0*M_PI*cos(M_PI*x);
}

double _f3(double x) {
	return pow(x,4) - 11.0*pow(x,3) + 42.35*pow(x,2) - 66.55*x + 35.1384;
}

double _fp3(double x) {
	return 4*pow(x,3) - 33.0 * pow(x,2) + 84.70*x - 66.55;
}

double _f_sqrt(double x) {
	return x * x - 2.0;
}

double _fp_sqrt(double x) {
	return 2.0 * x;
}

double _f_vehicle(double x) {
	double A = 89 * sin(11.5 * (M_PI / 180));
	double B = 89 * cos(11.5 * (M_PI / 180));
	double C = (49.0 + 0.5 * 55.0) * sin(11.5 * (M_PI / 180)) - 0.5 * 55.0 * tan(11.5 * (M_PI / 180));
	double E = (49.0 + 0.5 * 55.0) * cos(11.5 * (M_PI / 180)) - 0.5 * 55.0;


	return A * sin(x * (M_PI / 180)) * cos(x * (M_PI / 180)) + B * pow(sin(x * (M_PI / 180)), 2) - C * cos(x * (M_PI / 180)) - E * sin(x * (M_PI / 180));
}

double _fp_vehicle(double x) {
	double A = 89 * sin(11.5 * (M_PI / 180));
	double B = 89 * cos(11.5 * (M_PI / 180));
	double C = (49.0 + 0.5 * 55.0) * sin(11.5 * (M_PI / 180)) - 0.5 * 55.0 * tan(11.5 * (M_PI / 180));
	double E = (49.0 + 0.5 * 55.0) * cos(11.5 * (M_PI / 180)) - 0.5 * 55.0;

	return A * pow(cos(x * (M_PI / 180)), 2) - A * pow(sin(x * (M_PI / 180)), 2) + 2 * B * cos(x * (M_PI / 180)) * sin(x * (M_PI / 180)) + C * sin(x * (M_PI / 180)) - E * cos(x * (M_PI / 180));
}

double _f_comp(double x) {
	return log(x) - 1;
}

double _fp_comp(double x) {
	return 1.0 / x;
}
