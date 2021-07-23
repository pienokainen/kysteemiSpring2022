#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


void readInput();
void readFileToScreen();
void readAndWrite();
int main(int argc, char *argv[]) {
    if (argc == 1) {
        //readInput();
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

// void readInput() {
//     char *text = NULL;
//     size_t len = 0;
//     size_t read;
//     char *reversed;
//     while ((read = getline(&text, &len, stdin)) != -1 || len == 1) {
//         printf("%s", text);
//         if (reversed == NULL) {
//             reversed = (char*)malloc(strlen(text)+1);
//             strcpy(reversed, text);
//             continue;
//         } 
//         reversed = (char*)realloc(reversed, strlen(text)+1);
//         char *temp = (char*)malloc(strlen(reversed));
//         strcpy(temp, reversed);
//         strcpy(reversed, text);
//         if (reversed[strlen(text)-1] != '\n') {
//             strcat(reversed, "\n");
//         }
        
//         strcat(reversed, temp);
//         free(temp);
//     }
//     free(text);
//     fclose(stdin);
// }

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
        if ((reversed = (char*)realloc(reversed, strlen(text)+1)) == NULL) {
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
    free(reversed);
    
    
}


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
        if ((reversed = (char*)realloc(reversed, strlen(text)+1)) == NULL) {
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
    free(reversed);
}

