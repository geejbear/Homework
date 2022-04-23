#ifndef mylib_h
#define mylib_h

#include <stdio.h>

void PrintMessage(const char * message);

// #define this exactly once in your program
#ifdef mylib_implementation

void PrintMessage(const char * message)
{
    printf("%s\n", message);
}

#endif /* mylib_implementation */

#endif /* mylib_h */
