#pragma once

#include<vector>
#include<numeric>
#include<cmath>
#include"Function.h"

/// A class of stop criteria
class Criteria {
public:
    virtual bool stop(Function *func, \
                      const std::vector<double> &start_point, \
                      const std::vector<double> &current_point, \
                      const double eps) = 0;
    virtual~Criteria() {}
};

class CriteriaGradient:public Criteria {
public:
    bool stop(Function *func, \
              const std::vector<double> &start_point, \
              const std::vector<double> &current_point, \
              const double eps) override;
};


class CriteriaArgument:public Criteria {
public:
    bool stop(Function *func, \
              const std::vector<double> &start_point, \
              const std::vector<double> &current_point, \
              const double eps) override;
};

class CriteriaValue:public Criteria {
public:
    bool stop(Function *func, \
              const std::vector<double> &start_point, \
              const std::vector<double> &current_point, \
              const double eps) override;
};


class CriteriaSteps:public Criteria{
    bool stop(Function *func, \
              const std::vector<double> &start_point, \
              const std::vector<double> &current_point, \
              const double eps) override;
};
