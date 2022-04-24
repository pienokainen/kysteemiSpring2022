#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    char *text = NULL;
    size_t len = 0; 
    int i = 2;
    if (argc > 2) {
        while (i+1 <= argc) {
            printf("%i \n",i);
            if ((fp = fopen(argv[i], "r")) == NULL) {
                printf("my-grep: cannot open file.\n");
                exit(1);
            }
            while ((getline(&text, &len, fp)) != -1) {
                if (strstr(text, argv[1])) {
                    printf("%s", text);
                }
            
            }


            free(text);
            fclose(fp); 
            
            i++;
        }
    }
    
    else if (argc == 2) {
        
          // As long as user does not press enter two times (two \n) we ask for input
        while((getline(&text, &len, stdin)) != -1) {
            if (strstr(text, argv[1])!= NULL) {
                printf("%s", text);
            }
            if (strcmp(text, "\n") == 0) {
                break;
            }
        }

        
        }
    else {
        printf("my-grep: searchterm [file ...]");
        exit(1);
    }
    return 0;
}