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

    struct stat statBuff;                   // Buffer to store the stats
    char path[156];                         // String to store the path
    strcpy(path, argv[1]);

    if (stat(path, &statBuff) == -1) printf("Unable to get stats for %s", path);

    // Print file stats
    else {                              
        printf("%7s %s\n", "File:", path);
        printf("%7s %-17li", "Size:", statBuff.st_size);
        printf("%7s %li\n", "Blocks:", statBuff.st_blocks);
        printf("%7s %-17lu", "Inode:", statBuff.st_ino);
        printf("%7s %lu\n", "Links:", statBuff.st_nlink);
        printf("%7s (", "Access:");
        printf((S_ISDIR(statBuff.st_mode)) ? "d" : "-");
        printf((statBuff.st_mode & S_IRUSR) ? "r" : "-");
        printf((statBuff.st_mode & S_IWUSR) ? "w" : "-");
        printf((statBuff.st_mode & S_IXUSR) ? "x" : "-");
        printf((statBuff.st_mode & S_IRGRP) ? "r" : "-");
        printf((statBuff.st_mode & S_IWGRP) ? "w" : "-");
        printf((statBuff.st_mode & S_IXGRP) ? "x" : "-");
        printf((statBuff.st_mode & S_IROTH) ? "r" : "-");
        printf((statBuff.st_mode & S_IWOTH) ? "w" : "-");
        printf((statBuff.st_mode & S_IXOTH) ? "x" : "-");
        printf(")\n");
    }
    return 0;
}
