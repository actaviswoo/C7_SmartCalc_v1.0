#ifndef SRC_S21_CREDIT_H_
#define SRC_S21_CREDIT_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void s21_credit(double total_credit_amount, int term, double interest_rate,
                int type, double* monthly_payment,
                double* overpayment_on_credit, double* total_payment,
                double* diff_monthly_payment_max,
                double* diff_monthly_payment_min);
// void output(double monthly_payment, double overpayment_on_credit,
//             double total_payment, double diff_monthly_payment_max,
//             double diff_monthly_payment_min, int type);

#endif  // SRC_S21_CREDIT_H_
