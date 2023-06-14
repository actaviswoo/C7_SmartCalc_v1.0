#include "plotterwindow.h"
#include "ui_plotterwindow.h"

extern "C" {
    #include "s21_smartcalc.h"
}

PlotterWindow::PlotterWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlotterWindow)
{
    ui->setupUi(this);
}

PlotterWindow::~PlotterWindow()
{
    delete ui;
}

void PlotterWindow::draw(char * temp){
    ui->widget->clearGraphs();
    strcpy(temp_str, temp);
    double x_min_num, x_max_num, range_x, range_y;
    x_min_num = ui->doubleSpinBox_1->value();
    x_max_num = ui->doubleSpinBox_2->value();
    range_x = ui->doubleSpinBox_3->value();
    range_y = ui->doubleSpinBox_4->value();
    xBegin = x_min_num;
    xEnd = x_max_num;

    ui->widget->xAxis->setRange(-1 * range_x, range_x);
    ui->widget->yAxis->setRange(-1 * range_y, range_y);

     h = 0.1;

     N = (xEnd - xBegin) / h + 2;

     for (X = xBegin; X < xEnd; X += h) {
       x.push_back(X);
       y.push_back(s21_smartcalc(temp, X));
     }

     ui->widget->addGraph();
     ui->widget->graph(0)->addData(x, y);

     ui->widget->setInteraction(QCP::iRangeZoom, true);
     ui->widget->setInteraction(QCP::iRangeDrag, true);

     ui->widget->replot();

     x.clear();
     y.clear();
}



void PlotterWindow::on_pushButton_clicked()
{
    draw(temp_str);
}
