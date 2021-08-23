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

static float octave(int oct)
{
    oct = clamp(oct, 1, 7);
    float pedal_c = 32.70320f;
 
    int ratio = pow(2, oct - 1);
    
    return pedal_c * ratio;
}

static float notevalue_to_ms(int value, int tempo)
{
    float ms_per_beat = 60.0f/(float)tempo * 1000;
    float ratio = 4.0f/(float)value;
    return ms_per_beat * ratio;
}


static float freq(int note, int oct)
{
    const float half_step = 1.05946f; 
    float freq_ratio = powf(half_step, (float)note);
    float frequency = octave(oct) * freq_ratio;
    return frequency;
}

// =============================================================================
// PUBLIC FUNCTIONS (non-static functions, aka ones that go in the header file)

void play(int note, int octave, int note_value, int tempo)
{
    sound(freq(note, octave), notevalue_to_ms(note_value, tempo));
}





