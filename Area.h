#pragma once

#include<vector>
#include<cmath>

class Area{
    std::vector<double>_left_bound;
    std::vector<double>_right_bound;
public:
    Area(const std::vector<double>&l, const std::vector<double>&r);
    double GetLeftBound(int i);

    double GetRightBound(int i);
    int size(){
        return _left_bound.size();
    }
};
