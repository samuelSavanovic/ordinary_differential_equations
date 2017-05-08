#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double a, double x, double c) {
	return a*x + c;
}

void ode(double y0, double h, double slope, double (*coef)(double), FILE* plot) {
	int size = y0 / h;
	double t[size];
	t[0] = h;
	for(int i = 1; i < size; ++i) {
			t[i] = t[i-1] + h;
	}

	double y_star[size];
	y_star[0] = y0;
	fprintf(plot, "plot '-'\n");


	for (int i = 0; i < size; ++i) {
		double coeff = coef(t[i]);
		double k1= f(slope, y_star[i],coeff); 
		double y1 =y_star[i] + k1 * h/2;

		double k2 = f(slope, y1,coeff);
		double y2 = y_star[i] + k2 * h/2;

		double k3 = f(slope, y2,coeff);
		double y3 = y_star[i] + k3 * h/2;

		double k4 = f(slope, y3,coeff);

		y_star[i+1] = y_star[i] + (k1 + 2*k2 + 2*k3 +k4) * h /6;
		fprintf(plot, "%g %g \n", t[i], y_star[i]);
	}
	fprintf(plot, "e\n");
}

double coeff(double x) {
	return cos(4*x);	
}
int main() {
	FILE* plot = popen("gnuplot", "w");
	/*
	Solve: y'(t)=-2y(t)+cos(4t) with y0=3
	*/
	double y0 = 3, h = 0.01;
	
	ode(y0, h, -2, &coeff,plot);

	fflush(plot);
	getchar();
	pclose(plot);
	return 0;
}