#include<stdlib.h>
#include<stdio.h>
#include <stdbool.h>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        FILE *fp;
        char lc = '\0';
        char c = '\0';  
        int n = 1;
        int i = 1;     
        while (true) {
            if ((fp = fopen(argv[i], "r"))== NULL) {
                printf("my-zip: cannot open file\n");
                exit(1);
            }
            if (lc == '\0') {
                lc = getc(fp);
            }
                
            while ((c = getc(fp)) != EOF){
                if (c == lc) {
                    
                    n += 1;
                } else {
                    
                    fwrite(&n, 4, 1, stdout);
                    fwrite(&lc, 1, 1, stdout);
                    n = 1;
                }
                
                lc = c;
            }
            
            if(i == argc - 1) {
                fwrite(&n, 4, 1, stdout);
                fwrite(&lc, 1, 1, stdout);
                n = 1;
            }
            fclose(fp);
            i++;
            if (i == argc) {
                break;
            }
        }
        }
        else {
            printf("my-zip: file1 [file2 ...]\n");
            exit(1); 
        }
    

    return 0;
}


//if (argc == 1) {
        
    //     printf("my-zip: file1 [file2 ...]\n");
    //     exit(1);