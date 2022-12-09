#include "s21_smartcalc.h"

#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define STKDPTH 300 /* Глубина стека */

START_TEST(test_transfer) {
  char str[STKDPTH];
  double val = 123.1234567889;
  transfer(&val, str);
  ck_assert_str_eq(str, "123.12");
}
END_TEST

START_TEST(test_alg_01) {
  char str[STKDPTH];
  strncpy(str, "-sin(2+3*1.55)", STKDPTH - 1);
  algoritm_d(str);
  ck_assert_str_eq(str, "2 3 1.55 * + s M ");
}
END_TEST

START_TEST(test_sin) {
  char str[STKDPTH];
  strncpy(str, "-sin(-2-3*1.55)", STKDPTH - 1);
  algoritm_d(str);
  //   printf("%s\n", str);
  double end = 0;
  operand(str, &end, 0);
  double b = -2 - 3 * 1.55;
  double a = -sin(b);
  //   printf("b %.28f\ntest_sin %.8f\ntest_sin %.8f\n", b, rez, a);
  ck_assert_ldouble_eq_tol(end, a, ESP);
}
END_TEST

START_TEST(test_asin) {
  //   printf("\033[0d\033[2J");
  char str[STKDPTH];
  strncpy(str, "-asin(0.5)", STKDPTH - 1);
  algoritm_d(str);
  //   printf("%s\n", str);
  double end = 0;
  operand(str, &end, 0);
  double b = 0.5;
  float a = -asin(b);
  //   printf("%f\n", rez);
  ck_assert_ldouble_eq_tol(end, a, ESP);
}
END_TEST

START_TEST(test_cos) {
  char str[STKDPTH];
  strncpy(str, "cos(1.5)", STKDPTH - 1);
  algoritm_d(str);
  double end = 0;
  operand(str, &end, 0);
  double b = 1.5;
  float a = cos(b);
  ck_assert_ldouble_eq_tol(end, a, ESP);
}
END_TEST

START_TEST(test_acos) {
  char str[STKDPTH];
  strncpy(str, "acos(0.5)", STKDPTH - 1);
  algoritm_d(str);
  double end = 0;
  operand(str, &end, 0);
  double b = 0.5;
  double a = acos(b);
  ck_assert_ldouble_eq_tol(end, a, ESP);
}
END_TEST

START_TEST(test_tan) {
  char str[STKDPTH];
  strncpy(str, "tan(1.5)", STKDPTH - 1);
  algoritm_d(str);
  double end = 0;
  operand(str, &end, 0);
  double b = 1.5;
  double a = tan(b);
  //   printf("test_tan: %.28f\ntest_tan: %.28f\n", a, rez);
  ck_assert_ldouble_eq_tol(end, a, ESP);
}
END_TEST

START_TEST(test_atan) {
  char str[STKDPTH];
  strncpy(str, "atan(1.5)", STKDPTH - 1);
  algoritm_d(str);
  double end = 0;
  operand(str, &end, 0);
  double b = 1.5;
  ck_assert_ldouble_eq_tol(end, atan(b), ESP);
}
END_TEST

START_TEST(test_sqrt) {
  char str[STKDPTH];
  strncpy(str, "sqrt(9)", STKDPTH - 1);
  algoritm_d(str);
  double end = 0;
  operand(str, &end, 0);
  double b = 9;
  ck_assert_ldouble_eq_tol(end, sqrt(b), ESP);
}
END_TEST

START_TEST(test_ln) {
  char str[STKDPTH];
  strncpy(str, "ln(1.5)", STKDPTH - 1);
  algoritm_d(str);
  double end = 0;
  operand(str, &end, 0);
  double a = log10f(1.5);
  ck_assert_ldouble_eq_tol(end, a, ESP);
}
END_TEST

START_TEST(test_log) {
  char str[STKDPTH];
  strncpy(str, "log(1.5)", STKDPTH - 1);
  algoritm_d(str);
  double end = 0;
  operand(str, &end, 0);
  double a = log(1.5);
  ck_assert_ldouble_eq_tol(end, a, ESP);
}
END_TEST

