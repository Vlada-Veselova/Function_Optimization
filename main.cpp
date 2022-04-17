#include <iostream>
#include "Optimization.h"
#include "gradient.h"
#include "stochastic.h"

using namespace std;

int main()
{
    int dim = 8;
    Function *func = new Sphere(dim);
    Criteria *criteria = new CriteriaSteps;
    std::vector<double> start_point;
    for (auto i = 0; i < dim; ++i) {
        start_point.push_back(5);
    }

    Optimization *opt = new Gradient(func, criteria, start_point);
    opt->SetMaxIterations(1000);
    opt->SetStepSize(0.01);
    std::vector<double> ans = (opt->optimize());
    int n_iter = (opt->GetIterations());
    cout << "N iteration: " << n_iter << "\nMin point: ";
    for (auto i : ans) {
        cout << ans[i] << " ";
    }
    cout << "\nMin value: " << func->func_value(ans);
    cout << "\n";
}
