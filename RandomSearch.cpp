#include "RandomSearch.h"
#include <random>
#include <iostream>

void RandomSearch::calculate(Func *pfun, const Border &border, const std::vector<double> &point, const double &eps,
	const int &improve) {
	unsigned seed = 13;
	std::default_random_engine generator(seed);
	std::uniform_real_distribution<double> stand(0.0, 1.0);
	steps = 0;
	int improve_steps = 0;
	int n = pfun->dim();
    path.clear();
    path.shrink_to_fit();
    std::vector<double> starts;
    std::vector<double> ends;
    starts.push_back(point[0]);
    ends.push_back(point[1]);

	double rand, left, right;
	ans = point;
	f_ans = pfun->f(ans);
	std::vector<double> y(point);
	double f_y;
	double delta = 1;
	while (steps < max_steps) {
		++steps;
		rand = stand(generator);
		if (rand > prob)
			for (int j = 0; j < n; ++j) {
				rand = border.left[j] + (border.right[j] - border.left[j])*stand(generator);
				y[j] = rand;
			}
		else {
			for (int j = 0; j < n; ++j) {
				if (border.left[j] > ans[j] - delta)
					left = border.left[j];
				else left = ans[j] - delta;
				if (border.right[j] < ans[j] + delta)
					right = border.right[j];
				else right = ans[j] + delta;
				rand = left + (right - left)*stand(generator);
				y[j] = rand;
			}
		}
		f_y = pfun->f(y);
		if (f_y < f_ans) {
            starts.push_back(y[0]);
            ends.push_back(y[1]);
			ans = y;
			if ((f_ans - f_y) < eps) {
				f_ans = f_y;
                path.push_back(starts);
                path.push_back(ends);
				return;
			}
			f_ans = f_y;
			if (rand <= prob)
				delta *= 0.7;
			improve_steps = 0;
		}
		else {
			++improve_steps;
            if (improve_steps > improve){
                path.push_back(starts);
                path.push_back(ends);
				return;
            }
		}
	}
    path.push_back(starts);
    path.push_back(ends);
	return;
}
