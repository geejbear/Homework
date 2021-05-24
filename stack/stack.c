#include <stdio.h>
#include <stdbool.h>
#include "stack.h"
//#include "stack.h" // TODO: create a module

// stack data structure
// first in, last out (FILO)

// header: interface
// c file: implementation

// stack contents:
// ...
// 5:
// 4:
// 3:
// 2: 17 (added third) <- TOP
// 1: 345 (added second)
// 0: 14 (added first)



// push (add) to the stack: increase top by 1
// return type: maybe?
void push(mystack_t *stack, int value)
{
    // TODO: this
    if (stack->top != MAX_STACK_SIZE - 1) {
        stack->top++;
        stack->data[stack->top] = value;
    }
}


// pop (remove) from the stack: decrease top by 1
int pop(mystack_t *stack, int value)
{
    // TODO: this
    // check if the stack is empty!
    
    if (stack->top != -1) {
        value = stack->data[stack->top];
        stack->top--;
    }
}


// initialize a new stack
mystack_t new_stack()
{
    mystack_t new;
    
    new.top = -1;
    
    return new;
}


// check the stack's 'top' value to see if empty
bool stack_is_empty(mystack_t *check)
{
    // TODO: this
    if (check->top != -1) {
    
        return false; 
    }
        
}
