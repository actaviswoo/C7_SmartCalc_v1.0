#include "creditwindow.h"
#include "ui_creditwindow.h"

extern "C" {
#include "s21_credit.h"
}


CreditWindow::CreditWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreditWindow)
{
    ui->setupUi(this);
}

CreditWindow::~CreditWindow()
{
    delete ui;
}

void CreditWindow::on_pushButton_calc_clicked()
{
    if (ui->comboBox->currentText() == "annuity") {
        type = 1;
    } else if (ui->comboBox->currentText() == "differentiated") {
        type = 0;
    }
    double monthly_payment = 0, overpayment_on_credit = 0, total_payment = 0, diff_monthly_payment_max = 0, diff_monthly_payment_min = 0;
    s21_credit(ui->doubleSpinBox_total_credit_amount->value(), (ui->spinBox_year->value() * 12 + ui->spinBox_month->value()), ui->doubleSpinBox_interest_rate->value(), type, &monthly_payment, &overpayment_on_credit,
               &total_payment, &diff_monthly_payment_max, &diff_monthly_payment_min);
    if (type == 1) {
        QString temp = QString::number(monthly_payment);
        ui->label_monthly_payment->setText("monthly payment: " + temp);
        temp = QString::number(overpayment_on_credit);
        ui->label_overpayment_on_credit->setText("overpayment on credit: " + temp);
        temp = QString::number(total_payment);
        ui->label_total_payment->setText("total payment: " + temp);
    } else {
        QString temp = QString::number(diff_monthly_payment_min);
        QString temp2 = QString::number(diff_monthly_payment_max);
        ui->label_monthly_payment->setText("monthly payment: " + temp + "..." + temp2);
        temp = QString::number(overpayment_on_credit);
        ui->label_overpayment_on_credit->setText("overpayment on credit: " + temp);
        temp = QString::number(total_payment);
        ui->label_total_payment->setText("total payment: " + temp);
    }
}

void CreditWindow::on_pushButton_AC_clicked()
{
    ui->label_monthly_payment->setText("monthly payment: 0");
    ui->label_overpayment_on_credit->setText("overpayment on credit: 0");
    ui->label_total_payment->setText("total payment: 0");
    ui->doubleSpinBox_total_credit_amount->setValue(1000);
    ui->spinBox_year->setValue(0);
    ui->spinBox_month->setValue(1);
    ui->doubleSpinBox_interest_rate->setValue(1);
    ui->comboBox->setCurrentText("annuity");
}

