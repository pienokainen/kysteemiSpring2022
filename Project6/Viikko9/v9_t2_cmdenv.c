#include <stdio.h>
#include <stddef.h>

int main(int argc, char* argv[], char* envp[]) {
    int i;
    
    printf("Command line variables: ");
    for (i=0; argv[i] != NULL; i++) {
        printf("\n%s", argv[i]);
    }

    printf("\nEnvironment variables:");
    for (i = 0; envp[i] != NULL; i++) {
        printf("\n%s", envp[i]);
    }
    printf("\n");

    return 0;
}