/*
 * Created by Geegbear  
 * 29/05/2021  
 * "Frequency/millisecond calculator"
 * To be implemented along the function 'sound(...)' from the LibTC
 * Such implementation has not yet been tested!
 * 
 */   

#include <stdio.h>
#include <dos.h>
#include <math.h>

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

// TODO: call it 'bpm' or 'tempo'


float freq(int note)
{
    //for pitch...:
    const float half_step = 1.05946f; //in equal temperament
    float freq_ratio = powf(half_step, (float)note);
    float middle_c = 261.626f;
    float frequency = middle_c * freq_ratio;
    return frequency;
}

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
// naming: value -> note_value, beat -> notevalue_to_ms
float beat(int value, int tempo)
{
    //for rhythm...:

    float std_bps = 60.00f; //bps (standarized for the purpose of this calculation)

    // 4.00 = constant(k)
    float ms = (note_value(value) * 1000.00f) / 4.00f;
    
    //calculating milliseconds... value ∝ 1/ms -> 4, which is our constant
   
    return std_bps * ms / tempo;  
}

int main()
{
    int tempo;
    printf("How many beats per minute? :\n");
    scanf("%d", &tempo);

    printf("\nChoose a note and print its number :\n");
    
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
    
    printf("\n");
    printf("Frequency: %.4f Hz\n", freq(input - 1));
    printf("Milliseconds: %.2f\n", beat(num, tempo));
    printf("\n");
    // last step in Libdos: sound(frequency, milliseconds);
    
    return 0;
}
