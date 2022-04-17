#include"function.h"

double Sphere::func_value(const std::vector<double> &x) {
    double ans{};
    for (auto i = 0; i < _dim; ++i) {
        ans += x[i] * x[i];
    }
    return ans;
}
std::vector<double> Sphere::gradient(const std::vector<double> &x) {
    std::vector<double> ans;
    for (auto i = 0; i < _dim; ++i) {
        ans.push_back(2 * x[i]);
    }
    return ans;
}


double Rastrigin::func_value(const std::vector<double> &x) {
    double ans{ 10. * _dim };
    for (auto i = 0; i < _dim; ++i) {
        ans += x[i] * x[i] - 10 * cos(2 * M_PI * x[i]);
    }
    return ans;
}
std::vector<double> Rastrigin::gradient(const std::vector<double> &x) {
    std::vector<double> ans;
    for (auto i = 0; i < _dim; ++i) {
        ans.push_back(2 * x[i] + 20 * M_PI * sin(2 * M_PI * x[i]));
    }
    return ans;
}

double Booth::func_value(const std::vector<double> &x) {
    return (x[0] + 2 * x[1] - 7) * (x[0] + 2 * x[1] - 7) + (2 * x[0] + x[1] - 5) * (2 * x[0] + x[1] - 5);
}

std::vector<double> Booth::gradient(const std::vector<double> &x) {
    std::vector<double> ans;
    ans.push_back(2 * (x[0] + 2 * x[1] - 7) + 4 * (2 * x[0] + x[1] - 5));
    ans.push_back(4 * (x[0] + 2 * x[1] - 7) + 2 * (2 * x[0] + x[1] - 5));
    return ans;
}


double Matyas::func_value(const std::vector<double> &x) {
    return 0.26 * (x[0] * x[0] + x[1] * x[1]) - 0.48 * x[0] * x[1];
}

std::vector<double> Matyas::gradient(const std::vector<double> &x) {
    std::vector<double> ans;
    ans.push_back(0.26 * 2 * x[0] - 0.48 * x[1]);
    ans.push_back(0.26 * 2 * x[1] - 0.48 * x[0]);
    return ans;
}


double Himmelblau::func_value(const std::vector<double> &x) {
    return (x[0] * x[0] + x[1] - 11) * (x[0] * x[0] + x[1] - 11) + (x[0] + x[1] * x[1] - 7) * (x[0] + x[1] * x[1] - 7);
}

std::vector<double> Himmelblau::gradient(const std::vector<double> &x) {
    std::vector<double> ans;
    ans.push_back(2 * x[0] * (x[0] * x[0] + x[1] - 11) + 2 * (x[0] - x[1] * x[1] - 7));
    ans.push_back(2 * (x[0] * x[0] + x[1] - 11) + 2 * x[1] * (x[0] - x[1] * x[1] - 7));
    return ans;
}

