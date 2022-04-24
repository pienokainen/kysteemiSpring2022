#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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
                if (fread(n, 4, 1, fp) != 1) {
                    break;
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
            if (i == argc) {
                break;
            }
        }
    } else {
        printf("my-unzip: file1 [file2 ...]\n");
        exit(1);
    }

}