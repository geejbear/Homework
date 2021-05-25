#include "stack.h"

int main()
{
    mystack_t stack = new_stack();

    push(&stack, 15);
    push(&stack, 27);
    push(&stack, 3);
    
    int a = pop(&stack);

    printf("%d\n", a);

    
    return 0;
}
