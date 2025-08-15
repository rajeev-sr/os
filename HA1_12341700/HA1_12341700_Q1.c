#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int x = 10; // global variable

int main() {
    printf("Initial value of x: %d\n", x);
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } 
    else if (pid == 0) { // child
        x += 10;
        printf("Child: x = %d\n", x);
        printf("Child: My change does NOT affect parent.\n");
    } 
    else { // parent
        x += 5;
        printf("Parent: x = %d\n", x);
        printf("Parent: My change does NOT affect child.\n");
    }

    return 0;
}
