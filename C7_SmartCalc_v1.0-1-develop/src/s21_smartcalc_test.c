#include "s21_smartcalc.h"

#include <check.h>
#include <time.h>
#include <unistd.h>

#include "s21_credit.h"

START_TEST(s21_test_0) {
  double x = 0;
  double orig = 10;

  char str[255] = "5+5";
  x = s21_smartcalc(str, 0);
  ck_assert_double_eq(x, orig);
}
END_TEST

START_TEST(s21_test_1) {
  double x = 0;
  double orig = 162;
  // int error = 0;

  char str[255] = "4*5*2*2*2+2";
  x = s21_smartcalc(str, 0);
  ck_assert_double_eq(x, orig);
}
END_TEST

START_TEST(s21_test_2) {
  double x = 0;
  double orig = 20;
  // int error = 0;

  char str[255] = "150/10+5*2/2";
  x = s21_smartcalc(str, 0);
  ck_assert_double_eq(x, orig);
}
END_TEST

START_TEST(s21_test_3) {
  double x = 0;
  double orig = 9;
  // int error = 0;

  char str[255] = "5+5-2*3/6";
  x = s21_smartcalc(str, 0);
  ck_assert_double_eq(x, orig);
}
END_TEST

START_TEST(calc_test) {
  char str[100] = "4^acos(x/4)/tan(2*x)";
  double result = s21_smartcalc(str, 1.2);
  double real_result = -6.31492;
  ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test-2 failed");
}
END_TEST
START_TEST(calc_test1) {
  char str[100] = "x+x";

  double result = s21_smartcalc(str, 2);
  double real_result = 4;
  ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test-2 failed");
}
END_TEST
START_TEST(calc_test2) {
  char str[100] = "123+0.456";
  double result = s21_smartcalc(str, 0);
  double real_result = 123.456;
  ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test-3 failed");
}
END_TEST

END_TEST
START_TEST(calc_test4) {
  char str[100] = "cos(10mod2.2)";
  double result = s21_smartcalc(str, 0);
  double real_result = 0.362358;
  ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test-6 failed");
}
END_TEST
START_TEST(calc_test5) {
  char str[100] = "sqrt(ln(10))";
  double result = s21_smartcalc(str, 0);
  double real_result = 1.517427;
  ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test-7 failed");
}
END_TEST
START_TEST(calc_test6) {
  char str[100] = "atan(10)+sin(10)";
  double result = s21_smartcalc(str, 0);
  double real_result = 1.644775;
  ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test-8 failed");
}
END_TEST
START_TEST(calc_test7) {
  char str[100] = "asin(1)";
  double result = s21_smartcalc(str, 0);
  double real_result = 1.570796;
  ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test-9 failed");
}
END_TEST
START_TEST(calc_test8) {
  char str[100] = "10-20*(-10)";
  double result = s21_smartcalc(str, 0);
  double real_result = -210;
  ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test-10 failed");
}
END_TEST

START_TEST(calc_test10) {
  char str[100] = "-(o(i(a(10.01)*n(2))/10m(2))^q(5)";
  int result = validator(str);
  ck_assert_msg(!result, "test-10 failed");
}
END_TEST
START_TEST(calc_test11) {
  char str[100] = "mod+9(()))";
  int result = validator(str);
  ck_assert_msg(!result, "test-10 failed");
}
END_TEST
START_TEST(calc_test12) {
  char str[100] = "md(+9(()))";
  int result = validator(str);
  ck_assert_msg(!result, "test-10 failed");
}
END_TEST
START_TEST(calc_test13) {
  char str[100] = "-(o(i(a(10.01)*n(2))/10md+(2))^q(5)";
  int result = validator(str);
  ck_assert_msg(!result, "test-10 failed");
}
END_TEST
START_TEST(calc_test14) {
  char str[100] = ")(s(x)";
  int result = validator(str);
  ck_assert_msg(!result, "test-10 failed");
}
END_TEST
START_TEST(calc_test15) {
  char str[100] = ".+m)";
  int result = validator(str);
  ck_assert_msg(!result, "test-10 failed");
}

END_TEST
START_TEST(s21_test_4) {
  double x = 0;
  double orig = 69;
  // int error = 0;

  char str[255] = "2+(5*5*5+5+2*2)/(2)";

  x = s21_smartcalc(str, 0);
  ck_assert_double_eq(x, orig);
}
END_TEST

