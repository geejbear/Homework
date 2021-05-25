#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_STACK_SIZE 100

typedef struct
{
    int top; // = -1
    int data[MAX_STACK_SIZE]; 
} mystack_t;

void push(mystack_t *stack, int value);
int pop(mystack_t *stack);
mystack_t new_stack();
bool stack_is_empty(mystack_t *check);

#endif