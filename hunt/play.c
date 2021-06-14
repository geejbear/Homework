/*
 * Created by Geegbear  
 * 29/05/2021  
 * "Frequency/millisecond calculator" // TODO: write for what a user needs to know
 * To be implemented along the function 'sound(...)' from the LibTC
 * Such implementation has not yet been tested!
 * 
 */   

// TODO: make functions that are only to be used in this file static
// TODO: do a search for TODOs in rest of file

#include "play.h"

#include <dos.h>
#include <math.h>

// =============================================================================
// PRIVATE FUNCTIONS (private aka static functions)

static int clamp(int value, int min, int max)
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


static float notevalue_to_ms(int value, int tempo)
{
    float ms_per_beat = 60.0f/(float)tempo * 1000;
    float ratio = 4.0f/(float)value;
    return ms_per_beat * ratio;
}


// =============================================================================
// PUBLIC FUNCTIONS (non-static functions, aka ones that go in the header file)

// TODO: make static
float octave(int oct)
{
    oct = clamp(oct, 1, 7);
    float pedal_c = 32.70320f;
 
    int ratio = pow(2, oct - 1);
    
    return pedal_c * ratio;
}

// TODO: make static
float freq(int note, int oct)
{
    const float half_step = 1.05946f; 
    float freq_ratio = powf(half_step, (float)note);
    float frequency = octave(oct) * freq_ratio;
    return frequency;
}

void play(int note, int octave, int note_value, int tempo)
{
    sound(freq(note, octave), notevalue_to_ms(note_value, tempo));
}





