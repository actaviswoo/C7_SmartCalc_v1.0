#include "s21_credit.h"

// int main() {
// double total_credit_amount = 200000;
// int term = 24;
// double interest_rate = 7.9;
// int type = 2;
// double monthly_payment = 0;
// double overpayment_on_credit = 0;
// double total_payment = 0;
// double diff_monthly_payment_max = 0;
// double diff_monthly_payment_min = 0;
// s21_credit(total_credit_amount, term, interest_rate, type,
//            &monthly_payment, &overpayment_on_credit, &total_payment,
//            &diff_monthly_payment_max, &diff_monthly_payment_min);
// output(monthly_payment, overpayment_on_credit, total_payment,
// diff_monthly_payment_max, diff_monthly_payment_min, type);
// }

void s21_credit(double total_credit_amount, int term, double interest_rate,
                int type, double* monthly_payment,
                double* overpayment_on_credit, double* total_payment,
                double* diff_monthly_payment_max,
                double* diff_monthly_payment_min) {
  interest_rate = interest_rate / 100;
  *monthly_payment = 0;
  *overpayment_on_credit = 0;
  *total_payment = 0;
  *diff_monthly_payment_max = 0;
  *diff_monthly_payment_min = 0;
  if (type == 1) {
    *monthly_payment =
        total_credit_amount *
        (((interest_rate) / (12) * pow(1 + (interest_rate) / (12), term)) /
         (pow(1 + (interest_rate) / (12), term) - 1));
    *overpayment_on_credit = *monthly_payment * term - total_credit_amount;
    *total_payment = total_credit_amount + *overpayment_on_credit;
  } else {
    double principal_dept = total_credit_amount / term;
    double total_interest = 0;
    double loan_balance = total_credit_amount;
    double min_payment_per_month =
        principal_dept + (loan_balance * interest_rate / 12.0);
    double max_payment_per_month =
        total_credit_amount / term + (loan_balance * interest_rate / 12.0);
    for (int i = 0; i < term; i++) {
      double interest = loan_balance * interest_rate / 12.0;
      double payment = principal_dept + interest;
      total_interest += interest;
      loan_balance -= principal_dept;
      if (payment < min_payment_per_month) {
        min_payment_per_month = payment;
      }
      if (payment > max_payment_per_month) {
        max_payment_per_month = payment;
      }
    }
    *diff_monthly_payment_min = min_payment_per_month;
    *diff_monthly_payment_max = max_payment_per_month;
    *overpayment_on_credit = total_interest;
    *total_payment = total_credit_amount + total_interest;
  }
}

// void output(double monthly_payment, double overpayment_on_credit,
//             double total_payment, double diff_monthly_payment_max,
//             double diff_monthly_payment_min, int type) {
//   if (type == 1)
//     printf("Ежемесячный платеж == %lf\n", monthly_payment);
//   else
//     printf("Ежемесячный платеж == %lf..%lf\n", diff_monthly_payment_max,
//            diff_monthly_payment_min);
//   printf("Переплата по кредиту == %lf\n", overpayment_on_credit);
//   printf("Общая выплата == %lf\n", total_payment);
// }
