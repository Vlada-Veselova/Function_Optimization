#ifndef STOCHASTICDIALOG_H
#define STOCHASTICDIALOG_H

#include <QDialog>
#include"Function.h"
#include"Criteria.h"
#include"Area.h"
#include"Optimization.h"
#include"Stochastic.h"
#include"qcustomplot.h"

namespace Ui {
class StochasticDialog;
}

class StochasticDialog : public QDialog {
    Q_OBJECT
public:
    explicit StochasticDialog(Function* func, Area area, double step_size, int n_iter, QWidget *parent = nullptr);
    ~StochasticDialog();

private slots:
    void mousePressEvent(QMouseEvent*event);

private:
    Ui::StochasticDialog *ui;
    Function *_func;
    double _step_size;
    int _n_iter;
    std::vector<double> _left_bound;
    std::vector<double> _right_bound;
    std::vector<double> _start_point;
    double _bernoulli_param;
    double _delta;
};

#endif // STOCHASTICDIALOG_H
