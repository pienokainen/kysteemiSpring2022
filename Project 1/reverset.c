#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void readInput();
void readFileToScreen();
void readAndWrite();
int main(int argc, char *argv[]) {
    if (argc == 1) {
        readInput();
    } else if (argc == 2) {
        readFileToScreen(argv[1]);
    } else if (argc == 3) {
        readAndWrite(argv[1], argv[2]);
    } else if (argv[2] == argv[3]) {
        fprintf(stderr, "Input and output file must differ\n");
        exit(1);
    } else {
        printf("usage: reverse <input> <output>\n");
    }
}

void readInput() {

}

void readFileToScreen(char tiedosto1[]) {
    FILE *fp;
    
    if((fp = fopen(tiedosto1, "r"))==NULL){
		fprintf(stderr, "error: cannot open file '%s'\n", tiedosto1);
		exit(1);
	}
    
    char *text = NULL;
    char *reversed = NULL;
    size_t len = 0;
    int i = 0;
    while ((getline(&text, &len, fp)) != -1) {
        if (reversed == NULL) {
            if ((reversed = (char*)malloc(strlen(text)+1)) == NULL) {
                fprintf(stderr, "malloc failed\n");
                exit(1);
            }
            strcpy(reversed, text);
            continue;
        }
        if ((reversed = (char*)realloc(reversed, strlen(text)+1)) == NULL) {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }
        char *temp;
        if ((temp = (char*)malloc(strlen(reversed))) == NULL) {
            fprintf(stderr, "malloc failed\n");
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
        
    printf("\n%s", reversed);
    fclose (fp);
    free(text);
    free(reversed);
    
}


void readAndWrite(char tiedosto1[], char tiedosto2[]) {
    FILE *fp;
    
    if((fp = fopen(tiedosto1, "r"))==NULL){
		fprintf(stderr, "error: cannot open file '%s'\n", tiedosto1);
		exit(1);
	}
    
    char *text = NULL;
    char *reversed = NULL;
    size_t len = 0;
    int i = 0;
    while ((getline(&text, &len, fp)) != -1) {

        if (reversed == NULL) {
            if ((reversed = (char*)malloc(strlen(text)+1)) == NULL) {
                fprintf(stderr, "malloc failed\n");
                exit(1);
            }
            strcpy(reversed, text);
            continue;
        } 
        if ((reversed = (char*)realloc(reversed, strlen(text)+1)) == NULL) {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }

        char *temp;
        if ((temp = (char*)malloc(strlen(reversed))) == NULL) {
            fprintf(stderr, "malloc failed\n");
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
        
    printf("\n%s", reversed);
    fclose (fp);

    if((fp = fopen(tiedosto2, "w"))==NULL){
		fprintf(stderr,"error: cannot open file '%s'\n", tiedosto2);
		exit(1);
	}
    fprintf(fp, "%s", reversed);
    free(text);
    free(reversed);
}

