#pragma once

#include<cfloat>
#include<chrono>
#include<random>
#include<vector>
#include<list>
#include "function.h"
#include "criteria.h"

class Optimization{
public:
    Optimization() : _n_iter(0), _eps(0.001), _step_size(0.1), _max_iter(1000) {};

    virtual std::vector<double>optimize() = 0;

    int GetIterations(){ return _n_iter; };
    std::list<std::vector<double>> GetTrajectory(){ return _trajectory; };
    void SetFunction(Function *func) { _func = func; };
    void SetCriteria(Criteria *criteria) { _criteria = criteria; };
    void SetStartPoint(const std::vector<double> &start_point) { _start_point = start_point; };
    void SetStepSize(const double step_size){ _step_size = step_size; };
    void SetMaxIterations(const int max_iter) { _max_iter = max_iter; };
    void SetEps(const double eps) { _eps = eps; };

    virtual ~Optimization() {};

protected:
    int _n_iter;
    Function *_func;
    Criteria *_criteria;
    std::vector<double> _start_point;
    std::vector<double> _current_point;
    std::list<std::vector<double>> _trajectory;
    double _eps;
    double _step_size;
    int _max_iter;
};
