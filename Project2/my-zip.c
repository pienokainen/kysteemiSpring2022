#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
/*
Frisk & Peltonen 
Käyttöjärjestelmät ja systeemiohjelmointi 2022
*/
int main(int argc, char* argv[]) {
    if (argc > 1) {
        FILE *fp;
        char prev = '\0'; //variable to compare char c with the previous character (prev)
        char c = '\0';  // character that is being read currently
        int n = 1;
        int i = 1;     
        while (true) {
            //Trying to open inputted file
            if ((fp = fopen(argv[i], "r"))== NULL) {
                printf("my-zip: cannot open file\n");
                exit(1);
            }
            // Gets first character when variable prev is not set
            if (prev == '\0') {
                prev = getc(fp);
            }
            // This checks if character is found
            while ((c = getc(fp)) != EOF){
                //Current character comapred with previous character
                if (c == prev) {
                    
                    n += 1;
                } else {
                    // Writing the character and how many were found
                    fwrite(&n, 4, 1, stdout);
                    fwrite(&prev, 1, 1, stdout);
                    n = 1;
                }
                
                prev = c;
            }
            // The conclusion of characters and how many times each character was present in the file
            if(i == argc - 1) {
                fwrite(&n, 4, 1, stdout);
                fwrite(&prev, 1, 1, stdout);
                n = 1;
            }
            fclose(fp);
            i++;
            if (i == argc) {
                break;
            }
        }
        printf("\n");
        }
        // If a file is not found:
        else {
            printf("my-zip: file1 [file2 ...]\n");
            exit(1); 
        }
    

    return 0;
}


