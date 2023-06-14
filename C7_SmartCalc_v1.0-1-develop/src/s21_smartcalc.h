#ifndef SRC_S21_SMARTCALC_H_
#define SRC_S21_SMARTCALC_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  LEXEME_NUM = 1,
  LEXEME_X = 2,
  LEXEME_PLUS = 3,
  LEXEME_MINUS = 4,
  LEXEME_MUL = 5,
  LEXEME_DIV = 6,
  LEXEME_POW = 7,
  LEXEME_MOD = 8,
  LEXEME_COS = 9,
  LEXEME_SIN = 10,
  LEXEME_TAN = 11,
  LEXEME_ACOS = 12,
  LEXEME_ASIN = 13,
  LEXEME_ATAN = 14,
  LEXEME_LOG = 15,
  LEXEME_LN = 16,
  LEXEME_SQRT = 17,
  LEXEME_LEFT = 18,
  LEXEME_RIGHT = 19,
  LEXEME_uPLUS = 20,
  LEXEME_uMINUS = 21
} type_l;

typedef enum {
  PRIORITY_F = 0,
  PRIORITY_D = 1,
  PRIORITY_C = 2,
  PRIORITY_B = 3,
  PRIORITY_A = 4,
  PRIORITY__ = 5
} type_p;

typedef struct stack {
  double value;
  type_p priority;
  type_l lexeme;
  struct stack *next;
} type_s;

void push(type_s **head, double value, type_p priority, type_l type);
void pop(type_s **head);
type_s peek(type_s *head);
void print_type_s(type_s *head);
int counterstack(type_s *head);
void peektemp(type_s *temp, type_s *o);

double s21_smartcalc(char *str, double x);

int validator(char *str);
int endvalid(char *str, int len);
int oncevalid(char *str, int *i, int *dot, int *operation);
int doublevalid(char *str, int *i, int *left);
int triplevalid(char *str, int *i, int *dot, int *operation, int *left);
int quadrovalid(char *str, int *i, int *operation, int *left);
void nullflag(int *operation, int *dot);

double maincalc();
double parseroperand();
void parseroperator();
int compare();
type_s *calculation();
double calculationfunction();
double resfunction();
void leftrightfix();

void init_temp(type_s **operatortemp, type_s **temp);
void endcalc(type_s *operators, type_s *operand, double *result,
             type_s *operatortemp, type_s *temp);
void endcalcfunction(type_s *operators, type_s *operand, double *result,
                     type_s *operatortemp, type_s *temp, type_s *before);
void unarcheck(int *unar, type_s **operand, double value);
void free_type_s(type_s *operators, type_s *operand, type_s *operatortemp,
                 type_s *temp);
void compareone(type_s **operand, type_s **operators, type_s **operatortemp,
                type_s **temp);
void comparetwo(type_s **operand, type_s **operators);

#endif  // SRC_S21_SMARTCALC_H_