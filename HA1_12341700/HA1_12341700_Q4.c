#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
    pid_t pid1, pid2;

    pid1 = fork(); // First fork for first child

    if (pid1 < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid1 == 0) {
        // First child process
        printf("PID: %d, Parent PID: %d – I am first child\n", getpid(), getppid());
    } 
    else {
        // Only parent executes second fork
        pid2 = fork();

        if (pid2 < 0) {
            perror("fork failed");
            exit(1);
        }

        if (pid2 == 0) {
            // Second child process
            printf("PID: %d, Parent PID: %d – I am second child\n", getpid(), getppid());
        } 
        else {
            // Parent process
            printf("PID: %d, Parent PID: %d – I am Rajeev Kumar (parent)\n", getpid(), getppid());

            // Summary
            printf("Total number of processes = 3 (1 parent + 2 children)\n");
        }
    }

    return 0;
}
