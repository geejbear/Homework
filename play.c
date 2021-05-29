/*
 * Created by Geegbear  
 * 29/05/2021  
 * "Frequency/millisecond calculator"
 * To be implemented along the function 'sound(...)' from the LibDos turbo C Library    
 * Such implementation has not yet been tested!
 * 
 */   


#include <stdio.h>
#include <dos.h>
#include <math.h>

typedef struct 
{
    float whole;        //2^5
    float minim;        //2^4
    float crochet;      //2^2
    float crochet_d;    // 3/2 (1.50)
    float quaver;       // 2
    float quaver_d;     // 3/4 (0.75)    
    float semi_quaver;  // 1/2 (0.50)
} duration_t;

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


const float metronome = 60.0f;// variable in bps(beats per second)


float freq(float note)
{
    //for pitch...:
    const float half_step = 1.05946f; //in equal temperament
    float freq_ratio = pow(half_step, note);    
    float middle_c = 261.626f;
    float frequency = middle_c * freq_ratio;
    return frequency; 
}


float beat(float length) //
{
    //for rhythm...:
    float std_bps = 60.00f; //bps (standarized for the purpose of this calculation)

    // 4.00 = constant(k)
    float ms = (length * 1000.00f) / 4.00f; 

    //calculating milliseconds... length ∝ 1/ms -> 4, which is our constant
   
    return std_bps * ms / metronome;  //TODO: do inverse proportion of this value against variable declaration 'float length', 
                                      // and call it "float x" before calling the return value.
}
  
int main()
{
    
    printf("%f\n", freq(A));
    printf("%f\n", beat(5.0f));
    // last step in Libdos: sound(frequency, milliseconds);
    
    return 0;
}
