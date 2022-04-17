#pragma once

#ifndef QBGRADIENT_H
#define QBGRADIENT_H


#include"Optimization.h"
#include <functional>

class Gradient:public Optimization {
    public:
        Gradient(Function *fun, \
                   Criteria *cr, \
                   std::vector<double> &point) : Optimization() {
            _func = fun;
            _criteria = cr;
            _start_point = point;
            _current_point = point;
        };

        ~Gradient() {};
        std::vector<double>optimize() override;
    private:
        double ComputeGradient(int dim);
        std::vector<double> ComputeGradientVector();
        double ComputeGradientMagnitude(std::vector<double> gradientVector);
};

#endif
