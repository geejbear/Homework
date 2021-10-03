#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_ARRAY_SIZE 100

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
    float expenses[MAX_ARRAY_SIZE] = {'\0'};
    float amount = 00.00;
    float total = 00.00;
    
    int expense = 0;
    bool running = true;

    FILE * fp;
    fp = fopen("xpense.txt", "r");

    if (fp != NULL) {
        printf("laoding amounts from file...\n");
    }

    for (int i = 0; i < MAX_ARRAY_SIZE; i++) { 
	    fscanf(fp, "€%f\n", &expenses[i]);
        if (expenses[i] != 00.00) {
            expense++;
        }
    }

    fscanf(fp, "\ntotal:\n€%f\n", &total);
            
    fclose(fp);    
    
	while ( running ) {
        
        PrintMenu();
        
        int key;
        scanf("%d", &key);
        
        switch (key) {

            case MENU_ENTER_AMOUNT:
                if (key == 1) {
                    printf("Amount: ");
	                scanf("%f", &amount); 
                    expenses[expense] = amount;
                    expense++;
                }
                

                if (amount == 0 || expense >= MAX_ARRAY_SIZE) {
                    printf("quiting...");
                    return 0;
                }
                
                FILE * fp;
                fp = fopen("xpense.txt", "w");

	            if (fp == NULL) {
	            	printf("fopen failed");
	            	return 1;
                }
                for (int i = 0; i < expense; i++) { 
	                fprintf(fp, "€%.2f\n", expenses[i]);
                }
                fprintf(fp, "\ntotal:\n€%.2f\n", total);

                fclose(fp);
                
                break;
       
            case MENU_DISPLAY_AMOUNTS:
                if (key == 2) {
                    
                    total = 0;
                   
                    for (int i = 0; i < expense; i++) { 
                        printf("€%.2f\n", expenses[i]);
                        total += expenses[i]; 
                    }
                    printf("\ntotal:\n €%.2f\n", total);
                }
                
                    
                break; 
            
            default: break;
        }
    }

    return 0;
}