START_TEST(test_mod) {
  char str[STKDPTH];
  strncpy(str, "10 mod 3+2", STKDPTH - 1);
  algoritm_d(str);
  double end = 0;
  operand(str, &end, 0);
  ck_assert_ldouble_eq_tol(end, 3.0, ESP);
}
END_TEST

START_TEST(test_pow) {
  char str[STKDPTH];
  strncpy(str, "2^(3^4)", STKDPTH - 1);
  algoritm_d(str);
  double end = 0;
  operand(str, &end, 0);
  ck_assert_ldouble_eq_tol(end, pow(2, pow(3, 4)), ESP);
}
END_TEST

START_TEST(test_sin_cos) {
  char str[STKDPTH];
  strncpy(str, "sin(29456.123456*4+3)*cos(1-5)-1", STKDPTH - 1);
  algoritm_d(str);
  double end = 0;
  operand(str, &end, 0);
  ck_assert_ldouble_eq_tol(end, -0.4234395090200014, ESP);
}
END_TEST

START_TEST(test_all_01) {
  char str[STKDPTH];
  //   strncpy(str, "2--1", STKDPTH - 1);
  strncpy(str, "2-(-1)*(1-(((1-5)-2)+4)*2)-1", STKDPTH - 1);
  algoritm_d(str);
  double end = 0;
  operand(str, &end, 0);
  ck_assert_ldouble_eq_tol(end, 6.0F, ESP);
}
END_TEST

START_TEST(test_all_02) {
  char str[STKDPTH];
  strncpy(str,
          "15/(7-(1 + "
          "1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
          "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))",
          STKDPTH - 1);
  algoritm_d(str);
  double end = 0;
  operand(str, &end, 0);
  ck_assert_ldouble_eq_tol(end, -30.0721649484536082, ESP);
}
END_TEST

START_TEST(test_all_04) {
  char str[STKDPTH];
  strncpy(str, "2+(26,12*4+3)*(1-5)-1", STKDPTH - 1);
  algoritm_d(str);
  double end = 0;
  operand(str, &end, 0);
  ck_assert_ldouble_eq_tol(end, -428.92, ESP);
}
END_TEST

START_TEST(test_all_05) {
  char str[STKDPTH];
  strncpy(str, "cos(1*(2+3*(4-5*(sin(1.5)))+6))-7", STKDPTH - 1);
  algoritm_d(str);
  double end = 0;
  operand(str, &end, 0);
  ck_assert_ldouble_eq_tol(end, -6.680514747636, ESP);
}
END_TEST

START_TEST(test_x1) {
  char str[STKDPTH];
  strncpy(str, "cos(x*0.5)", STKDPTH - 1);
  algoritm_d(str);
  double end = 0;
  operand(str, &end, 0.5);
  ck_assert_ldouble_eq_tol(end, cos(0.5 * 0.5), ESP);
}
END_TEST

START_TEST(test_credit_a) {
  struct credits cr;
  cr.sum = 300000;
  cr.time = 60;
  cr.percent = 25;
  cr.type = 1;
  cr.all_pay = 0;
  cr.overpayment = 0;
  cr.pay[0] = 0;
  credit_calc(&cr);

  ck_assert_ldouble_eq_tol(cr.pay[0], 8805.40, 1e-2);
  ck_assert_ldouble_eq_tol(cr.all_pay, 528324, 1e-2);
  ck_assert_ldouble_eq_tol(cr.overpayment, 228324, 1e-2);
}
END_TEST

START_TEST(test_credit_d) {
  struct credits cr;
  cr.sum = 300000;
  cr.time = 60;
  cr.percent = 25;
  cr.type = 0;
  cr.all_pay = 0;
  cr.overpayment = 0;
  cr.day[0] = 25;
  cr.month[0] = 10;
  cr.year[0] = 2022;
  cr.pay[0] = 0;
  cr.debt = 0;
  cr.procent[0] = 0;
  cr.balance[0] = 0;
  credit_calc(&cr);

  //   ck_assert_ldouble_eq_tol(cr.pay[0], 8805.40, 1e-2);
  ck_assert_ldouble_eq_tol(cr.all_pay, 490629.08, 1e-2);
  ck_assert_ldouble_eq_tol(cr.overpayment, 190629.08, 1e-2);
}
END_TEST

