#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    int fd[2];
    pid_t pid;
    int sum, i, x;

    if (pipe(fd) < 0) {
        perror("pipe");
        return errno;
    }

    pid = fork();
    if (pid < 0) {
        perror("fork");
        return errno;
    }

    if (pid == 0) {
        close(fd[1]);

        sum = 0;
        while (read(fd[0], &x, sizeof(int)) > 0) {
            sum += x;
        }
        
        printf("%d\n", sum);
        close(fd[0]);
    } else {
        close(fd[0]);

        for (i=1; i<argc; i++) {
            x = atoi(argv[i]);
            write(fd[1], &x, sizeof(int));
        }
        close(fd[1]);
        wait(NULL);
    }

    return 0;
}