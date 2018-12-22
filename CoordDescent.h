#pragma once
#include "Optim.h"

/**
Coordinate Descent - optimization algorithm that minimizes along coordinate directions to find the minimum of a multivariable function
*/
const double alpha = 0.618;

class CoordDescent :
	public Optim
{
public:
    CoordDescent(): Optim() {}
	void calculate(Func *pfun, const Border &border, const std::vector<double> &point, const double &eps = 0, const int &improve = max_steps)
		override; //!< Calculates minimum point, minimum value and the amount of steps it took to minimize
    ~CoordDescent() {}
};

/**
Golden ratio - optimization algorithm that minimizes one-dimensional function. 
*/
double GoldenRatio(double a, double b, Func *pfun, double eps, int index, std::vector<double> &var); 
