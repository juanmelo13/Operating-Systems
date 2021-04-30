// mysearch: implementation of a recursive printing algorithm
// By: Juan Melo

#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

int dirPrint(char* PATH, int level) {
    struct stat statBuff;                                   // Buffer to store the stats
    char buff[256];                                         // Char buffer in case PATH is directory

    DIR *d;                                                 // Directory pointer
    if ((d = opendir(PATH)) == NULL) {                      // Try opening the directory
        printf("Unable to open %s\n", PATH);
        return 0;
    }
    struct dirent *entry;  

    // Iterate over the files in the directory
    while ((entry = readdir(d)) != NULL) {
        // Check if entry is the root
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;

        // Print identation
        for (int i = 0; i < level; i++)
            printf("    ");

        printf("%-10s\n", entry->d_name);                   // Print the entry name

        // Get stats to check if the entry is a directory
        strcpy(buff, PATH);
        strcat(buff, "/");
        strcat(buff, entry->d_name);

        if (stat(buff, &statBuff) == -1) {
            printf("Unable to get stats for %s\n", entry->d_name);
        }
        else if (S_ISDIR(statBuff.st_mode)) {
            
            dirPrint(buff, level + 1);
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2 && argc != 1) {                        // Check if command is used successfully
        printf("Usage: mysearch (DIRNAME)\n");
        return 0;
    }

    char *path = (argc == 2) ? argv[1] : ".";           // Root path
    dirPrint(path, 0);    

    return 0;
}