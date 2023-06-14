#include "s21_smartcalc.h"

// int main() {
//   char *str = "cos(x*cos(x))";
//   double dd = cos(10 * cos(10));
//   printf("%lf %lf\n", dd, s21_smartcalc(str, 10));
//   printf("%lf %lf\n", 1 + 2 + 23 * 3 + 32 / 2 - 1 + pow((cos(13) - 1), (6)),
//          s21_smartcalc("1+2+23*3+32/2-1+(cos(13)-1)^(6)", 0));
// }

double s21_smartcalc(char *str, double x) {
  double res = 0;
  res = maincalc(str, x);
  return res;
}

double parseroperand(char *str, int *i) {
  double value = 0, len = strlen(str);
  char temp[255];
  memset(temp, '\0', 255);
  int j = 0;
  while (str[*i] != '+' && str[*i] != '-' && str[*i] != '/' && str[*i] != '*' &&
         str[*i] != '^' && str[*i] != ')' && str[*i] != 'm') {
    if (str[*i] == '\0') continue;
    temp[j] = str[*i];
    (*i)++;
    j++;
    if (*i == len) break;
  }
  (*i)--;
  value = atof(temp);
  memset(temp, '\0', 255);
  return value;
}

void parseroperator(char *str, int *i, type_s **operator, int * unar,
                    int *operatorisfuntion) {
  if (str[*i] == '*') {
    push(operator, 0, PRIORITY_C, LEXEME_MUL);
  } else if (str[*i] == '-' && ((*i) == 0 || str[*i - 1] == '(')) {
    push(operator, 0, PRIORITY_D, LEXEME_uMINUS);
    *unar = 1;
  } else if (str[*i] == '+' && ((*i) == 0 || str[*i - 1] == '(')) {
    push(operator, 0, PRIORITY_D, LEXEME_uPLUS);
    *unar = 2;
  } else if (str[*i] == '+') {
    push(operator, 0, PRIORITY_D, LEXEME_PLUS);
  } else if (str[*i] == '-') {
    push(operator, 0, PRIORITY_D, LEXEME_MINUS);
  } else if (str[*i] == '/') {
    push(operator, 0, PRIORITY_C, LEXEME_DIV);
  } else if (str[*i] == '^') {
    push(operator, 0, PRIORITY_B, LEXEME_POW);
  } else if (str[*i] == 'm') {
    push(operator, 0, PRIORITY_B, LEXEME_MOD);
    (*i) += 2;
  } else if (str[*i] == '(') {
    push(operator, 0, PRIORITY__, LEXEME_LEFT);
  } else if (str[*i] == ')') {
    push(operator, 0, PRIORITY__, LEXEME_RIGHT);
  } else if (str[*i] == 'l' && str[*i + 1] == 'n') {
    push(operator, 0, PRIORITY_A, LEXEME_LN);
    (*i) += 2;
    *operatorisfuntion = 1;
  } else if (str[*i] == 'l' && str[*i + 1] == 'o') {
    push(operator, 0, PRIORITY_A, LEXEME_LOG);
    (*i) += 3;
    *operatorisfuntion = 1;
  } else if (str[*i] == 's' && str[*i + 1] == 'i') {
    push(operator, 0, PRIORITY_A, LEXEME_SIN);
    (*i) += 3;
    *operatorisfuntion = 1;
  } else if (str[*i] == 'c') {
    push(operator, 0, PRIORITY_A, LEXEME_COS);
    (*i) += 3;
    *operatorisfuntion = 1;
  } else if (str[*i] == 't') {
    push(operator, 0, PRIORITY_A, LEXEME_TAN);
    (*i) += 3;
    *operatorisfuntion = 1;
  } else if (str[*i] == 'a' && str[*i + 1] == 's') {
    push(operator, 0, PRIORITY_A, LEXEME_ASIN);
    (*i) += 4;
    *operatorisfuntion = 1;
  } else if (str[*i] == 'a' && str[*i + 1] == 'c') {
    push(operator, 0, PRIORITY_A, LEXEME_ACOS);
    (*i) += 4;
    *operatorisfuntion = 1;
  } else if (str[*i] == 'a' && str[*i + 1] == 't') {
    push(operator, 0, PRIORITY_A, LEXEME_ATAN);
    (*i) += 4;
    *operatorisfuntion = 1;
  } else if (str[*i] == 's' && str[*i + 1] == 'q') {
    push(operator, 0, PRIORITY_A, LEXEME_SQRT);
    (*i) += 4;
    *operatorisfuntion = 1;
  }
}

