#include <stdio.h>

#define STR_LEN 20

int main()
{
    char str1[STR_LEN] = "reverse me, baby!";
    for (int i = STR_LEN - 1; i > 0; i--) {
        printf("%c",str1[i]);
    }
    
    return 0;
}
