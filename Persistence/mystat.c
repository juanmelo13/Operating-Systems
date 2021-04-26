// mystat: implementation of the stat command
// By: Juan Melo

#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 2 && argc != 3) {                        // Check if command is used successfully
        printf("Usage: mystat -OPTIONS FILENAME\n");
        return 0;
    }
    printf("Used successfully!\n");

    struct stat buffer;
    char* path;

    
}