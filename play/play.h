/*
 * Created by Geegbear  
 * 29/05/2021  
 * "Frequency/millisecond calculator" // TODO: write for what a user needs to know
 * To be implemented along the function 'sound(...)' from the LibTC
 * Such implementation has not yet been tested!
 * 
 */  

#ifndef PLAY_H
#define PLAY_H

typedef enum
{
    NOTE_C,
    NOTE_C_SHARP,
    NOTE_D,
    NOTE_D_SHARP,
    NOTE_E,
    NOTE_F,
    NOTE_F_SHARP,
    NOTE_G,
    NOTE_G_SHARP,
    NOTE_A,
    NOTE_B_FLAT,
    NOTE_B
} NOTE_TYPE;

void play(int note, int octave, int note_value, int tempo);

#endif 