void endcalc(type_s *operator, type_s * operand, double *result,
             type_s *operatortemp, type_s *temp) {
  while (operator!= NULL && operand != NULL) {
    operand = calculation(operand, operator);
    pop(&operator);
  }
  *result = operand->value;
  free_type_s(operator, operand, operatortemp, temp);
}

void xcheck(char *str, int *i, double *value, double x) {
  if (str[*i] != 'x')
    *value = parseroperand(str, i);
  else
    *value = x;
}

int startoperand(char *str, int i) {
  return ((str[i] >= '0' && str[i] <= '9') || str[i] == '.' || str[i] == 'x');
}

double maincalc(char *str, double x) {
  double result = 0, value = 0, len = strlen(str);
  int unar = 0, operatorisfunction = 0;
  type_s *operand = NULL, *operator= NULL, *operatortemp = NULL, *temp = NULL;
  init_temp(&operatortemp, &temp);
  for (int i = 0; i < len; i++) {
    if (startoperand(str, i)) {
      xcheck(str, &i, &value, x);
      unarcheck(&unar, &operand, value);
    } else {
      if (operator!= NULL) {
        peektemp(operatortemp, operator);
      }
      parseroperator(str, &i, &operator, & unar, &operatorisfunction);
      if (operatorisfunction == 1) {
        value = calculationfunction(str, &i, operator, x);
        unarcheck(&unar, &operand, value);
        pop(&operator);
        if (str[i - 1] == ')') i--;
        operatorisfunction = 0;
      } else if (unar != 0) {
        pop(&operator);
      } else if (compare(operator, operatortemp) == 1) {
        compareone(&operand, &operator, & operatortemp, &temp);
      } else if (compare(operator, operatortemp) == 2) {
        comparetwo(&operand, &operator);
      }
      peektemp(operatortemp, NULL);
    }
  }
  endcalc(operator, operand, &result, operatortemp, temp);
  return result;
}

void compareone(type_s **operand, type_s **operator, type_s ** operatortemp,
                type_s **temp) {
  peektemp(*temp, *operator);
  *operand = calculation(*operand, *operatortemp);
  for (int j = 0; j < 2; j++) pop(operator);
  push(operator,(*temp)->value, (*temp)->priority, (*temp)->lexeme);
  peektemp(*temp, NULL);
}

void comparetwo(type_s **operand, type_s **operator) {
  pop(operator);
  while ((*operator)->lexeme != LEXEME_LEFT) {
    *operand = calculation(*operand, *operator);
    pop(operator);
  }
  pop(operator);
}

void unarcheck(int *unar, type_s **operand, double value) {
  if ((*unar) == 0 || (*unar) == 2)
    push(operand, value, PRIORITY_F, LEXEME_NUM);
  if ((*unar) == 1) push(operand, -value, PRIORITY_F, LEXEME_NUM);
  (*unar) = 0;
}

