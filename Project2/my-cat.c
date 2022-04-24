#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
/*
Frisk & Peltonen 
Käyttöjärjestelmät ja systeemiohjelmointi 2022
*/

int main(int argc, char *argv[]) {
    int i = 1;
    FILE *fp;
    char *text = NULL;
    size_t len = 0;
    // Check if there is a file my-cat cannot open
    if (argc == 1) {
        printf("No files provided");
        exit(0);
    }
    //Looping through files that were given as command line arguments
    while(true){
        if ((fp = fopen(argv[i], "r")) ==  NULL) {
            printf("my-cat: cannot open file.\n");
            exit(1);
        }
        // Printing contents
        while ((getline(&text, &len, fp)) != -1) {
            printf("%s", text);
        }
        printf("\n");
        free(text);
        fclose(fp);
        if (argc == i+1) {
            break;
        } else {
            i++;
        }
        
    }
    

    return 0;
}