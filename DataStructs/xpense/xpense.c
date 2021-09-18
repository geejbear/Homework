#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 10

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
 
    float array[MAX_STACK_SIZE];
    float amount = 0;
    int index = 0;

    // 1. enter amount spent
	while (index < MAX_STACK_SIZE) {
        
        printf("enter the amount spent:\n");
	    scanf("%f", &amount); 
        printf("\n");
        array[index] = amount;
        index++;
    }
    
    //values are temporarily listed on the prompter
    for (int i = 0; i < MAX_STACK_SIZE; i++) { 
        printf("€%.2f\n", array[i]);
    }
    
    // 2. save values in file
	
    #if 1
    FILE * fp;
	fp = fopen("xpense.txt", "w");
	if (fp == NULL) {
		printf("fopen failed");
		return 1;
	}
    
    for (int i = 0; i < MAX_STACK_SIZE; i++) { //list of values are saved in the file
	    fprintf(fp, "€%.2f\n", array[i]);
    }
    
    fclose(fp);
    #endif
    
    //values are added up
    
    for (int i = 0; i < MAX_STACK_SIZE; i++) {
        //the calculation is made with the algorithm for summing all the numbers together
        array[i] = array[i - 1] + array[i]; 
    }
    
    //the total is printed
    
    printf("total: €%.2f\n", array[MAX_STACK_SIZE - 1]);
    

    return 0;
}
