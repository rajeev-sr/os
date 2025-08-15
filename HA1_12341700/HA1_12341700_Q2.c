#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid1, pid2;

    pid1 = fork(); // first fork

    pid2 = fork(); // second fork

    printf("PID: %d, Parent PID: %d\n", getpid(), getppid());

    return 0;
}
