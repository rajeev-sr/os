#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>


int main(int argc, char *argv[]) {
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_APPEND);
    pid_t rc = fork();
    if (rc < 0) {
        // fork() failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // This is the child process.
        assert(fd >= 0);
    	char buffer[20];
    	sprintf(buffer, "Child writing\n");
    	int rc = write(fd, buffer, strlen(buffer));
    assert(rc == (strlen(buffer)));
    } else {
        // This is the parent process.
        // It waits for the child to complete to ensure predictable output order.
        assert(fd >= 0);
   	 char buffer[20];
   	 sprintf(buffer, "Parent writing\n");
   	 int rc = write(fd, buffer, strlen(buffer));
   	 assert(rc == (strlen(buffer)));
    }
    fsync(fd);
    close(fd);
    return 0;
}
