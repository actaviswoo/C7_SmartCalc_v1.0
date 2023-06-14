#include <stdio.h>
#include <stdlib.h>

#include "s21_smartcalc.h"

void push(type_s **head, double value, type_p priority, type_l lexeme) {
  type_s *temp = (type_s *)malloc(sizeof(type_s));
  if (temp == NULL) {
    exit(1);
  }
  temp->value = value;
  temp->lexeme = lexeme;
  temp->priority = priority;
  temp->next = (*head);
  (*head) = temp;
}

void pop(type_s **head) {
  if (*head != NULL) {
    type_s *temp = (*head)->next;
    free(*head);
    *head = temp;
  }
}

// void print_type_s(type_s *head) {
//   while (head != NULL) {
//     printf("VALUE %lf\n", head->value);
//     printf("PRIORITY %d\n", head->priority);
//     printf("TYPE %d\n", head->lexeme);
//     head = head->next;
//   }
// }

void peektemp(type_s *temp, type_s *o) {
  if (o != NULL) {
    temp->lexeme = o->lexeme;
    temp->priority = o->priority;
    temp->value = o->value;
  } else {
    temp->lexeme = 0;
    temp->priority = 0;
    temp->value = 0;
  }
}
