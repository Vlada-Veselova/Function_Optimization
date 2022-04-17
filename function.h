#pragma once

#include<vector>
#include<math.h>
#define _USE_MATH_DEFINES

class Function{
protected:
    int _dim;
public:
    Function() {};
    virtual double func_value(const std::vector<double> &x) = 0;
    virtual std::vector<double>gradient(const std::vector<double> &x) = 0;
    virtual int GetDim() { return _dim; };
    virtual~Function() {};
};

class Sphere: public Function {
public:
    Sphere(int d) { _dim = d; };
    double func_value(const std::vector<double> &x) override;
    std::vector<double>gradient(const std::vector<double> &x) override;
    ~Sphere() {};
};

class Rastrigin: public Function {
public:
    Rastrigin(int d) { _dim = d; };
    double func_value(const std::vector<double> &x) override;
    std::vector<double>gradient(const std::vector<double> &x) override;
    ~Rastrigin() {};
};

class Booth: public Function {
public:
    Booth() { _dim = 2; };
    double func_value(const std::vector<double> &x) override;
    std::vector<double> gradient(const std::vector<double> &x) override;
    ~Booth() {};
};

class Matyas: public Function {
public:
    Matyas() { _dim = 2; };
    double func_value(const std::vector<double> &x) override;
    std::vector<double> gradient(const std::vector<double> &x) override;
    ~Matyas() {};
};

class Himmelblau: public Function {
public:
    Himmelblau() { _dim = 2; };
    double func_value(const std::vector<double> &x) override;
    std::vector<double> gradient(const std::vector<double> &x) override;
    ~Himmelblau() {};
};
