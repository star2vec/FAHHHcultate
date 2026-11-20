#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {	
    int n;
    
    n = atoi(argv[1]);
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
    } else {
        wait(NULL);
        printf("Child %d finished\n", pid);
    }
    
    return 0;
}