START_TEST(s21_test_5) {
  double x = 0;
  double orig = 11.958851;
  // int error = 0;

  char str[255] = "5+(3+sin(8/2-3.5))*2";

  x = s21_smartcalc(str, 0);
  ck_assert_double_eq_tol(x, orig, 1e-7);
}
END_TEST

START_TEST(s21_test_6) {
  char *str = "24*4-3*2";
  double orig = 90;
  double value = s21_smartcalc(str, 0);

  ck_assert_int_eq(value, orig);
}
END_TEST

START_TEST(s21_test_7) {
  double orig = 4;
  char *str = "2-(-2)";

  double value = s21_smartcalc(str, 0);

  ck_assert_int_eq(value, orig);
}
END_TEST

START_TEST(s21_test_8) {
  double orig = -0.41211848524;
  char *str = "-sin(9)";

  double value = s21_smartcalc(str, 0);

  ck_assert_int_eq(value, orig);
}
END_TEST
START_TEST(s21_test_9) {
  double orig = 2.41211848524;
  char *str = "sin(9)-(-2)";

  double value = s21_smartcalc(str, 0);

  ck_assert_int_eq(value, orig);
}
END_TEST
START_TEST(s21_test_10) {
  double orig = 0.91113026188;
  char *str = "-cos(9)";

  double value = s21_smartcalc(str, 0);

  ck_assert_int_eq(value, orig);
}
END_TEST
START_TEST(plus_t) {
  double my = s21_smartcalc("(-2)+2", 0);
  ck_assert_float_eq(my, 0);
}
END_TEST

START_TEST(minus_t) {
  double my = s21_smartcalc("(-2.2)-2.2", 0);
  ck_assert_float_eq(my, -4.4);
}
END_TEST

START_TEST(mult_t) {
  double my = s21_smartcalc("(-2.2)*(+2.2)", 0);
  ck_assert_float_eq(my, -4.84);
}
END_TEST

START_TEST(division_t) {
  double my = s21_smartcalc("(-2.2)/2.2", 0);
  ck_assert_float_eq(my, -1);
}
END_TEST

START_TEST(degr_t) {
  double my = s21_smartcalc("(2.2)^(-2.2)", 0);
  ck_assert_double_eq_tol(my, 0.17647, 0.17647);
}
END_TEST

START_TEST(sin_t) {
  double my = s21_smartcalc("sin(+2)", 0);
  ck_assert_double_eq(my, sin(2));
}
END_TEST

START_TEST(cos_t) {
  long double my = s21_smartcalc("cos(2)", 0);
  ck_assert_double_eq_tol(my, cos(2), 1e-7);
}
END_TEST

START_TEST(tan_t) {
  long double my = s21_smartcalc("tan(2)", 0);
  ck_assert_ldouble_eq(my, tan(2));
}
END_TEST

START_TEST(asin_t) {
  long double my = s21_smartcalc("asin(1)", 0);
  ck_assert_ldouble_eq(my, asin(1));
}
END_TEST

START_TEST(acos_t) {
  long double my = s21_smartcalc("acos(1)", 0);
  ck_assert_ldouble_eq(my, acos(1));
}
END_TEST

START_TEST(atan_t) {
  long double my = s21_smartcalc("atan(1)", 0);
  ck_assert_ldouble_eq(my, atan(1));
}
END_TEST

START_TEST(ln_t) {
  long double my = s21_smartcalc("log(1)", 0);
  ck_assert_ldouble_eq(my, log(1));
}
END_TEST

START_TEST(log_t) {
  long double my = s21_smartcalc("log(1)", 0);
  ck_assert_ldouble_eq(my, log10(1));
}
END_TEST

START_TEST(sqrt_t) {
  long double my = s21_smartcalc("sqrt(1)", 0);
  ck_assert_ldouble_eq(my, sqrt(1));
}
END_TEST

START_TEST(mod_t) {
  long double my = s21_smartcalc("4mod8", 0);
  ck_assert_ldouble_eq(my, 4);
}
END_TEST

