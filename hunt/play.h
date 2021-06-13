#ifndef PLAY_H
#define PLAY_H
#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include <math.h>
#include <stdbool.h>

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

float freq(int note, int oct);
int clamp(int value, int min, int max);
float octave(int oct);
float notevalue_to_ms(int value, int tempo); //made this  public because play() uses it. 
void play(int note, int octave, int note_value, int tempo);

#endif 