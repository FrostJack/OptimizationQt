#pragma once
#include "Optim.h"
#include <random>

/**
Random search - optimization algorithm that minimizes multivariable function by throwing random points inside domain.
*/
class RandomSearch :
	public Optim
{
	double prob; /**< probability to randomize new point near current point */
    std::default_random_engine generator;
    std::uniform_real_distribution<double> standard;
public:
    RandomSearch(double p = 0.9);
	void calculate(Func *pfun, const Border &border, const std::vector<double> &point, const double &eps = 0, const int &improve = max_steps)
		override;
    ~RandomSearch() {}
};

