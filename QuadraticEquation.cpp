#include "QuadraticEquation.h"
#include <cmath>
#include <string>

const double EPS = 1e-9;

QuadraticEquation::QuadraticEquation(double a_, double b_, double c_)
    : a(a_), b(b_), c(c_) {
}

int QuadraticEquation::solve(double& x1, double& x2) const {
    if (std::fabs(a) < EPS) {
        return -1;
    }

    double d = b * b - 4 * a * c;

    if (d < 0) {
        return 0;
    }

    if (std::fabs(d) < EPS) {
        x1 = -b / (2 * a);
        return 1;
    }

    x1 = (-b - std::sqrt(d)) / (2 * a);
    x2 = (-b + std::sqrt(d)) / (2 * a);
    return 2;
}

std::string QuadraticEquation::formatAnswer(double x1, double x2, int rootsCount) const {
    if (rootsCount == 0) {
        return "no roots";
    }
    else if (rootsCount == 1) {
        return "x = " + std::to_string(x1);
    }
    else {
        if (x1 > x2) {
            std::swap(x1, x2);
        }
        return "x1 = " + std::to_string(x1) + ", x2 = " + std::to_string(x2);
    }
}

double QuadraticEquation::getA() const { return a; }
double QuadraticEquation::getB() const { return b; }
double QuadraticEquation::getC() const { return c; }
