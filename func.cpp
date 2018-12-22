#include "Func.h"
#include "Exception.h"

double TwoDim::f(const std::vector<double> &point) {
    if (point.size() != n)
        throw Exception("Point with wrong dimension received in ThreeDim function");
    double x = point[0];
    double y = point[1];
    return 5 * pow(x, 2) - 6 * x*y + 5 * pow(y, 2);
}

double TwoDim2::f(const std::vector<double> &point) {
    if (point.size() != n)
        throw Exception("Point with wrong dimension received in ThreeDim function");
    double x = point[0];
    double y = point[1];
    return pow((1 - x), 2) + 100*pow(y - pow(x, 2), 2);
}