START_TEST(test_credit_d2) {
  struct credits cr;
  cr.sum = 300000;
  cr.time = 60;
  cr.percent = 25;
  cr.type = 0;
  cr.all_pay = 0;
  cr.overpayment = 0;
  cr.day[0] = 31;
  cr.month[0] = 12;
  cr.year[0] = 2022;
  cr.pay[0] = 0;
  cr.debt = 0;
  cr.procent[0] = 0;
  cr.balance[0] = 0;
  credit_calc(&cr);

  // ck_assert_ldouble_eq_tol(cr.pay[0], 8805.40, 1e-2);
  ck_assert_ldouble_eq_tol(cr.all_pay, 490477.78, 1e-2);
  ck_assert_ldouble_eq_tol(cr.overpayment, 190477.78, 1e-2);
}
END_TEST

START_TEST(test_deposit_0) {
  struct deposit dp;
  struct popolnenie add;

  dp.sum = 100000;
  dp.time = 1;
  dp.percent = 10;
  dp.day[0] = 01;
  dp.month[0] = 10;
  dp.year[0] = 2022;
  dp.nalog = 13;
  dp.periud = 0;
  dp.kapital = 0;
  dp.add = &add;
  //   dp.add->sum[0] = 50000;
  //   dp.add->day[0] = 10;
  //   dp.add->month[0] = 02;
  //   dp.add->year[0] = 2023;

  //   dp.add->sum[1] = -30000;
  //   dp.add->day[1] = 29;
  //   dp.add->month[1] = 2;
  //   dp.add->year[1] = 2024;

  dp.add->day[0] = 0;

  dp.all_nalog = 0;
  dp.all_cash = 0;
  deposit_calc(&dp);

  ck_assert_ldouble_eq_tol(dp.all_nalog, 0.0, 1e-2);
  ck_assert_ldouble_eq_tol(dp.all_cash, 100000.00, 1e-2);
  ck_assert_ldouble_eq_tol(dp.all_procent, 849.40, 1e-2);
}
END_TEST

START_TEST(test_deposit_1) {
  struct deposit dp;
  struct popolnenie add;

  dp.sum = 100000;
  dp.time = 50;
  dp.percent = 10;
  dp.day[0] = 01;
  dp.month[0] = 10;
  dp.year[0] = 2022;
  dp.nalog = 13;
  dp.periud = 1;
  dp.kapital = 1;
  dp.add = &add;
  dp.add->sum[0] = 50000;
  dp.add->day[0] = 10;
  dp.add->month[0] = 02;
  dp.add->year[0] = 2023;

  dp.add->sum[1] = -30000;
  dp.add->day[1] = 29;
  dp.add->month[1] = 2;
  dp.add->year[1] = 2024;

  dp.add->day[2] = 0;

  dp.all_nalog = 0;
  dp.all_cash = 0;
  deposit_calc(&dp);

  ck_assert_ldouble_eq_tol(dp.all_nalog, 0.0, 1e-2);
  ck_assert_ldouble_eq_tol(dp.all_procent, 65263.16, 1e-2);
  ck_assert_ldouble_eq_tol(dp.all_cash, 185263.16, 1e-2);
}
END_TEST

