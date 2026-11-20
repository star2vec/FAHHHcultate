#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>

void handler (int signum) {
    waitpid(-1, NULL, 0);
}

int main() {
    int nrt, nrsec, i;
    struct sigaction sa = {0};
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGCHLD, &sa, NULL);
    
    printf("me (parent) :3 %d\n", getpid());
    
    nrt = 300;
    for (i=0; i<nrt; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("copil bruh");
            return errno;
        } else if (pid==0) {
            nrsec = i%3+1;
            sleep(nrsec);
            printf("me :3 %d\n", getpid());
            exit(0);
        }
    }
    
    return 0;
}
