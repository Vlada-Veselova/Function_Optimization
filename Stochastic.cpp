#include"Stochastic.h"

std::vector<double>Stochastic::optimize(){
    unsigned seed(std::chrono::system_clock::now().time_since_epoch().count());
    std::mt19937 generator(seed);
    std::bernoulli_distribution Ber(_bernoulli_param);
    std::vector<double> x0(_start_point);
    _current_point = _start_point;
    _trajectory.push_back(x0);
    double fmin(_func->func_value(x0));
    for (auto k = 0; k < _max_iter; ++k) {
        if (Ber(generator)) {
            double box[_func->GetDim()][2];
            for (auto i = 0; i < _func->GetDim(); ++i) {
                box[i][0] = std::max(x0[i] - _delta, _area->GetLeftBound(i));
                box[i][1] = std::min(x0[i] + _delta, _area->GetRightBound(i));
            }
            for(auto i = 0; i < _func->GetDim(); ++i) {
                std::uniform_real_distribution<double> uniform(box[i][0], box[i][1]);
                _current_point[i] = uniform(generator);
            }
            _delta *= _step_size;
        } else {
            for (auto i = 0; i < _func->GetDim(); ++i) {
                std::uniform_real_distribution<double> uniform(_area->GetLeftBound(i), _area->GetRightBound(i));
                _current_point[i] = uniform(generator);
            }
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
