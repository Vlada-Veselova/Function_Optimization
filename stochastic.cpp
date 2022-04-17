#include "stochastic.h"

std::vector<double>Stochastic::optimize(){
    unsigned seed(std::chrono::system_clock::now().time_since_epoch().count());
    std::mt19937 generator(seed);
    std::bernoulli_distribution Ber(_bernoulli_param);
    std::vector<double> x0(_start_point);
    _current_point = _start_point;
    _trajectory.push_back(x0);
    double fmin(_func->func_value(x0));
    for (auto k = 0; k < _max_iter; ++k) {
        for (auto i = 0; i < _func->GetDim(); ++i) {
            std::uniform_real_distribution<double> uniform(-_delta, _delta);
            _current_point[i] = uniform(generator);
        }
        double fx(_func->func_value(_current_point));
        if (fx < fmin){
            x0 = _current_point;
            fmin = fx;
            _trajectory.push_back(x0);
        }
    }
    _n_iter = _max_iter;
    return x0;
}
