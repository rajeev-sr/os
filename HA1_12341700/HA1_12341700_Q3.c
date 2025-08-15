#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int fd;
    pid_t pid;

    fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open failed");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }
    else if (pid == 0) { // child
        char msg[] = "Roll Number: 12341700\n";
        write(fd, msg, strlen(msg));
        printf("Child wrote to file.\n");
    }
    else { // parent
        char msg[] = "Name: Rajeev Kumar\n";
        write(fd, msg, strlen(msg));
        printf("Parent wrote to file.\n");
    }

    close(fd);
    return 0;
}
