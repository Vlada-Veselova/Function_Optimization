#ifndef GRADIENTDIALOG_H
#define GRADIENTDIALOG_H

#include <QDialog>
#include"Function.h"
#include"Criteria.h"
#include"Area.h"
#include"Optimization.h"
#include"Gradient.h"
#include"qcustomplot.h"

namespace Ui {
class GradientDialog;
}

class GradientDialog : public QDialog {
    Q_OBJECT
public:
    explicit GradientDialog(Function* func, Area area, double step_size, int n_iter, QWidget *parent = nullptr);
    ~GradientDialog();

private slots:
    void mousePressEvent(QMouseEvent*event);

private:
    Ui::GradientDialog *ui;
    Function *_func;
    double _step_size;
    int _n_iter;
    double _eps;
    int _stop_criteria;
    std::vector<double> _left_bound;
    std::vector<double> _right_bound;
    std::vector<double> _start_point;
};

#endif // GRADIENTDIALOG_H


