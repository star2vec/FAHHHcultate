#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>

void handler (int signum) {
    printf ("nu inchid bleh :P\n");
}

int main() {
    
    struct sigaction sa = {0};
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa , NULL);
    
    printf("me :3 %d\n", getpid());
    
    while (1+1==2) {
        sleep(1);
        printf("miau\n");
    }
    
    return 0;
}
