// TODO: move file header here: info for users of this module

#ifndef PLAY_H
#define PLAY_H

// TODO: typedef it!
enum
{
    NOTE_C,
    NOTE_CIS,
    NOTE_D,
    NOTE_DIS,
    NOTE_E,
    NOTE_F,
    NOTE_FIS,
    NOTE_G,
    NOTE_GIS,
    NOTE_A,
    NOTE_B,
    NOTE_H,
};

void play(int note, int octave, int note_value, int tempo);

#endif 
