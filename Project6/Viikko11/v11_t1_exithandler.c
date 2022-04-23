/*
1.	Write a program which opens a temporary file, writes lines to it once a second for 30 seconds, and then quits.
2.	Then add an exit handler function which deletes the temporary file (hint: atexit() and unlink()). 
Why the temporary file is not deleted if the program is terminated with kill command? Or with ctrl-c?
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define MAX 512

void bye(FILE *tmp) {
    int status = unlink(tmp);
    if (status != 0) {
        printf("Something went wrong with unlinking! %s\n", strerror(errno));
    }
    else {
        printf("That was all!\n");
    }
}

void main() {
    char line[MAX];
    FILE *tmp, *stories;
    int i = 0;

    // Error handling while creating / opening files
    tmp = tmpfile();
    if (tmp == NULL) {
        perror("Creating temp file failed");
        exit(0);
    }

    stories = fopen("stories.txt", "r");
    if (stories == NULL) {
        perror("File stories.txt doesn't exist.");
        exit(1);
    }

    // Loop to write from stories.txt to tmp file

    for (i=0; i < 30; i++) {
        while (fgets(line, sizeof(line), stories) != NULL) {
            fputs(line, tmp);
            printf("%s", line);
            sleep(1);
        }
    }
    printf("\n");

    // Closing the files
    fclose(tmp);
    fclose(stories);

    int status = atexit((bye(tmp)));
    if (status != 0) {
        fprintf(stderr, "cannot set exit function\n");
    }
}