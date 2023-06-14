#ifndef PLOTTERWINDOW_H
#define PLOTTERWINDOW_H

#include <QMainWindow>
#include <QVector>

namespace Ui {
class PlotterWindow;
}

class PlotterWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit PlotterWindow(QWidget *parent = nullptr);
  ~PlotterWindow();
  void draw(char *temp);

 private slots:
  void on_pushButton_clicked();

 private:
  Ui::PlotterWindow *ui;
  double xBegin, xEnd, h, X;
  int N;
  char temp_str[255];
  QString text_str;
  QVector<double> x, y;
};

#endif  // PLOTTERWINDOW_H
