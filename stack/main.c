#include "stack.h"

int main()
{
    mystack_t stack = new_stack();

    push(&stack, 15);
    push(&stack, 27);
    push(&stack, 3);
    
    int a = pop(&stack, 3);

    printf("%d\n", a); // should print "3"

    
    return 0;
}
