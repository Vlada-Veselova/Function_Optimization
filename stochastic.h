#pragma once

#include"Optimization.h"

class Stochastic: public Optimization{
public:
    Stochastic(Function *func, \
               Criteria *criteria, \
               std::vector<double> &start_point) : _bernoulli_param(0.5), _delta(0.5) {
        _func = func;
        _criteria = criteria;
        _start_point = start_point;
        _current_point = start_point;
    };
    ~Stochastic() {};

    double SetBernoulliParam(double p) { return _bernoulli_param = p; };
    double SetDelta(double delta) { return _delta = delta; };
    std::vector<double>optimize() override;
private:
    double _bernoulli_param;
    double _delta;
};
