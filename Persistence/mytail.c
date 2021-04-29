// mytail: implementation of the tail command
// By: Juan Melo

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {                        // Check if command is used successfully
        printf("Usage: mytail -n FILENAME\n");
        return 0;
    }

    int file;                               // File object
    struct stat statBuff;                   // Buffer to store the size
    char stringBuff[100];                   // String buffer to print the tail

    char *path = argv[2];
    int n = atoi(argv[1]);

    if (stat(path, &statBuff) == -1) printf("Unable to get stats for %s", path);
    unsigned long fileSize = statBuff.st_size;

    file = open(path, O_RDONLY);                // Open file and check if it was opened successfully
    if (file < 0) {
        printf("Could not open file %s\n", path);
        return -1;
    }

    lseek(file, fileSize, SEEK_SET);        // Go to end of file
    // while (n > 0) {

    lseek(file, -100, SEEK_CUR);
    while (read(file, stringBuff, 100)) printf("%s", stringBuff);
    printf("\n%lu\n%i\n", fileSize, n);


    close(file);
    return 0;   
}