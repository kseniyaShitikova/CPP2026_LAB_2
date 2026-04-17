#pragma once
#ifndef QUADRATICEQUATION_H
#define QUADRATICEQUATION_H

#include <string>

class QuadraticEquation {
private:
    double a, b, c;

public:
    QuadraticEquation(double a_, double b_, double c_);
    int solve(double& x1, double& x2) const;
    std::string formatAnswer(double x1, double x2, int rootsCount) const;
    double getA() const;
    double getB() const;
    double getC() const;
};

#endif