double calculationfunction(char *str, int *i, type_s *before, double x) {
  double value = 0, result = 0, len = strlen(str);
  int left = 1, right = 0, unar = 0, operatorisfunction = 0;
  type_s *operand = NULL, *operator= NULL, *operatortemp = NULL, *temp = NULL;
  init_temp(&operatortemp, &temp);
  while (left != right && (*i) < len) {
    if (startoperand(str, *i)) {
      xcheck(str, i, &value, x);
      unarcheck(&unar, &operand, value);
    } else {
      if (operator!= NULL) peektemp(operatortemp, operator);
      operatorisfunction = 0;
      parseroperator(str, i, &operator, & unar, &operatorisfunction);
      leftrightfix(&right, &left, operator, before);
      if (operatorisfunction == 1) {
        value = calculationfunction(str, i, operator, x);
        unarcheck(&unar, &operand, value);
        pop(&operator);
        peektemp(operatortemp, NULL);
        if (str[*i - 1] == ')' && str[*i] == ')') left = right;
      } else if (unar != 0) {
        peektemp(operatortemp, NULL);
        pop(&operator);
      } else if (compare(operator, operatortemp) == 1) {
        compareone(&operand, &operator, & operatortemp, &temp);
      } else if (compare(operator, operatortemp) == 2) {
        comparetwo(&operand, &operator);
        peektemp(operatortemp, NULL);
      }
    }
    (*i)++;
  }
  endcalcfunction(operator, operand, &result, operatortemp, temp, before);
  return result;
}

void init_temp(type_s **operatortemp, type_s **temp) {
  push(operatortemp, 0, 0, 0);
  push(temp, 0, 0, 0);
}

void endcalcfunction(type_s *operator, type_s * operand, double *result,
                     type_s *operatortemp, type_s *temp, type_s *before) {
  while (operator!= NULL && operand != NULL && operator->lexeme != 18) {
    operand = calculation(operand, operator);
    pop(&operator);
  }
  *result = resfunction(before, operand);
  free_type_s(operator, operand, operatortemp, temp);
}

void free_type_s(type_s *operator, type_s * operand, type_s *operatortemp,
                 type_s *temp) {
  free(operand);
  free(operator);
  free(operatortemp);
  free(temp);
}

void leftrightfix(int *right, int *left, type_s *operator, type_s * before) {
  if (operator->lexeme == LEXEME_RIGHT) (*right)++;
  if (operator->lexeme == LEXEME_LEFT && before->lexeme != LEXEME_SIN &&
      before->lexeme != LEXEME_COS && before->lexeme != LEXEME_TAN &&
      before->lexeme != LEXEME_ASIN && before->lexeme != LEXEME_ACOS &&
      before->lexeme != LEXEME_ATAN && before->lexeme != LEXEME_LN &&
      before->lexeme != LEXEME_LOG && before->lexeme != LEXEME_SQRT)
    (*left)++;
}

double resfunction(type_s *before, type_s *operand) {
  double result = 0;
  if (before->lexeme == LEXEME_SIN) {
    result = sin(operand->value);
  } else if (before->lexeme == LEXEME_COS) {
    result = cos(operand->value);
  } else if (before->lexeme == LEXEME_TAN) {
    result = tan(operand->value);
  } else if (before->lexeme == LEXEME_ASIN) {
    result = asin(operand->value);
  } else if (before->lexeme == LEXEME_ACOS) {
    result = acos(operand->value);
  } else if (before->lexeme == LEXEME_ATAN) {
    result = atan(operand->value);
  } else if (before->lexeme == LEXEME_LN) {
    result = log(operand->value);
  } else if (before->lexeme == LEXEME_LOG) {
    result = log10(operand->value);
  } else if (before->lexeme == LEXEME_SQRT) {
    result = sqrt(operand->value);
  }
  return result;
}

int compare(type_s *operator, type_s * operatortemp) {
  int result = 0;
  if (operatortemp->priority >= operator->priority &&
                                operatortemp->priority != PRIORITY__)
    result = 1;
  if (operator->lexeme == LEXEME_LEFT) result = 0;
  if (operator->lexeme == LEXEME_RIGHT) result = 2;
  return result;
}