START_TEST(test_1) {
  char *str = "+10";
  double x = 0;
  double result = s21_smartcalc(str, x);

  ck_assert_ldouble_eq(result, 10);
}
END_TEST
START_TEST(test_2) {
  char *str = "-10";
  double x = 0;
  double result = s21_smartcalc(str, x);

  ck_assert_ldouble_eq(result, -10);
}
END_TEST
START_TEST(test_3) {
  char *str = "*10";
  double result = validator(str);
  ck_assert_msg(!result, "test3 failed");
}
END_TEST
START_TEST(test_4) {
  char *str = "/10";
  double x = 0;
  double result = s21_smartcalc(str, x);
  ck_assert_msg(!result, "test4 failed");
}
END_TEST
START_TEST(test_5) {
  char *str = "mod10";
  double x = 0;
  double result = s21_smartcalc(str, x);
  ck_assert_msg(!result, "test5 failed");
}
END_TEST
START_TEST(test_6) {
  char *str = "^10";
  double x = 0;
  double result = s21_smartcalc(str, x);
  ck_assert_msg(!result, "test6 failed");
}
END_TEST
START_TEST(test_7) {
  char *str = "log(log(10))";
  double x = 0;
  double result = s21_smartcalc(str, x);
  double real_result = 0;
  ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test7 failed");
}
END_TEST
START_TEST(test_8) {
  char *str = "sin(sin(-10))";
  double x = 0;
  double real_result = 0.51758076746;
  double result = s21_smartcalc(str, x);
  ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test8 failed");
}
END_TEST
START_TEST(test_9) {
  char *str = "cos(-cos(10))";
  double x = 0;
  double real_result = 0.66815391753;
  double result = s21_smartcalc(str, x);
  ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test9 failed");
}
END_TEST
START_TEST(test_10) {
  char *str = "-cos(cos(10))";
  double x = 0;
  double real_result = -0.66815391753;
  double result = s21_smartcalc(str, x);
  ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test10 failed");
}
END_TEST
START_TEST(test_11) {
  char *str = "-cos(-cos(10))";
  double x = 0;
  double real_result = -0.66815391753;
  double result = s21_smartcalc(str, x);
  ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test11 failed");
}
END_TEST
START_TEST(test_12) {
  char *str = "tan(--tan(10)+tan(10))";
  double result = validator(str);
  ck_assert_msg(!result, "test12 failed");
}
END_TEST
START_TEST(test_13) {
  char *str = "log(mod10)";
  double result = validator(str);
  ck_assert_msg(!result, "test13 failed");
}
END_TEST
START_TEST(test_14) {
  char *str = "sin(0.3)";
  double x = 0;
  double real_result = 0.29552020666;
  double result = s21_smartcalc(str, x);
  ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test14 failed");
}
END_TEST
START_TEST(test_15) {
  char *str = "cos(cos(10)))";
  double result = validator(str);
  ck_assert_msg(!result, "test15 failed");
}
END_TEST
START_TEST(test_16) {
  char *str = "cos(cos(10*))";
  double result = validator(str);
  ck_assert_msg(!result, "test16 failed");
}
END_TEST
START_TEST(test_17) {
  char *str = "cos(-cos(*10))";
  double result = validator(str);
  ck_assert_msg(!result, "test17 failed");
}
END_TEST
START_TEST(test_18) {
  char *str = "tan(--tan(10)+tan(10))";
  double result = validator(str);
  ck_assert_msg(!result, "test18 failed");
}
END_TEST
START_TEST(test_19) {
  char *str = "log(ln(50))";
  double x = 0;
  double real_result = 0.59240140007;
  double result = s21_smartcalc(str, x);
  ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test19 failed");
}
END_TEST
START_TEST(test_20) {
  char *str = "log(1mod10)";
  double x = 0;
  double real_result = 0;
  double result = s21_smartcalc(str, x);
  ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test20 failed");
}
END_TEST
START_TEST(test_21) {
  char *str = "sin(-12*cos(32))";
  double x = 0;
  double real_result = 0.55295147027;
  double result = s21_smartcalc(str, x);
  ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test21 failed");
}
END_TEST
START_TEST(test_22) {
  char *str = "acos(-acos(10))";
  double x = 0;
  double real_result = NAN;
  double result = s21_smartcalc(str, x);
  ck_assert_msg(result != result && real_result != real_result,
                "test-22 failed");
}
END_TEST
START_TEST(test_23) {
  char *str = "-acos(*acos(10))";
  double result = validator(str);
  ck_assert_msg(!result, "test23 failed");
}
END_TEST
START_TEST(test_24) {
  char *str = "ln(*ln(2))*5";
  double result = validator(str);
  ck_assert_msg(!result, "test18 failed");
}
END_TEST
START_TEST(test_25) {
  char *str = "ln(ln(2))";
  double x = 0;
  double real_result = -0.36651292058;
  double result = s21_smartcalc(str, x);
  ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test25 failed");
}
END_TEST
START_TEST(test_26) {
  char *str = "-log(1mod10)";
  double x = 0;
  double real_result = 0;
  double result = s21_smartcalc(str, x);
  ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test26 failed");
}
END_TEST
START_TEST(test_27) {
  char *str = "-sin(-12*cos(32))";
  double x = 0;
  double real_result = -0.55295147027;
  double result = s21_smartcalc(str, x);
  ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test27 failed");
}
END_TEST
START_TEST(test_28) {
  char *str = "-acos(-acos(10))";
  double x = 0;
  double real_result = NAN;
  double result = s21_smartcalc(str, x);
  ck_assert_msg(result != result && real_result != real_result,
                "test-28 failed");
}
END_TEST
START_TEST(test_29) {
  char *str = "acos(*acos(10))";
  double result = validator(str);
  ck_assert_msg(!result, "test29 failed");
}
END_TEST
START_TEST(test_30) {
  char *str = "-ln(*ln(2))*5";
  double result = validator(str);
  ck_assert_msg(!result, "test30 failed");
}
END_TEST
START_TEST(test_31) {
  char *str = "-ln(-ln(2))";
  double x = 0;
  double real_result = NAN;
  double result = s21_smartcalc(str, x);
  ck_assert_msg(result != result && real_result != real_result,
                "test31 failed");
}
END_TEST
START_TEST(test_32) {
  char *str = "ln(ln(x))";
  double x = 16;
  double real_result = 1.01978144054;
  double result = s21_smartcalc(str, x);
  ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test27 failed");
}
END_TEST
START_TEST(test_33) {
  char *str = "ln(*ln(x))*x";
  double result = validator(str);
  ck_assert_msg(!result, "test33 failed");
}
END_TEST
START_TEST(test_34) {
  char *str = "-acos(*acos(x))";
  double result = validator(str);
  ck_assert_msg(!result, "test34 failed");
}
END_TEST
START_TEST(test_35) {
  char *str = "acos(-acos(x))";
  double x = 1;
  double real_result = 1.570796;
  double result = s21_smartcalc(str, x);
  ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test35 failed");
}
END_TEST
START_TEST(test_36) {
  char *str = "sin(-x*cos(x))";
  double x = 17;
  double real_result = -0.99940105644;
  double result = s21_smartcalc(str, x);
  ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test36 failed");
}
END_TEST
START_TEST(test_37) {
  char *str = "log(50mod14)";
  double x = 1;
  double real_result = 0.90308998699;
  double result = s21_smartcalc(str, x);
  ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test37 failed");
}
END_TEST
START_TEST(test_38) {
  char *str = "1+1-1+ln(234)modln(log(12))";
  double x = 0;
  double real_result = 1.04493309902;
  double result = s21_smartcalc(str, x);
  ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test38 failed");
}
END_TEST
START_TEST(test_39) {
  char *str = "log(log(10))";
  double x = 0;
  double real_result = 0;
  double result = s21_smartcalc(str, x);
  ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test39 failed");
}
END_TEST
START_TEST(test_40) {
  char *str = "(421+3.2)-32*cos(32)/3^4";
  double x = 0;
  double real_result = 423.870430277;
  double result = s21_smartcalc(str, x);
  ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test40 failed");
}
END_TEST
START_TEST(test_41) {
  char *str = "cos(xmodx)";
  double x = 10;
  double real_result = 1;
  double result = s21_smartcalc(str, x);
  ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test41 failed");
}
END_TEST
START_TEST(test_42) {
  char *str = "1modcos(3)";
  double x = 0;
  double real_result = -0.9799849932;
  double result = s21_smartcalc(str, x);
  ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test42 failed");
}
END_TEST
START_TEST(test_43) {
  char *str = "-cos(3)^4";
  double x = 0;
  double real_result = -0.96056688816;
  double result = s21_smartcalc(str, x);
  ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test43 failed");
}
END_TEST
START_TEST(test_44) {
  char *str = "1^0";
  double x = 0;
  double real_result = 1;
  double result = s21_smartcalc(str, x);
  ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test43 failed");
}
END_TEST

