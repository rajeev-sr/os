#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    // Create a new process by calling fork().
    pid_t rc = fork();

    if (rc < 0) {
        // fork() failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // This is the child process.
        execl("/bin/ls","ls", NULL);
    } else {
        // This is the parent process.
        wait(NULL);
        printf("--- Parent process finishing ---\n");
    }

    return 0;
}
