#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int main () {
    pid_t pid = fork();
    
    if (pid>0) {
        printf("My PID=%d, Child PID=%d\n", getpid(), pid);
        wait(NULL);
        printf("Child %d finished\n", pid);
    } else if (pid==0) {
        char *argv [] = {"ls" , NULL};
        execve("/bin/ls", argv, NULL);
        perror(NULL);
        return errno;
    } else {
        perror("idk");
        return errno;
    }
    
    return 0;
}
