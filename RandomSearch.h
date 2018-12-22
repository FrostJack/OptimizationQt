#pragma once
#include "Optim.h"

/**
Random search - optimization algorithm that minimizes multivariable function by throwing random points inside domain.
*/
class RandomSearch :
	public Optim
{
	double prob; /**< probability to randomize new point near current point */
public:
    RandomSearch(double p = 0.6) : Optim(), prob(p) {}
	void calculate(Func *pfun, const Border &border, const std::vector<double> &point, const double &eps = 0, const int &improve = max_steps)
		override;
    ~RandomSearch() {}
};

