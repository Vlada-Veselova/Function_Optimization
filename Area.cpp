#include"Area.h"

Area::Area(const std::vector<double> &l,const std::vector<double> &r){
    if(l.size() != r.size())
        return;
    _left_bound = l;
    _right_bound = r;
}
double Area::GetLeftBound(int i){
    if(!_left_bound.size())
        return std::nan("");
    return _left_bound.at(i);
}
double Area::GetRightBound(int i){
    if(!_right_bound.size())
        return std::nan("");
    return _right_bound.at(i);
}