START_TEST(test_deposit_2) {
  struct deposit dp;
  struct popolnenie add;

  dp.sum = 100000;
  dp.time = 50;
  dp.percent = 10;
  dp.day[0] = 01;
  dp.month[0] = 10;
  dp.year[0] = 2022;
  dp.nalog = 13;
  dp.periud = 2;
  dp.kapital = 0;
  dp.add = &add;
  dp.add->sum[0] = 50000;
  dp.add->day[0] = 10;
  dp.add->month[0] = 02;
  dp.add->year[0] = 2023;

  dp.add->sum[1] = -30000;
  dp.add->day[1] = 29;
  dp.add->month[1] = 2;
  dp.add->year[1] = 2024;

  dp.add->day[2] = 0;

  dp.all_nalog = 0;
  dp.all_cash = 0;
  deposit_calc(&dp);

  ck_assert_ldouble_eq_tol(dp.all_nalog, 0.0, 1e-2);
  ck_assert_ldouble_eq_tol(dp.all_procent, 52437.04, 1e-2);
  ck_assert_ldouble_eq_tol(dp.all_cash, 120000.00, 1e-2);
}
END_TEST

START_TEST(test_deposit_21) {
  struct deposit dp;
  struct popolnenie add;

  dp.sum = 100000;
  dp.time = 50;
  dp.percent = 10;
  dp.day[0] = 01;
  dp.month[0] = 10;
  dp.year[0] = 2022;
  dp.nalog = 13;
  dp.periud = 2;
  dp.kapital = 1;
  dp.add = &add;
  dp.add->sum[0] = 50000;
  dp.add->day[0] = 10;
  dp.add->month[0] = 02;
  dp.add->year[0] = 2023;

  dp.add->sum[1] = -30000;
  dp.add->day[1] = 29;
  dp.add->month[1] = 2;
  dp.add->year[1] = 2024;

  dp.add->day[2] = 0;

  dp.all_nalog = 0;
  dp.all_cash = 0;
  deposit_calc(&dp);

  ck_assert_ldouble_eq_tol(dp.all_nalog, 0.0, 1e-2);
  ck_assert_ldouble_eq_tol(dp.all_procent, 65008.04, 1e-2);
  ck_assert_ldouble_eq_tol(dp.all_cash, 185008.04, 1e-2);
}
END_TEST

START_TEST(test_deposit_3) {
  struct deposit dp;
  struct popolnenie add;

  dp.sum = 100000;
  dp.time = 50;
  dp.percent = 10;
  dp.day[0] = 01;
  dp.month[0] = 10;
  dp.year[0] = 2022;
  dp.nalog = 13;
  dp.periud = 3;
  dp.kapital = 1;
  dp.add = &add;
  dp.add->sum[0] = 50000;
  dp.add->day[0] = 10;
  dp.add->month[0] = 02;
  dp.add->year[0] = 2023;

  dp.add->sum[1] = -30000;
  dp.add->day[1] = 29;
  dp.add->month[1] = 2;
  dp.add->year[1] = 2024;

  dp.add->day[2] = 0;

  dp.all_nalog = 0;
  dp.all_cash = 0;
  deposit_calc(&dp);

  ck_assert_ldouble_eq_tol(dp.all_nalog, 0.0, 1e-2);
  ck_assert_ldouble_eq_tol(dp.all_procent, 64371.47, 1e-2);
  ck_assert_ldouble_eq_tol(dp.all_cash, 184371.47, 1e-2);
}
END_TEST

START_TEST(test_deposit_4) {
  struct deposit dp;
  struct popolnenie add;

  dp.sum = 1000000;
  dp.time = 50;
  dp.percent = 10;
  dp.day[0] = 01;
  dp.month[0] = 10;
  dp.year[0] = 2022;
  dp.nalog = 13;
  dp.periud = 4;
  dp.kapital = 1;
  dp.add = &add;
  dp.add->sum[0] = 50000;
  dp.add->day[0] = 10;
  dp.add->month[0] = 02;
  dp.add->year[0] = 2023;

  dp.add->sum[1] = -30000;
  dp.add->day[1] = 29;
  dp.add->month[1] = 2;
  dp.add->year[1] = 2024;

  dp.add->day[2] = 0;

  dp.all_nalog = 0;
  dp.all_cash = 0;
  deposit_calc(&dp);

  ck_assert_ldouble_eq_tol(dp.all_nalog, 28002.14, 1e-2);
  ck_assert_ldouble_eq_tol(dp.all_procent, 515401.09, 1e-2);
  ck_assert_ldouble_eq_tol(dp.all_cash, 1535401.09, 1e-2);
}
END_TEST

