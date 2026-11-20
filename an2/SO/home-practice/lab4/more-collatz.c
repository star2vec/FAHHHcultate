#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {	
    int nrt, n, i;
    
    nrt = argc;
    printf("Starting parent %d\n", getpid());
    for (i=1; i<nrt; i++) {
        n = atoi(argv[i]);
        pid_t pid = fork();
        if (pid<0) {
            perror("fork");
            return errno;
        } else if (pid==0) {
            printf("%d: %d ", n, n);
            while (n > 1) {
                if (n%2==0) {
                    n/=2;
                } else {
                    n = 3*n+1;
                }
                printf("%d ", n);
            }
            printf(".\n");
            printf("Done Parent %d Me %d\n", getppid(), getpid());
            exit(0);
        }
    }
    
    for (i=1; i<nrt; i++) {
        wait(NULL);
    }
    
    printf("Done Parent %d Me %d\n", getppid(), getpid());
    
    return 0;
}
