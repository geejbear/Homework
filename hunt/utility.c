#include "utility.h"

int clamp(int value, int min, int max)
{
    int result;
    
    if (value < min) {
        result = min;
    } else if (value > max) {
        result = max;
    } else { // in range
        result = value;
    }
    
    return result;
}