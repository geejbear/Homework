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

#include <stdio.h>
#include <dos.h>
#include <math.h>

// =============================================================================
// DEFINES

// =============================================================================
// TYPES / ENUMS

// TODO: use NOTE_...
enum
{
    C,
    CIS,
    D,
    DIS,
    E,
    F,
    FIS,
    G,
    GIS,
    A,
    B,
    H,
};

// =============================================================================
// DATA

//static int bmp = 60; // TODO: maybe this later


// =============================================================================
// PROTOTYPES (function declarations)


// =============================================================================
// PRIVATE FUNCTIONS (private aka static functions)

// =============================================================================
// PUBLIC FUNCTIONS (non-static functions, aka ones that go in the header file)


// TODO: reorder functions into the above categories:


#if 0
// TODO: public function for setting bmp
void set_tempo(int value)
{
    bmp = value;
}
#endif


float freq(int note)
{
    //for pitch...:
    const float half_step = 1.05946f; //in equal temperament
    float freq_ratio = powf(half_step, (float)note);
    float middle_c = 261.626f;
    float frequency = middle_c * freq_ratio;
    return frequency;
}

// TODO: to be removed
int note_value(int value)
{
    switch (value) {
    case 16: return value / 16;   //1
        break;
    case 8: return value / 4;     //2
        break;
    case 4: return value / 1;     //4
        break;
    case 2: return value * 4;     //8
        break;
    case 1: return value * 16;    //16
        break;
    default:
        break;
    }
    return 0;
}

/*
 
 bpm: 60
 
 nv     ms                  calc
 1      4000    * 4.0       4 / 1
 2      2000    * 2.0       4 / 2
 4      1000    * 1.0 <-    4 / 4
 8      500     * 0.5       4 / 8
 16     250     * 0.25      4 / 16
 
 
 */


// TODO: un-hack this
static float notevalue_to_ms(int value, int tempo)
{
    //for rhythm...:

    float std_bps = 60.00f; //bps (standarized for the purpose of this calculation)

    // 4.00 = constant(k)
    float nv = note_value(value); // TODO: use one line calculation (see discord)
    float ms = (nv * 1000.0f) / 4.0f;
    
    //calculating milliseconds... value ∝ 1/ms -> 4, which is our constant
   
    
    
    return std_bps * ms / tempo;  
}


// TODO: octave (C4 = middle)
void play(int note, int octave, int note_value, int tempo)
{
    sound(freq(note), notevalue_to_ms(note_value, tempo));
}


int main()
{
    int tempo;
    printf("How many beats per minute?: ");
    scanf("%d", &tempo);
    
    // TODO: put question after the list
    printf("\nChoose a note and print its number :\n");
    
    // TODO: ?
    // [1] C
    // [2] C sharp
    // [3] D

    printf("\n1.C\t2.CIS\t3.D\t4.DIS\n");
    printf("5.E\t6.F\t7.FIS\t8.G\t\n");
    printf("9.GIS\t10.A\t11.B\t12.H\t\n");
    
    printf("\n");
    
    int input;
    scanf("%d", &input);    

    int num;
    printf("\nPrint a note value from the following options :\n");
    printf("\n1\t2\t4\t8\t16\n");
    
    printf("\n");
    
    scanf("%d", &num);
    
    float frequency = freq(input - 1);
    float ms = notevalue_to_ms(num, tempo);
    
    printf("\nFrequency: %.4f Hz\n", frequency);
    printf("Milliseconds: %.2f\n\n", ms);
    
    // last step in Libdos:
    initdos();
    sound(frequency, ms);
    
    return 0;
}