START_TEST(credit_1) {
  double total_credit_amount = 200000;
  int term = 24;
  double interest_rate = 7.9;
  int type = 1;
  double monthly_payment = 0;
  double overpayment_on_credit = 0;
  double total_payment = 0;
  double diff_monthly_payment_max = 0;
  double diff_monthly_payment_min = 0;
  s21_credit(total_credit_amount, term, interest_rate, type, &monthly_payment,
             &overpayment_on_credit, &total_payment, &diff_monthly_payment_max,
             &diff_monthly_payment_min);
  double real_result = 9036.34;
  ck_assert_msg(fabs(monthly_payment) - fabs(real_result) <= 0.00001,
                "credit1 failed");
}
END_TEST

START_TEST(credit_2) {
  double total_credit_amount = 200000;
  int term = 24;
  double interest_rate = 7.9;
  int type = 1;
  double monthly_payment = 0;
  double overpayment_on_credit = 0;
  double total_payment = 0;
  double diff_monthly_payment_max = 0;
  double diff_monthly_payment_min = 0;
  s21_credit(total_credit_amount, term, interest_rate, type, &monthly_payment,
             &overpayment_on_credit, &total_payment, &diff_monthly_payment_max,
             &diff_monthly_payment_min);
  double real_result = 16872.16;
  ck_assert_msg(fabs(overpayment_on_credit) - fabs(real_result) <= 0.00001,
                "credit2 failed");
}
END_TEST

