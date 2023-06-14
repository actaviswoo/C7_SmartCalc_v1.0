#ifndef CREDITWINDOW_H
#define CREDITWINDOW_H

#include <QDialog>
extern "C" {
#include "s21_credit.h"
}

namespace Ui {
class CreditWindow;
}

class CreditWindow : public QDialog {
  Q_OBJECT

 public:
  explicit CreditWindow(QWidget *parent = nullptr);
  ~CreditWindow();

 private slots:
  void on_pushButton_calc_clicked();

  void on_pushButton_AC_clicked();

 private:
  Ui::CreditWindow *ui;
  int type = 1;
};

#endif  // CREDITWINDOW_H
