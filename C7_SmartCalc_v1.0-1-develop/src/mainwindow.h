#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "creditwindow.h"
#include "plotterwindow.h"

extern "C" {
#include "s21_smartcalc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void s21_number();
  void s21_operations();
  void s21_result();
  void s21_delete();
  void s21_dot();
  void s21_function();
  void s21_delete_one();

  void on_pushButton_credit_clicked();

 private:
  Ui::MainWindow *ui;
  int flag = 1;
  int operation = 0;
  int dot = 0;
  int numberflag = 0;
  CreditWindow credit;
  PlotterWindow plotter;
};
#endif  // MAINWINDOW_H
