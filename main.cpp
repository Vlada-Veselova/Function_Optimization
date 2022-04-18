#include <iostream>
#include "Optimization.h"
#include "gradient.h"
#include "stochastic.h"

int main() {
    int dim;
    int func_number;
    int criteria_number;
    int method_number;
    std::vector<double> start_point;
    Criteria *criteria;
    Function *func;
    Optimization *opt;
    std::cout << "Choose function\nTo choose Sphere press 1\nTo choose Matyas function press 2\nTo choose Booth function press 3\n";
    std::cin >> func_number;
    switch(func_number) {
    case 1: std::cout << "Enter the dimention [1, 10]\n";
        std::cin >> dim;
        if (dim > 10 || dim < 1) {
            std::cout << "Wrong number. Optimization of the Sphere of dimention 3\n";
            dim = 3;
        }
        func = new Sphere(dim);
        break;
    case 2: func = new Matyas;
        dim = 2;
        break;
    case 3: func = new Booth;
        dim = 2;
        break;
    default:
        std::cout << "Wrong number. Optimization of the Sphere of dimention 3\n";
        dim = 3;
        func = new Sphere(dim);
        break;
    }

    std::cout << "Choose stop criteria\nTo choose stop by steps press 1\nTo choose stop by value press 2\nTo choose stop by gradient press 3\n";
    std::cin >> criteria_number;
    switch(criteria_number) {
    case 1: criteria = new CriteriaSteps;
        break;
    case 2: criteria = new CriteriaValue;
        break;
    case 3: criteria = new CriteriaGradient;
        break;
    default:
        std::cout << "Wrong number. Optimization with stop by the Gradient value\n";
        criteria = new CriteriaGradient;
        break;
    }
    double tmp;
    std::cout << "Enter the start point. Each of the coordinates must be from the interval [-10, 10]\n";
    for (auto i = 0; i < dim; ++i){
        std::cin >> tmp;
        if (tmp > 10 || tmp < -10) {
            std::cout << "Wrong number. The coordinate changed to 1\n";
            tmp = 1;
        }
        start_point.push_back(tmp);
    }
    std::cout << "Choose the method\nTo choose Gradient Descent press 1\nTo choose Stochastic method press 2\n";
    std::cin >> method_number;
    switch(method_number) {
    case 1: opt = new Gradient(func, criteria, start_point);
        break;
    case 2: opt = new Stochastic(func, criteria, start_point);
        break;
    default:
        std::cout << "Wrong number. Optimization by Gradient Descent\n";
        opt = new Gradient(func, criteria, start_point);
        break;
    }
    opt->SetMaxIterations(1000);
    opt->SetStepSize(0.01);
    std::vector<double> ans = (opt->optimize());
    int n_iter = (opt->GetIterations());
    std::cout << "N iteration: " << n_iter << "\nMin point: ";
    for (auto i : ans) {
        std::cout << i << " ";
    }
    std::cout << "\nMin value: " << func->func_value(ans);
    std::cout << "\n";
}
