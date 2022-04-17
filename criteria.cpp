#include "criteria.h"

bool  CriteriaGradient::stop(Function *func, \
                             const std::vector<double> &start_point, \
                             const std::vector<double> &current_point, \
                             const double eps){
    std::vector<double>g(func->gradient(current_point));
    return (std::inner_product(g.begin(), g.end(), g.begin(), 0.) > eps);
}


bool CriteriaArgument::stop(Function *func, \
                            const std::vector<double> &start_point, \
                            const std::vector<double> &current_point, \
                            const double eps){
    std::vector<double> y(current_point.size());
    for(auto i = 0; i < y.size(); ++i)
        y[i] = current_point[i] - start_point[i];
    return(std::inner_product(y.begin(), y.end(), y.begin(), 0.) > eps);
}

bool CriteriaValue::stop(Function *func, \
                         const std::vector<double> &start_point, \
                         const std::vector<double> &current_point, \
                         const double eps){
    return(abs((func->func_value(current_point) - func->func_value(start_point)) / func->func_value(current_point)) > eps);
}

bool CriteriaSteps::stop(Function *func, \
                          const std::vector<double> &start_point, \
                          const std::vector<double> &current_point, \
                          const double eps){
    return true;
}
