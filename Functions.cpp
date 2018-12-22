#include "Functions.h"
#include <iostream>
#include <random>
#include <chrono>



double Norm(const std::vector<double> &x, const std::vector<double> &y, int n) {
	double res = 0;
	for (int j = 0; j < n; ++j) {
		res += pow(x[j] - y[j], 2);
	}
	return res;
}

