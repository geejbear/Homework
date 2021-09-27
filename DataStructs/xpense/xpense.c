#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_ARRAY_SIZE 10

enum
{
    MENU_ENTER_AMOUNT = 1,
    MENU_DISPLAY_AMOUNTS,
    MENU_COUNT,

};

char *menu[] = {"Enter amount", "Display amounts"};

void PrintMenu()
{
    for (int i = 0; i < MENU_COUNT - 1; i++) {
        printf("\n[%d]%s\n", i + 1, menu[i]);
    }
}

int main()
{    
    //initializing a new array
    
    float array[MAX_ARRAY_SIZE] = {0};
    float amount = 00.00;
    float total = 00.00;
    
    int index = 0;
    bool running = true;
        
    
    // 1. enter amount spent
	while ( running ) {
        
        PrintMenu();
        
        int key;
        scanf("%d", &key);
        
        switch (key) {

            case MENU_ENTER_AMOUNT:
                if (key == 1) {
                    printf("Amount: ");
	                scanf("%f", &amount); 
                    array[index] = amount;
                    index++;
                    if (amount == 0 || index >= MAX_ARRAY_SIZE) {
                        printf("quiting...");
                        return 0;
                    }
                    break;
                }    
            case MENU_DISPLAY_AMOUNTS:
                if (key == 2) {
                    
                    total = 0;
                   
                    for (int i = 0; i < MAX_ARRAY_SIZE; i++) { 
                        printf("€%.2f\n", array[i]);
                        total += array[i]; 
                    }
                    printf("\ntotal:\n €%.2f\n", total);
                }
                FILE * fp;
	            fp = fopen("xpense.txt", "w");
	            if (fp == NULL) {
	            	printf("fopen failed");
	            	return 1;
	            }

                for (int i = 0; i < MAX_ARRAY_SIZE; i++) { //list of values are saved in the file
	                fprintf(fp, "€%.2f\n", array[i]);
                }

                fprintf(fp, "\ntotal:\n€%.2f\n", total);
            
                fclose(fp);
                    
                break; 
            
            default: break;
        }
    }

    return 0;
}