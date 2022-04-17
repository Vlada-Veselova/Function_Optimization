#include "StochasticDialog.h"
#include "ui_StochasticDialog.h"

StochasticDialog::StochasticDialog(Function *func, Area area, double step_size, int n_iter, QWidget *parent) :
    QDialog(parent), \
    ui(new Ui::StochasticDialog), \
    _step_size(step_size), \
    _n_iter(n_iter) {
    _func = func;
    _left_bound.resize(2);
    _right_bound.resize(2);
    _start_point.resize(2);
    _left_bound[0] = area.GetLeftBound(0);
    _left_bound[1] = area.GetLeftBound(1);
    _right_bound[0] = area.GetRightBound(0);
    _right_bound[1] = area.GetRightBound(1);

    ui->setupUi(this);

    connect(ui->plot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePressEvent(QMouseEvent*)));

    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
    ui->plot->axisRect()->setupFullAxesBox(true);
    ui->plot->xAxis->setLabel("x");
    ui->plot->yAxis->setLabel("y");
    ui->plot->xAxis->setRange(_left_bound[0], _right_bound[0]);
    ui->plot->yAxis->setRange(_left_bound[1], _right_bound[1]);

    // set up the QCPColorMap:
    QCPColorMap *colorMap = new QCPColorMap(ui->plot->xAxis, ui->plot->yAxis);
    int nx = 200;
    int ny = 200;
    colorMap->data()->setSize(nx, ny); // we want the color map to have nx * ny data points
    colorMap->data()->setRange(QCPRange(_left_bound[0], _right_bound[0]), QCPRange(_left_bound[1],_right_bound[1])); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
    //colorMap->data()->setRange(QCPRange(-10,10), QCPRange(-10,10)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
    // now we assign some data, by accessing the QCPColorMapData instance of the color map:
    double x, y, z;
    for (int xIndex=0; xIndex<nx; ++xIndex)
    {
      for (int yIndex=0; yIndex<ny; ++yIndex)
      {
        colorMap->data()->cellToCoord(xIndex, yIndex, &x, &y);
        std::vector<double>point(2);
        point[0] = x;
        point[1] = y;
        z = _func->func_value(point); // the B field strength of dipole radiation (modulo physical constants)
        colorMap->data()->setCell(xIndex, yIndex, z);
      }
    }

    // add a color scale:
    QCPColorScale *colorScale = new QCPColorScale(ui->plot);
//    ui->plot->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect
    colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
    colorMap->setColorScale(colorScale); // associate the color map with the color scale
    colorScale->axis()->setLabel("Function value");

    // set the color gradient of the color map to one of the presets:
    colorMap->setGradient(QCPColorGradient::gpThermal);
    // we could have also created a QCPColorGradient instance and added own colors to
    // the gradient, see the documentation of QCPColorGradient for what's possible.

    // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
    colorMap->rescaleDataRange();

    // make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->plot);
    ui->plot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

    // rescale the key (x) and value (y) axes so the whole color map is visible:
    ui->plot->rescaleAxes();
}

StochasticDialog::~StochasticDialog() {
    delete ui;
}

void StochasticDialog::mousePressEvent(QMouseEvent *event)
{
    QPoint point = event->pos();
    _start_point[0]=ui->plot->xAxis->pixelToCoord(event->x());
    _start_point[1]=ui->plot->yAxis->pixelToCoord(event->y());

    _bernoulli_param = ui->prob->value();
    _delta=ui->delt->value();
    Area *A = new Area(_left_bound,_right_bound);
    _start_point.resize(2);
    Criteria *C = new CriteriaSteps;

    double eps = 0;
    Stochastic *opt = new Stochastic(_func, A, C, _start_point);
    opt->SetBernoulliParam(_bernoulli_param);
    opt->SetDelta(_delta);
    opt->SetEps(eps);
    opt->SetStepSize(_step_size);
    opt->SetMaxIterations(_n_iter);
    if((_start_point[0]<_left_bound[0]) ||
            (_start_point[1]<_left_bound[1]) || \
            (_start_point[0]>_right_bound[0]) || \
            (_start_point[1]>_right_bound[1])) {
        delete A;
        return;
    }
    std::vector<double> xp(opt->optimize());
    std::list<std::vector<double>> trajectory = opt->GetTrajectory();
    double fx(_func->func_value(xp));
    ui->x->setText(QString::number(xp[0]));
    ui->y->setText(QString::number(xp[1]));
    ui->f->setText(QString::number(fx));
    ui->k->setText(QString::number(_n_iter));

    ui->plot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
    ui->plot->axisRect()->setupFullAxesBox(true);
    ui->plot->xAxis->setLabel("x");
    ui->plot->yAxis->setLabel("y");
    ui->plot->xAxis->setRange(_left_bound[0],_right_bound[0]);
    ui->plot->yAxis->setRange(_left_bound[1],_right_bound[1]);

    // set up the QCPColorMap:
    QCPColorMap *colorMap = new QCPColorMap(ui->plot->xAxis, ui->plot->yAxis);
    int nx = 200;
    int ny = 200;
    colorMap->data()->setSize(nx, ny); // we want the color map to have nx * ny data points
    colorMap->data()->setRange(QCPRange(_left_bound[0],_right_bound[0]), QCPRange(_left_bound[1],_right_bound[1])); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
    //colorMap->data()->setRange(QCPRange(-10,10), QCPRange(-10,10)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
    // now we assign some data, by accessing the QCPColorMapData instance of the color map:
    double x, y, z;
    for (int xIndex=0; xIndex<nx; ++xIndex)
    {
      for (int yIndex=0; yIndex<ny; ++yIndex)
      {
        colorMap->data()->cellToCoord(xIndex, yIndex, &x, &y);
        std::vector<double>point(2);
        point[0]=x;
        point[1]=y;
        z = _func->func_value(point); // the B field strength of dipole radiation (modulo physical constants)
        colorMap->data()->setCell(xIndex, yIndex, z);
      }
    }

    // add a color scale:
    QCPColorScale *colorScale = new QCPColorScale(ui->plot);
    colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
    colorMap->setColorScale(colorScale); // associate the color map with the color scale
//    colorScale->axis()->setLabel("Function value");

    // set the color gradient of the color map to one of the presets:
    colorMap->setGradient(QCPColorGradient::gpThermal);
    // we could have also created a QCPColorGradient instance and added own colors to
    // the gradient, see the documentation of QCPColorGradient for what's possible.

    // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
    colorMap->rescaleDataRange();

    // make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->plot);
    ui->plot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

    QCPCurve*tr_curve=new QCPCurve(ui->plot->xAxis, ui->plot->yAxis);
    tr_curve->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 3));
    tr_curve->setPen(QPen(Qt::white));

    int i(0);
    for(auto it = trajectory.begin(); it != trajectory.end(); ++it)
        tr_curve->addData(i++, (*it)[0], (*it)[1]);
    ui->plot->rescaleAxes();
    ui->plot->replot();

    delete C;
    delete opt;
    delete A;
}
