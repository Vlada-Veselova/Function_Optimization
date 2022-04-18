#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

void MainWindow::on_proceed_clicked() {
    switch(ui->function->currentIndex()){
        case 0: _func = new Himmelblau; break;
    case 1: _func = new Matyas; break;
    case 2: _func = new Sphere(2); break;
        default :_func = new Rastrigin(2); break;
    }
    _step_size = ui->step_size->value();
    _n_iter = ui->max_steps->value();
    std::vector<double>l(2), r(2);
    l[0]=ui->x_left_bound->value();
    l[1]=ui->y_left_bound->value();
    r[0]=ui->x_right_bound->value();
    r[1]=ui->y_right_bound->value();
    Area A(l,r);
    if(!ui->method->currentIndex()){
        GradientDialog D(_func, A, _step_size, _n_iter);
        D.exec();
    }else{
        StochasticDialog D(_func, A, _step_size, _n_iter);
        D.exec();
    }
}
