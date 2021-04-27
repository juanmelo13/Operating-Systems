// myls: implementation of the ls command
// By: Juan Melo

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc > 4 && argc < 1) {                        // Check if command is used successfully
        printf("Usage: myls -OPTIONS DIRNAME\n");
        return 0;
    }

    char* path = ".";
    int longer = strcmp("-l", argv[1]);
    printf("%i\n", longer);

    if (longer == 0) {
        
    }

    return 0;
}