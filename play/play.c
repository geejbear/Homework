/*
 * Created by Geegbear  
 * 29/05/2021  
 * "Frequency/millisecond calculator"
 * To be implemented along the function 'sound(...)' from the LibTC
 * Such implementation has not yet been tested!
 * 
 */   

// TODO: make a header file
// TODO: make functions that are only to be used in this file static
// TODO: do a search for TODOs in rest of file

// =============================================================================
// INCLUDES

#include "play.h"

// =============================================================================
// DEFINES
// =============================================================================
// TYPES / ENUMS
// =============================================================================
// DATA
// =============================================================================
// PROTOTYPES (function declarations)
// =============================================================================
// PRIVATE FUNCTIONS (private aka static functions)
// =============================================================================
// PUBLIC FUNCTIONS (non-static functions, aka ones that go in the header file)

float notevalue_to_ms(int value, int tempo)
{
    float ms_per_beat = 60.0f/(float)tempo * 1000;
    float ratio = 4.0f/(float)value;
    return ms_per_beat * ratio;
}

float freq(int note, int oct)
{
    const float half_step = 1.05946f; 
    float freq_ratio = powf(half_step, (float)note);
    float frequency = octave(oct) * freq_ratio;
    return frequency;
}

int clamp(int value, int min, int max)
{
    if (value < min) {
        value = min;
        return value;
    } 
    
    if (value > max) {
        value = max;
        return value;
    } else if (value >= min || value <= max) {
        return value;
    }
    return 0;
}

float octave(int oct)
{
    oct = clamp(oct, 1, 7);
    float pedal_c = 32.70320f;
 
    int ratio = pow(2, oct - 1);
    
    return pedal_c * ratio;
}

void play(int note, int octave, int note_value, int tempo)
{
    sound(freq(note, octave), notevalue_to_ms(note_value, tempo));
}





