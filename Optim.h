#pragma once

#include "Func.h"
#include "Border.h"

const int max_steps = 1e8;

class Optim
{
protected:
	int steps; /**< the amount of steps algorithm made while minimizing a function */
public:
    Optim(): steps(0), ans(0), f_ans(0), path(0) {}
    std::vector<std::vector<double>> path;
    std::vector<double> ans; /**< minimum point */
    double f_ans; /**< minimum value */
	virtual void calculate(Func *pfun, const Border &border, const std::vector<double> &point, const double &eps = 0, 
		const int &improve = max_steps) = 0;
    //void output();
    int getSteps();
    virtual ~Optim() {}
};

