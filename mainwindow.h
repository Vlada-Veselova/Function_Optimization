#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"Function.h"
#include"Criteria.h"
#include"Area.h"
#include"Optimization.h"
#include"Stochastic.h"
#include"StochasticDialog.h"
#include"GradientDialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() { delete ui; };

private slots:
    void on_proceed_clicked();

private:
    Ui::MainWindow *ui;
    Function* _func;
    double _step_size;
    int _n_iter;

};
#endif // MAINWINDOW_H
