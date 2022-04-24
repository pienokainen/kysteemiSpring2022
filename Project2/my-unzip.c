#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
/*
Frisk & Peltonen 
Käyttöjärjestelmät ja systeemiohjelmointi 2022
*/
int main(int argc, char* argv[]) {
    char *c = (char*)malloc(sizeof(char));
               
    if (argc > 1) {
        FILE *fp;
        int i = 1;
        int n[1];
        while (true) {
            if ((fp = fopen(argv[i], "r")) == NULL) {
                fprintf(stderr, "my-unzip: cannot open file.\n");
                exit(1);
            }
            while (true) {
                //reading numbers: if there is no number quit loop
                if (fread(n, 4, 1, fp) != 1) {
                    break;
                //Going through numbers given for each character and then printing them
                } else {
                    if (fread(c, 1, 1, fp) == 1) {
                        for (int j = 0; j < n[0]; j++){
                            printf("%c", c[0]);
                        }
                    } else {
                        break;
                    }
                    
                }
            }
            i++;
            printf("\n");
            if (i == argc) {
                break;
            }
        }
        printf("\n");
        // In case filename is not found:
    } else {
        printf("my-unzip: file1 [file2 ...]\n");
        exit(1);
    }

}