type_s *calculation(type_s *operand, type_s *operator) {
  double result = 0;
  type_s *num1 = NULL, *num2 = NULL;
  init_temp(&num1, &num2);
  peektemp(num1, operand);
  pop(&operand);
  peektemp(num2, operand);
  pop(&operand);
  if (operator->lexeme == LEXEME_PLUS) {
    result = num2->value + num1->value;
  } else if (operator->lexeme == LEXEME_MINUS) {
    result = num2->value - num1->value;
  } else if (operator->lexeme == LEXEME_MUL) {
    result = num2->value * num1->value;
  } else if (operator->lexeme == LEXEME_MOD) {
    result = fmod(num2->value, num1->value);
  } else if (operator->lexeme == LEXEME_DIV) {
    result = num2->value / num1->value;
  } else if (operator->lexeme == LEXEME_POW) {
    result = pow(num2->value, num1->value);
  }
  push(&operand, result, PRIORITY_F, LEXEME_NUM);
  free(num1);
  free(num2);
  return operand;
}

int validator(char *str) {
  int result = 1, right = 0, left = 0, len = strlen(str), dot = 0,
      operation = 1;
  if (endvalid(str, len)) {
    result *= result;
  } else {
    result = 0;
  }
  for (int i = 0; i < len; i++) {
    if (str[i] == ' ') continue;
    if (str[i] == ')') {
      right++;
      if (left > 0 && left == right) {
        if (operation == 0) result = 0;
        operation = 2;
      }
      if (left < right) result = 0;
    }
    if (str[i] == '(') left++;
    if (oncevalid(str, &i, &dot, &operation)) {
      result *= result;
    } else if (doublevalid(str, &i, &left)) {
      result *= result;
    } else if (triplevalid(str, &i, &dot, &operation, &left)) {
      result *= result;
    } else if (quadrovalid(str, &i, &operation, &left)) {
      result *= result;
    } else {
      result = 0;
    }
    if (str[i] == '(' && str[i + 1] == ')') {
      result = 0;
    }
  }
  if (operation == 0) result = 0;
  if (right != left) result = 0;
  return result;
}

int endvalid(char *str, int len) {
  int result = 1;
  if (str[len - 1] == ')' || (str[len - 1] >= '0' && str[len - 1] <= '9') ||
      str[len - 1] == '.' || str[len - 1] == 'x' || str[len - 1] == '\0' ||
      str[len - 1] == ' ') {
    result *= result;
  } else {
    result = 0;
  }
  if (str[0] == 'm') result = 0;
  return result;
}

int oncevalid(char *str, int *i, int *dot, int *operation) {
  int result = 1;
  if ((str[*i] >= '0' && str[*i] <= '9') || str[*i] == 'x' || str[*i] == '(' ||
      str[*i] == ')') {
    *operation = 1;
    if (str[*i] == '(' && *operation == 1 && *operation == 3 && *i != 0)
      result = 0;
    result *= result;
    if (str[*i] == '(' &&
        (str[*i + 1] == '/' || str[*i + 1] == '*' || str[*i + 1] == '^'))
      result = 0;
    if (str[*i] == 'x' && ((str[*i - 1] >= '0' && str[*i - 1] <= '9') ||
                           (str[*i + 1] >= '0' && str[*i + 1] <= '9') ||
                           str[*i - 1] == '.' || str[*i + 1] == '.'))
      result = 0;
    if (str[*i] == ')' &&
        ((str[*i + 1] >= '0' && str[*i + 1] <= '9') || str[*i + 1] == '.'))
      result = 0;
  } else if (str[*i] == '+' || str[*i] == '-' || str[*i] == '/' ||
             str[*i] == '*' || str[*i] == '^') {
    result *= result;
    if (str[*i + 1] == '+' || str[*i + 1] == '-' || str[*i + 1] == '/' ||
        str[*i + 1] == '*' || str[*i + 1] == '^' || str[*i + 1] == 'm' ||
        str[*i + 1] == ')') {
      result = 0;
    }
    if (*i == 0 && (str[*i] == '-' || str[*i] == '+') &&
        !(str[*i + 1] == '+' || str[*i + 1] == '-' || str[*i + 1] == '/' ||
          str[*i + 1] == '*' || str[*i + 1] == '^' || str[*i + 1] == 'm' ||
          str[*i + 1] == ')')) {
      *operation = 3;
      result = 1;
    } else if (*i == 0 &&
               (str[*i] == '^' || str[*i] == '/' || str[*i] == '*')) {
      result = 0;
    } else {
      nullflag(operation, dot);
    }
  } else if (str[*i] == '.' && (str[*i + 1] >= '0' && str[*i + 1] <= '9') &&
             *dot == 0 &&
             ((str[*i - 1] >= '0' && str[*i - 1] <= '9') ||
              str[*i - 1] == '(' || str[*i - 1] == '+' || str[*i - 1] == '-' ||
              str[*i - 1] == '/' || str[*i - 1] == '*' || str[*i - 1] == '^' ||
              *i == 0)) {
    *dot = 1;
    result *= result;
  } else {
    result = 0;
  }
  return result;
}

