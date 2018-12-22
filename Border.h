#pragma once
#include <vector>

/**
n-dimensional rectangular domain
*/

class Border
{
	int n; /**< dimension */
public:
	std::vector<double> left;
	std::vector<double> right;
    Border(int n_ = 0) : n(n_), left(n_), right(n_) {}
    Border(const int &n_, std::vector<double> left_, std::vector<double> right_);
    void changeDim(const int &n_);
    void changeLeft(std::vector<double> left_);
    void changeRight(std::vector<double> right_);
    void changeBorder(const int &n_, std::vector<double> left_, std::vector<double> right_);
    ~Border() {}
};
