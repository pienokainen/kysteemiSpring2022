#define _GNU_SOURCE // Fixes the problem of not finding getline() function on Linux systems
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Function 1: Read input from user and then print out them in reverse order
void readInput() {
    char *reversed = NULL;
    char *temp = NULL;
    char *text = NULL;
    
    // Allocate memory for user input
    if ((text = (char*)malloc((sizeof(char*)+1))) == NULL) {
        fprintf(stderr, "malloc failed.\n");
        exit(1);
    }

    // As long as user does not press enter two times (two \n) we ask for input
    while(scanf("%[^\n]%*c",text)==1) {
        if (reversed == NULL) {
            if ((reversed = (char*)malloc((strlen(text)+1))) == NULL) { // +1 to have enough room from strlen
                fprintf(stderr, "malloc failed.\n");
                exit(1);
            }
            strcpy(reversed, text);
            strcat(reversed, "\n");
            continue;
        }
        // Allocate memory for temp to have the combined memory of reversed and text
        if ((temp = (char*)malloc((strlen(reversed)+1)+(strlen(text)+1))) == NULL) {
            fprintf(stderr, "malloc failed.\n");
            exit(1);
        }
        // We copy data from reversed to temp and then free reversed to malloc it again
        strcpy(temp, reversed);
        free(reversed);
        reversed = NULL;

        if ((reversed = (char*)malloc(((strlen(text)+1)+(strlen(temp)+1))*sizeof(char))) == NULL) {
            fprintf(stderr, "malloc failed.\n");
            exit(1);
        }

        strcpy(reversed, text);
        strcat(reversed, "\n");
        strcat(reversed, temp);
        free(temp);
    }
    printf("%s", reversed);
    free(text);
}

// Function 2: Read a file containing text and then print it on the screen in reverse order
void readFileToScreen(char tiedosto1[]) {
    FILE *fp;
    
    if((fp = fopen(tiedosto1, "r"))==NULL){
		fprintf(stderr, "cannot open file '%s'\n", tiedosto1);
		exit(1);
	}
    
    char *text = NULL;
    char *reversed = NULL;
    size_t len = 0;
    char *temp;
    while ((getline(&text, &len, fp)) != -1) {
        if (reversed == NULL) {
            reversed = (char*)malloc(strlen(text)+1);
            strcpy(reversed, text);
            continue;
        } 
        if ((reversed = (char*)realloc(reversed, (strlen(text)+1)*sizeof(char*))) == NULL) {
            fprintf(stderr, "malloc failed.\n");
            exit(1);
        }
        if ((temp = (char*)malloc(strlen(reversed)+1)) == NULL) {
            fprintf(stderr, "malloc failed.\n");
            exit(1);
        }
        
        strcpy(temp, reversed);
        strcpy(reversed, text);
        if (reversed[strlen(text)-1] != '\n') {
            strcat(reversed, "\n");
        }
        
        strcat(reversed, temp);
        free(temp);
    }
        
    printf("%s", reversed);
    fclose (fp);
    free(text);
}

// Function 3: Read a file containing text and then print it on the screen and write it on other file reversed
void readAndWrite(char tiedosto1[], char tiedosto2[]) {
    FILE *fp;
    
    if((fp = fopen(tiedosto1, "r"))==NULL){
		fprintf(stderr, "cannot open file '%s'\n", tiedosto1);
		exit(1);
	}
    
    char *text = NULL;
    char *reversed = NULL;
    size_t len = 0;
    char *temp;
    while ((getline(&text, &len, fp)) != -1) {
        if (reversed == NULL) {
            reversed = (char*)malloc(strlen(text)+1);
            strcpy(reversed, text);
            continue;
        }
        if ((reversed = (char*)realloc(reversed, (strlen(text)+1)*sizeof(char*))) == NULL) {
            fprintf(stderr, "malloc failed.\n");
            exit(1);
        }
        if ((temp = (char*)malloc(strlen(reversed))) == NULL) {
            fprintf(stderr, "malloc failed.\n");
            exit(1);
        }
        strcpy(temp, reversed);
        strcpy(reversed, text);
        if (reversed[strlen(text)-1] != '\n') {
            strcat(reversed, "\n");
        }
        
        strcat(reversed, temp);
        free(temp);
    }
        
    printf("Input in file '%s' was successfully printed to file '%s'.\n", tiedosto1, tiedosto2);
    fclose (fp);

    if((fp = fopen(tiedosto2, "w"))==NULL){
		fprintf(stderr, "cannot open file '%s'\n", tiedosto2);
		exit(1);
	}
    fprintf(fp, "%s", reversed);
    free(text);
    
}

// Main function to handle different amount of command line arguments
int main(int argc, char *argv[]) {
    if (argc == 1) {
        readInput();
    } else if (argc == 2) {
        readFileToScreen(argv[1]);
    } else if (argc == 3) {
        if (strcmp(argv[1],argv[2]) == 0) {
            fprintf(stderr, "Input and output files must differ.\n");
            exit(1);
        } 
        readAndWrite(argv[1], argv[2]);
    } else {
        printf("usage: reverse <input> <output>");
    }
    
}