START_TEST(credit_3) {
  double total_credit_amount = 200000;
  int term = 24;
  double interest_rate = 7.9;
  int type = 1;
  double monthly_payment = 0;
  double overpayment_on_credit = 0;
  double total_payment = 0;
  double diff_monthly_payment_max = 0;
  double diff_monthly_payment_min = 0;
  s21_credit(total_credit_amount, term, interest_rate, type, &monthly_payment,
             &overpayment_on_credit, &total_payment, &diff_monthly_payment_max,
             &diff_monthly_payment_min);
  double real_result = 216872.16;
  ck_assert_msg(fabs(total_payment) - fabs(real_result) <= 0.00001,
                "credit3 failed");
}
END_TEST

START_TEST(credit_4) {
  double total_credit_amount = 200000;
  int term = 24;
  double interest_rate = 7.9;
  int type = 2;
  double monthly_payment = 0;
  double overpayment_on_credit = 0;
  double total_payment = 0;
  double diff_monthly_payment_max = 0;
  double diff_monthly_payment_min = 0;
  s21_credit(total_credit_amount, term, interest_rate, type, &monthly_payment,
             &overpayment_on_credit, &total_payment, &diff_monthly_payment_max,
             &diff_monthly_payment_min);
  double real_result = 9650.00;
  ck_assert_msg(fabs(diff_monthly_payment_max) - fabs(real_result) <= 0.00001,
                "credit4 failed");
}
END_TEST

START_TEST(credit_5) {
  double total_credit_amount = 200000;
  int term = 24;
  double interest_rate = 7.9;
  int type = 2;
  double monthly_payment = 0;
  double overpayment_on_credit = 0;
  double total_payment = 0;
  double diff_monthly_payment_max = 0;
  double diff_monthly_payment_min = 0;
  s21_credit(total_credit_amount, term, interest_rate, type, &monthly_payment,
             &overpayment_on_credit, &total_payment, &diff_monthly_payment_max,
             &diff_monthly_payment_min);
  double real_result = 8388.194444;
  ck_assert_msg(fabs(diff_monthly_payment_min) - fabs(real_result) <= 0.00001,
                "credit5 failed");
}
END_TEST

START_TEST(credit_6) {
  double total_credit_amount = 200000;
  int term = 24;
  double interest_rate = 7.9;
  int type = 2;
  double monthly_payment = 0;
  double overpayment_on_credit = 0;
  double total_payment = 0;
  double diff_monthly_payment_max = 0;
  double diff_monthly_payment_min = 0;
  s21_credit(total_credit_amount, term, interest_rate, type, &monthly_payment,
             &overpayment_on_credit, &total_payment, &diff_monthly_payment_max,
             &diff_monthly_payment_min);
  double real_result = 16458.333333;
  ck_assert_msg(fabs(overpayment_on_credit) - fabs(real_result) <= 0.00001,
                "credit6 failed");
}
END_TEST

