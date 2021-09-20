#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 10 // TODO: rename (it's not a stack) MAX_EXPENSES
// TODO: something large like 1000

#if 0
float add(float nums[MAX_STACK_SIZE], float n)
{
    float *sum = malloc( n * sizeof(float));

    for (int i = 0; i < MAX_STACK_SIZE; i++) {
        nums[i] = nums[i - 1] + nums[i]; //the algorithm for summing all the numbers together
        printf("%f\n", nums[i]);
    }    
    
    free(sum);

    return 0;
}
#endif

int main()
{    
    //initializing a new array
 
    float array[MAX_STACK_SIZE]; // more descriptive name: expenses
    float amount = 0;
    int index = 0; // rename: num_expenses

    // TODO: only enter as many expenses as user has/wants
    // 1. enter amount spent
    printf("enter \"0\" to stop\n"); // for example
	while (index < MAX_STACK_SIZE) {
        
        printf("enter the amount spent:\n"); // print once at the start ?
        // for each line: "amount: %f" ?
	    scanf("%f", &amount); 
        printf("\n");
        array[index] = amount;
        index++;
    }
    
    //values are temporarily listed on the prompter
    // TODO: use num_expenses to only print those entered
    for (int i = 0; i < MAX_STACK_SIZE; i++) { 
        printf("€%.2f\n", array[i]);
    }
    
    // 2. save values in file
	
    #if 1
    FILE * fp = fopen("xpense.txt", "w");
	if (fp == NULL) {
		printf("fopen failed\n"); // use fprint and stderr
		return 1;
	}
    
    // TODO: use num_expenses
    for (int i = 0; i < MAX_STACK_SIZE; i++) { //list of values are saved in the file
	    fprintf(fp, "€%.2f\n", array[i]);
    }
    
    fclose(fp);
    #endif
    
    //values are added up
    
    // TODO: int total = 0; // (this is the simplest way, memorize it)
    
    for (int i = 0; i < MAX_STACK_SIZE; i++) {
        //the calculation is made with the algorithm for summing all the numbers together
        array[i] = array[i - 1] + array[i];
        // TODO: total += array[i];
    }
    
    //the total is printed
    
    printf("total: €%.2f\n", array[MAX_STACK_SIZE - 1]);
    

    return 0;
}
