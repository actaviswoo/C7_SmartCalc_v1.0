#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QLabel>
#include <QPixmap>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(s21_number()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(s21_number()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(s21_number()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(s21_number()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(s21_number()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(s21_number()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(s21_number()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(s21_number()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(s21_number()));
    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(s21_number()));
    connect(ui->pushButton_left, SIGNAL(clicked()), this, SLOT(s21_number()));
    connect(ui->pushButton_right, SIGNAL(clicked()), this, SLOT(s21_number()));
    connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(s21_number()));

    connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(s21_dot()));

    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(s21_operations()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(s21_operations()));
    connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(s21_operations()));
    connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(s21_operations()));
    connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(s21_operations()));
    connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(s21_operations()));

    connect(ui->pushButton_lg, SIGNAL(clicked()), this, SLOT(s21_function()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(s21_function()));
    connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(s21_function()));
    connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(s21_function()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(s21_function()));
    connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(s21_function()));
    connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(s21_function()));
    connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(s21_function()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(s21_function()));

    connect(ui->pushButton_AC, SIGNAL(clicked()), this, SLOT(s21_delete()));

    connect(ui->pushButton_exit, SIGNAL(clicked()), this, SLOT(s21_delete_one()));

    connect(ui->pushButton_result, SIGNAL(clicked()), this, SLOT(s21_result()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::s21_number() {
  numberflag = 1;
  if (flag == 0) ui->result_text->setText("");
  QPushButton *button = (QPushButton *)sender();

  QString new_label = ui->result_text->text() + button->text();

  ui->result_text->setText(new_label);
  flag = 1;
}

void MainWindow::s21_delete_one() {
    if (ui->result_text->text().size() == 1) {
        ui->result_text->setText("");
    } else {
        ui->result_text->setText(ui->result_text->text().left(ui->result_text->text().size()-1));
    }
}

void MainWindow::s21_dot() {
  if (flag == 0) ui->result_text->setText("");
  if (operation == 1) dot = 0;
  if (!(ui->result_text->text().endsWith('.')) && dot == 0) {
     if (numberflag == 0) ui->result_text->setText(ui->result_text->text() + "0.");
     else ui->result_text->setText(ui->result_text->text() + ".");
     numberflag = 0;
     dot = 1;
  }
  flag = 1;
}


void MainWindow::s21_operations() {
  numberflag = 0;
  operation = 1;
  if (flag == 0) {
      ui->result_text->setText("");
      operation = 1;
  }
  QPushButton *button = (QPushButton *)sender();

  QString new_label;

  new_label = ui->result_text->text();

  if (button->text() == "/" && !(ui->result_text->text().endsWith("/") || ui->result_text->text().endsWith("*") ||
                                 ui->result_text->text().endsWith("-") || ui->result_text->text().endsWith("^") ||
                                 ui->result_text->text().endsWith("mod") || ui->result_text->text().endsWith("+"))) {
    new_label += "/";
  } else if (button->text() == "*" && !(ui->result_text->text().endsWith("/") || ui->result_text->text().endsWith("*") ||
                                        ui->result_text->text().endsWith("-") || ui->result_text->text().endsWith("^") ||
                                        ui->result_text->text().endsWith("mod") || ui->result_text->text().endsWith("+"))) {
    new_label += "*";
  } else if (button->text() == "+" && !(ui->result_text->text().endsWith("/") || ui->result_text->text().endsWith("*") ||
                                        ui->result_text->text().endsWith("-") || ui->result_text->text().endsWith("^") ||
                                        ui->result_text->text().endsWith("mod")|| ui->result_text->text().endsWith("+"))) {
    new_label += "+";
  } else if (button->text() == "-" && !(ui->result_text->text().endsWith("/") || ui->result_text->text().endsWith("*") ||
                                        ui->result_text->text().endsWith("-") || ui->result_text->text().endsWith("^") ||
                                        ui->result_text->text().endsWith("mod")|| ui->result_text->text().endsWith("+"))) {
    new_label += "-";
  } else if (button->text() == "^" && !(ui->result_text->text().endsWith("/") || ui->result_text->text().endsWith("*") ||
                                        ui->result_text->text().endsWith("-") || ui->result_text->text().endsWith("^") ||
                                        ui->result_text->text().endsWith("mod")|| ui->result_text->text().endsWith("+"))) {
    new_label += "^";
  } else if (button->text() == "mod" && !(ui->result_text->text().endsWith("/") || ui->result_text->text().endsWith("*") ||
                                          ui->result_text->text().endsWith("-") || ui->result_text->text().endsWith("^") ||
                                          ui->result_text->text().endsWith("mod")|| ui->result_text->text().endsWith("+"))) {
    new_label += "mod";
  } else if (button->text() == "(") {
    new_label += "(";
  } else if (button->text() == ")") {
    new_label += ")";
  }

  ui->result_text->setText(new_label);
  flag = 1;
}

void MainWindow::s21_result() {
    if (ui->result_text->text().size() == 0) {
        ui->result_text->setText("");
    } else {
        flag = 0;
        operation = 0;
        dot = 0;
        numberflag = 0;
        char *str = new char(ui->result_text->text().length());
        QByteArray barr = ui->result_text->text().toLatin1();
        strncpy(str, barr, ui->result_text->text().length() + 1);
        if (validator(str) == 0) {
        ui->result_text->setText("Invalid input");
        } else if (ui->result_text->text().contains("x")) {
          plotter.draw(str);
          plotter.show();
        } else {
        double result = s21_smartcalc(str, 0.0);
        QString numberResult = QString::number(result);
        ui->result_text->setText(numberResult);
        }
        delete (str);
    }
}


void MainWindow::s21_delete() {
    flag = 1;
    operation = 0;
    dot = 0;
    numberflag = 0;
    ui->result_text->setText("");
}

void MainWindow::s21_function() {
    if (flag == 0) {
        ui->result_text->setText("");
        operation = 1;
    }
    QPushButton *button = (QPushButton *)sender();

    if (button->text() == "sin") {
      ui->result_text->setText(ui->result_text->text() + "sin(");
    } else if (button->text() == "asin") {
      ui->result_text->setText(ui->result_text->text() + "asin(");
    } else if (button->text() == "cos") {
      ui->result_text->setText(ui->result_text->text() + "cos(");
    } else if (button->text() == "acos") {
      ui->result_text->setText(ui->result_text->text() + "acos(");
    } else if (button->text() == "tan") {
      ui->result_text->setText(ui->result_text->text() + "tan(");
    } else if (button->text() == "atan") {
      ui->result_text->setText(ui->result_text->text() + "atan(");
    } else if (button->text() == "ln") {
      ui->result_text->setText(ui->result_text->text() + "ln(");
    } else if (button->text() == "lg") {
      ui->result_text->setText(ui->result_text->text() + "log(");
    } else if (button->text() == "sqrt") {
        ui->result_text->setText(ui->result_text->text() + "sqrt(");
    }
    flag = 1;
}

void MainWindow::on_pushButton_credit_clicked()
{
    credit.show();
}

