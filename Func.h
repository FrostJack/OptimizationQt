#pragma once

#include <vector>
#include <math.h>

/**
virtual parent class for objects immitating mathematical functions. 
*/

class Func
{
protected:
	int n; /**< function dimension */
public:
    Func(int n_ = 0) :n(n_) {}
	int dim() { return n; }
	virtual double f(const std::vector<double> &point) = 0; 
    virtual ~Func() {}
};


/**
f(x, y) = 5x ^ 2 - 6xy + 5y ^ 2
min f(x, y) = 0 at (0, 0)
*/

class TwoDim :
    public Func
{
public:
    TwoDim() :Func(2) {}
    double f(const std::vector<double> &point) override;
    ~TwoDim() {}
};


/**
Rosenbrock function
f(x, y) = (1 - x)^2 + 100(y - x^2)^2
min f(x, y) = 0 at (1, 1)
*/
class TwoDim2 :
    public Func
{
public:
    TwoDim2() :Func(2) {}
    double f(const std::vector<double> &point) override;
    ~TwoDim2() {}
};
