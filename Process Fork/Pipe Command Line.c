 /*******************************************************
 *                  Author: Juan Melo                   *
 *                      U67631796                       *
 *                                                      *
 * This program takes an input from the command line,   *
 * and creates a two process to execute them in pipe.   *
 *******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Not enough arguments\n");
        exit(1);
    }

    // Creating the pipe.
    int fd[2];
    int pipe1 = pipe(fd);

    if (pipe1 < 0) {
        fprintf(stderr, "Pipe failed\n");
        exit(1);
    }

    // Creating t
    int rc1 = fork();

    if (rc1 < 0) {              
        fprintf(stderr, "Fork failed\n");
        exit(1);

    } else if (rc1 == 0) {       // Process 1 (cmd 1)
        close(fd[0]);            // Close unused read end.

        char *cmd = argv[1];
        // printf("process 1 ran %s\n", cmd);
        
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);

        execlp(cmd, cmd, NULL);

    }

    int rc2 = fork(); 

    if (rc2 < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(1);

    } else if (rc2 == 0) {      // Process 2 (cmd 2)
        close(fd[1]);           // Close unused write end.

        char *cmd = argv[3];
        // printf("process 2 ran %s\n", cmd);        

        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);

        execlp(cmd, cmd, NULL);

    }
    
    // Parent process.
    close(fd[0]);
    close(fd[1]);

    waitpid(rc1, NULL, 0);
    waitpid(rc2, NULL, 0);

    printf("++++\n");
    return 0;
}