void nullflag(int *operation, int *dot) {
  *operation = 0;
  *dot = 0;
}

int doublevalid(char *str, int *i, int *left) {
  int result = 1;
  if (str[*i] == 'l' && str[*i + 1] == 'n' && str[*i + 2] == '(') {
    if (str[*i + 3] == '/' || str[*i + 3] == '*' || str[*i + 3] == '^' ||
        str[*i + 3] == 'm')
      result = 0;
    (*left)++;
    (*i) += 2;
  } else {
    result = 0;
  }
  return result;
}

int triplevalid(char *str, int *i, int *dot, int *operation, int *left) {
  int result = 1;
  if ((str[*i] == 'm' && str[*i + 1] == 'o' && str[*i + 2] == 'd')) {
    if (str[*i + 3] == '+' || str[*i + 3] == '-' || str[*i + 3] == '/' ||
        str[*i + 3] == '*' || str[*i + 3] == '^')
      result = 0;
    if (*operation == 0) result = 0;
    *operation = 0;
    *dot = 0;
    (*i) += 2;
    result *= result;
  } else if ((str[*i] == 's' && str[*i + 1] == 'i' && str[*i + 2] == 'n' &&
              str[*i + 3] == '(') ||
             (str[*i] == 'c' && str[*i + 1] == 'o' && str[*i + 2] == 's' &&
              str[*i + 3] == '(') ||
             (str[*i] == 't' && str[*i + 1] == 'a' && str[*i + 2] == 'n' &&
              str[*i + 3] == '(') ||
             (str[*i] == 'l' && str[*i + 1] == 'o' && str[*i + 2] == 'g' &&
              str[*i + 3] == '(')) {
    if (str[*i + 4] == '/' || str[*i + 4] == '*' || str[*i + 4] == '^' ||
        str[*i + 4] == 'm')
      result = 0;
    (*left)++;
    if (*operation == 0 || *operation == 3 || *i == 0 || str[*i - 1] == '(') {
      result *= result;
    } else {
      result = 0;
    }
    (*i) += 3;
  } else {
    result = 0;
  }
  return result;
}

int quadrovalid(char *str, int *i, int *operation, int *left) {
  int result = 1;
  if ((str[*i] == 'a' && str[*i + 1] == 's' && str[*i + 2] == 'i' &&
       str[*i + 3] == 'n' && str[*i + 4] == '(') ||
      (str[*i] == 'a' && str[*i + 1] == 'c' && str[*i + 2] == 'o' &&
       str[*i + 3] == 's' && str[*i + 4] == '(') ||
      (str[*i] == 'a' && str[*i + 1] == 't' && str[*i + 2] == 'a' &&
       str[*i + 3] == 'n' && str[*i + 4] == '(') ||
      (str[*i] == 's' && str[*i + 1] == 'q' && str[*i + 2] == 'r' &&
       str[*i + 3] == 't' && str[*i + 4] == '(')) {
    if (str[*i + 5] == '/' || str[*i + 5] == '*' || str[*i + 5] == '^' ||
        str[*i + 5] == 'm')
      result = 0;
    (*left)++;
    if (*operation == 0 || *operation == 3 || *i == 0 || str[*i - 1] == '(') {
      result *= result;
    } else {
      result = 0;
    }
    (*i) += 4;
  } else {
    result = 0;
  }
  return result;
}