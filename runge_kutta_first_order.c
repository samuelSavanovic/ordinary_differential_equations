#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double a = 1, double x=1, double c = 0) {
	return a*x + c;
}

void ode(double y0, double h, FILE* plot) {
	int size = y0 / h;
	double t[size] = {0};
	t[0] = h;
	for(int i = 1; i < size; ++i) {
			t[i] = t[i-1] + h;
	}

	double y_star[size] = {0.0};
	y_star[0] = y0;

	fprintf(plot, "plot '-'\n");

	for (int i = 0; i < size; ++i) {

		double k1= f(-2, y_star[i], cos(4*t[i])); //aprox of deriv
		y_star[i+1] = y_star[i] + k1 *h;
		fprintf(plot, "%g %g \n", t[i], y_star[i]);
	}
	fprintf(plot, "e\n");
}

int main() {
	FILE* plot = popen("gnuplot", "w");
	/*
	Solve: y'(t)=-2y(t)+cos(4t) with y0=3
	*/
	double y0 = 3, h = 0.01;

	ode(y0, h, plot);

	fflush(plot);
	getchar();
	pclose(plot);
	return 0;
}