START_TEST(test_deposit_5) {
  struct deposit dp;
  struct popolnenie add;

  dp.sum = 100000;
  dp.time = 50;
  dp.percent = 10;
  dp.day[0] = 01;
  dp.month[0] = 10;
  dp.year[0] = 2022;
  dp.nalog = 13;
  dp.periud = 5;
  dp.kapital = 1;
  dp.add = &add;
  dp.add->sum[0] = 50000;
  dp.add->day[0] = 10;
  dp.add->month[0] = 02;
  dp.add->year[0] = 2023;

  dp.add->sum[1] = -30000;
  dp.add->day[1] = 29;
  dp.add->month[1] = 2;
  dp.add->year[1] = 2024;

  dp.add->day[2] = 0;

  dp.all_nalog = 0;
  dp.all_cash = 0;
  deposit_calc(&dp);

  ck_assert_ldouble_eq_tol(dp.all_nalog, 0.0, 1e-2);
  ck_assert_ldouble_eq_tol(dp.all_procent, 61766.06, 1e-2);
  ck_assert_ldouble_eq_tol(dp.all_cash, 181766.06, 1e-2);
}
END_TEST

START_TEST(test_deposit_6) {
  struct deposit dp;
  struct popolnenie add;

  dp.sum = 100000;
  dp.time = 50;
  dp.percent = 10;
  dp.day[0] = 01;
  dp.month[0] = 10;
  dp.year[0] = 2022;
  dp.nalog = 13;
  dp.periud = 6;
  dp.kapital = 1;
  dp.add = &add;
  dp.add->sum[0] = 50000;
  dp.add->day[0] = 10;
  dp.add->month[0] = 02;
  dp.add->year[0] = 2023;

  dp.add->sum[1] = -30000;
  dp.add->day[1] = 29;
  dp.add->month[1] = 2;
  dp.add->year[1] = 2024;

  dp.add->day[2] = 0;

  dp.all_nalog = 0;
  dp.all_cash = 0;
  deposit_calc(&dp);

  ck_assert_ldouble_eq_tol(dp.all_nalog, 0.0, 1e-2);
  ck_assert_ldouble_eq_tol(dp.all_procent, 52437.01, 1e-2);
  ck_assert_ldouble_eq_tol(dp.all_cash, 172437.01, 1e-2);
}
END_TEST

int main(void) {
  Suite *suite = suite_create("TheTest");
  TCase *tc = tcase_create("TheTest");
  SRunner *sr = srunner_create(suite);
  int nf;
  suite_add_tcase(suite, tc);

  tcase_add_test(tc, test_transfer);
  tcase_add_test(tc, test_alg_01);

  tcase_add_test(tc, test_all_01);
  tcase_add_test(tc, test_all_02);
  tcase_add_test(tc, test_all_04);
  tcase_add_test(tc, test_all_05);

  tcase_add_test(tc, test_pow);
  tcase_add_test(tc, test_mod);

  tcase_add_test(tc, test_cos);
  tcase_add_test(tc, test_sin);
  tcase_add_test(tc, test_tan);
  tcase_add_test(tc, test_acos);
  tcase_add_test(tc, test_asin);
  tcase_add_test(tc, test_atan);
  tcase_add_test(tc, test_sqrt);
  tcase_add_test(tc, test_ln);
  tcase_add_test(tc, test_log);

  tcase_add_test(tc, test_sin_cos);

  tcase_add_test(tc, test_x1);

  tcase_add_test(tc, test_credit_a);
  tcase_add_test(tc, test_credit_d);
  tcase_add_test(tc, test_credit_d2);

  tcase_add_test(tc, test_deposit_0);
  tcase_add_test(tc, test_deposit_1);
  tcase_add_test(tc, test_deposit_2);
  tcase_add_test(tc, test_deposit_21);
  tcase_add_test(tc, test_deposit_3);
  tcase_add_test(tc, test_deposit_4);
  tcase_add_test(tc, test_deposit_5);
  tcase_add_test(tc, test_deposit_6);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