START_TEST(credit_7) {
  double total_credit_amount = 200000;
  int term = 24;
  double interest_rate = 7.9;
  int type = 2;
  double monthly_payment = 0;
  double overpayment_on_credit = 0;
  double total_payment = 0;
  double diff_monthly_payment_max = 0;
  double diff_monthly_payment_min = 0;
  s21_credit(total_credit_amount, term, interest_rate, type, &monthly_payment,
             &overpayment_on_credit, &total_payment, &diff_monthly_payment_max,
             &diff_monthly_payment_min);
  double real_result = 216458.333333;
  ck_assert_msg(fabs(total_payment) - fabs(real_result) <= 0.00001,
                "credit7 failed");
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc);
  tcase_add_test(tc, s21_test_0);
  tcase_add_test(tc, s21_test_1);
  tcase_add_test(tc, s21_test_2);
  tcase_add_test(tc, s21_test_3);
  tcase_add_test(tc, calc_test);
  tcase_add_test(tc, calc_test1);
  tcase_add_test(tc, calc_test2);
  tcase_add_test(tc, calc_test4);
  tcase_add_test(tc, calc_test5);
  tcase_add_test(tc, calc_test6);
  tcase_add_test(tc, calc_test7);
  tcase_add_test(tc, calc_test8);
  tcase_add_test(tc, calc_test10);
  tcase_add_test(tc, calc_test11);
  tcase_add_test(tc, calc_test12);
  tcase_add_test(tc, calc_test13);
  tcase_add_test(tc, calc_test14);
  tcase_add_test(tc, calc_test15);
  tcase_add_test(tc, s21_test_4);
  tcase_add_test(tc, s21_test_5);
  tcase_add_test(tc, s21_test_6);
  tcase_add_test(tc, s21_test_7);
  tcase_add_test(tc, s21_test_8);
  tcase_add_test(tc, s21_test_9);
  tcase_add_test(tc, s21_test_10);

  tcase_add_test(tc, plus_t);
  tcase_add_test(tc, minus_t);
  tcase_add_test(tc, division_t);
  tcase_add_test(tc, mult_t);
  tcase_add_test(tc, degr_t);
  tcase_add_test(tc, sin_t);
  tcase_add_test(tc, cos_t);
  tcase_add_test(tc, tan_t);
  tcase_add_test(tc, asin_t);
  tcase_add_test(tc, acos_t);
  tcase_add_test(tc, atan_t);
  tcase_add_test(tc, ln_t);
  tcase_add_test(tc, log_t);
  tcase_add_test(tc, sqrt_t);
  tcase_add_test(tc, mod_t);

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);
  tcase_add_test(tc, test_5);
  tcase_add_test(tc, test_6);
  tcase_add_test(tc, test_7);
  tcase_add_test(tc, test_8);
  tcase_add_test(tc, test_9);
  tcase_add_test(tc, test_10);
  tcase_add_test(tc, test_11);
  tcase_add_test(tc, test_12);
  tcase_add_test(tc, test_13);
  tcase_add_test(tc, test_14);
  tcase_add_test(tc, test_15);
  tcase_add_test(tc, test_16);
  tcase_add_test(tc, test_17);
  tcase_add_test(tc, test_18);
  tcase_add_test(tc, test_19);
  tcase_add_test(tc, test_20);
  tcase_add_test(tc, test_21);
  tcase_add_test(tc, test_22);
  tcase_add_test(tc, test_23);
  tcase_add_test(tc, test_24);
  tcase_add_test(tc, test_25);
  tcase_add_test(tc, test_26);
  tcase_add_test(tc, test_27);
  tcase_add_test(tc, test_28);
  tcase_add_test(tc, test_29);
  tcase_add_test(tc, test_30);
  tcase_add_test(tc, test_31);
  tcase_add_test(tc, test_32);
  tcase_add_test(tc, test_33);
  tcase_add_test(tc, test_34);
  tcase_add_test(tc, test_35);
  tcase_add_test(tc, test_36);
  tcase_add_test(tc, test_37);
  tcase_add_test(tc, test_38);
  tcase_add_test(tc, test_39);
  tcase_add_test(tc, test_40);
  tcase_add_test(tc, test_41);
  tcase_add_test(tc, test_42);
  tcase_add_test(tc, test_43);
  tcase_add_test(tc, test_44);

  tcase_add_test(tc, credit_1);
  tcase_add_test(tc, credit_2);
  tcase_add_test(tc, credit_3);
  tcase_add_test(tc, credit_4);
  tcase_add_test(tc, credit_5);
  tcase_add_test(tc, credit_6);
  tcase_add_test(tc, credit_7);

  // srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
