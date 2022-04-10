#define _GNU_SOURCE // Fixes the problem of not finding getline() function on Linux systems
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Function 1: Read input from user and then print out them in reverse order

// Suomenkieliset kommentit poistetaan ennen palautusta!!
/*Tällä hetkellä (10.4.) funktio pystyy vastaanottamaan hyvin 5 sanaa ja printata nämä
Mutta kun syöttää 6 tulee Segmentation fault loppuun
Ja kun syöttää 7 tulee munmap_chunk(): invalid pointer error
*/
void readInput() {
    char *reversed = NULL;
    char *temp = (char*)malloc((sizeof(char*)+1));
    char *text = (char*)malloc((sizeof(char*)+1));
    while(scanf("%[^\n]%*c",text)==1) {
         if (reversed == NULL) {
            if ((reversed = (char*)malloc((strlen(text)+1))) == NULL) {
                fprintf(stderr, "malloc failed.\n");
                exit(1);
            }
            strcpy(reversed, text);
            strcat(reversed, "\n");
            continue;
        } 
        if ((reversed = (char*)realloc(reversed, (strlen(text)+1)*sizeof(char*))) == NULL) {
            fprintf(stderr, "malloc failed.\n");
            exit(1);
        }
        strcpy(temp, reversed);
        strcpy(reversed, text);
        strcat(reversed, "\n");
        strcat(reversed, temp);
    }
    printf("%s", reversed);
    free(temp);
    free(text); // Jos tän rivin poistaa nii ohjelma vuotaa muistia (tsekattu Valgrindilla)
}

// Function 2: Read a file containing text and then print it on the screen in reverse order
void readFileToScreen(char tiedosto1[]) {
    FILE *fp;
    
    if((fp = fopen(tiedosto1, "r"))==NULL){
		printf("error: cannot open file '%s'", tiedosto1);
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
        
    printf("%s", reversed);
    fclose (fp);
    free(text);
}

// Function 3: Read a file containing text and then print it on the screen and write it on other file reversed
void readAndWrite(char tiedosto1[], char tiedosto2[]) {
    FILE *fp;
    
    if((fp = fopen(tiedosto1, "r"))==NULL){
		printf("error: cannot open file '%s'", tiedosto1);
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
        
    printf("%s", reversed);
    fclose (fp);

    if((fp = fopen(tiedosto2, "w"))==NULL){
		printf("error: cannot open file '%s'", tiedosto2);
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