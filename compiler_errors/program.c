#include <stdio.h>

// INSTRUCTIONS

//    For each exercise:
// 1. break the program as directed, then compile it
// 2. in errors.txt, write down:
//    a. The exact compiler error message(s) (excluding portions
//       specific to this code)
//    b. Write down in simple language what the error means
// 3. unbreak it so the program compilers correctly before
//    proceeding to next exercise


// EXERCISES

// 1. In main(): change variable 'message' name to 'mssage'
// 2. Move function calc() below main()
// 3. In calc(): Comment out line 'return squared;'
// 4. Change calc()'s return type to void.

int calc(int a, int b, int c)
{
    int sum = a + b;
    int squared = sum * sum;
    
    return squared;
}

int main()
{
    const char * message = "Hello, world";
    printf("%s\n", message);
    
    int value = calc(1, 2, 3);
    printf("calculated value: %d\n", value);
    
    return 0;
}
