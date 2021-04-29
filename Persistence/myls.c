// myls: implementation of the ls command
// By: Juan Melo

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

void printStat(char *PATH);

int main(int argc, char *argv[]) {
    if (argc > 3 && argc < 1) {                             // Check if command is used successfully
        printf("Usage: myls (-OPTIONS) (DIRNAME)\n");
        return 0;
    }

    int longer = (argc > 1) ? strcmp("-l", argv[1]) : -1;   // -l command used?
    char* path;                                         

    // Check if -OPTIONS argument is passed, assign path to desired path ("." if ommitted)
    if (longer == 0) 
        path = (argc == 3) ? argv[2] : ".";
    else 
        path = (argc == 2) ? argv[1] : ".";

    
    DIR *d;                                                 // Directory pointer
    if ((d = opendir(path)) == NULL) {                      // Try opening the directory
        printf("Unable to open %s\n", path);
        return 0;
    }
    struct dirent *entry;  

    // Iterate over the files in the directory
    while ((entry = readdir(d)) != NULL) {
        if (longer == 0) {
            printStat(entry->d_name);
            printf(" %s\n", entry->d_name);
        }
        else printf("%-10s", entry->d_name);
    }

    closedir(d);
    return 0;
}

void printStat(char *PATH) {
    struct stat statBuff;                   // Buffer to store the stats
    struct tm *time;                        // Time
    char timeStr[40];
    if (stat(PATH, &statBuff) == -1) printf("Unable to get stats for %s", PATH);

    // Print file stats
    else {
        // Print permissions.
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

        // Print links
        printf(" %lu ", statBuff.st_nlink);

        // Print owner and group
        printf("%u ", statBuff.st_uid);
        printf("%u ", statBuff.st_gid);

        // Print time
        time = localtime(&statBuff.st_mtime);
        strftime(timeStr, 40, "%m %d %H:%M", time);
        printf("%s ", timeStr);

        // Print size
        printf("%6lu", statBuff.st_size);      
    }
}
