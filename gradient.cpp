#include "gradient.h"
#include <iostream>
#include <fstream>
#include <math.h>


std::vector<double>Gradient::optimize() {
    _n_iter = 0;
    _current_point = _start_point;
    double gradientMagnitude = 1.0;
    do {
        _trajectory.push_back(_current_point);
        std::vector<double> gradientVector = ComputeGradientVector();
        gradientMagnitude = ComputeGradientMagnitude(gradientVector);
        for (auto i = 0; i < _func->GetDim(); ++i) {
            _current_point[i] += -(gradientVector[i] * _step_size);
        }
        ++_n_iter;
    } while ((_n_iter < _max_iter) && (_criteria->stop(_func, _start_point, _current_point, _eps)));
    return _current_point;
}

double Gradient::ComputeGradient(int dim) {
    std::vector<double> new_point = _current_point;
    new_point[dim] += _step_size;
    auto func_val_1 = (_func->func_value)(_current_point);
    auto func_val_2 = (_func->func_value)(new_point);
    return (func_val_2 - func_val_1) / _step_size;
}

std::vector<double> Gradient::ComputeGradientVector() {
    std::vector<double> gradientVector = _current_point;
    for (auto i = 0; i < _func->GetDim(); ++i)
        gradientVector[i] = ComputeGradient(i);

    return gradientVector;
}

double Gradient::ComputeGradientMagnitude(std::vector<double> gradient_vector) {
    double vectorMagnitude = 0.0;
    for (auto i = 0; i < _func->GetDim(); ++i) {
        vectorMagnitude += gradient_vector[i] * gradient_vector[i];
    }
    return sqrt(vectorMagnitude);
}
