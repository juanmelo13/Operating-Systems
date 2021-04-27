// myls: implementation of the ls command
// By: Juan Melo

#include <stdio.h>
#include <string.h>
#include <dirent.h>

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
    if ((d = opendir(path)) == NULL) {
        printf("Unable to open %s\n", path);
        return 0;
    }
    struct dirent *entry;  

    while ((entry = readdir(d)) != NULL) {
        if (longer == 0) {
            printStat(entry->d_name);
        }
        printf("%s\n", entry->d_name);
    }

    closedir(d);
    return 0;
}

void printStat(char *PATH) {
    
}
