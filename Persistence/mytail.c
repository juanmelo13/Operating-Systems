// mytail: implementation of the tail command
// By: Juan Melo

#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2 && argc != 1) {                        // Check if command is used successfully
        printf("Usage: myls -OPTIONS\n");
        return 0;
    }

    return 0;   
}