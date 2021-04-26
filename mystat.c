// mystat: implementation of the stat command
// By: Juan Melo

#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {                        // Check if command is used successfully
        printf("Usage: mystat -OPTIONS FILENAME\n");
        return 0;
    }
    printf("Used successfully!\n");

    struct stat statBuff;                     // Buffer to store the stats
    char* path;                             // String to store the path
    strcpy(argv[1], path);

    if (stat(path, &statBuff) == -1) printf("Unable to get stats for %s", path);
    else {
        
    }
    return 0;
}
