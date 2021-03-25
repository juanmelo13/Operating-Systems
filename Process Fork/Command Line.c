 /*******************************************************
 *                  Author: Juan Melo                   *
 *                      U67631796                       *
 *                                                      *
 * This program takes an input from the command line,   *
 * and creates a new process to execute it.             *
 *******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Not enough arguments\n");
        return -1;
    }

    int rc = fork();            // Fork reference from "Operating Systems: Three Easy Pieces", 
    if (rc < 0) {               // by Remzi H. Arpaci-Dusseau and Andrea C. Arpaci-Dusseau.
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (rc == 0) {       // Child process.
        
        char *cmd = argv[1];    
        char *params[argc];

        // Iterating over the input arguments to save the parameters.
        for (int i = 1; i < argc; i++) {
            params[i-1] = argv[i];
        }
        params[argc - 1] = NULL;

        execvp(cmd, params);

    } else {                    // Parent process.
        wait(NULL);
        printf("++++\n");
    }

    return 0;
}
