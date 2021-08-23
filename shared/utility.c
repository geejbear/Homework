#include "utility.h"

void clamp(int *value, int min, int max)
{
    
    if (*value < min) {
        *value = min;
    } else if (*value > max) {
        *value = max;
    }
}