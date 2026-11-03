
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int n;

	n = atoi(argv[1]);

	pid_t pid = fork();
	if (pid < 0) {
		return errno;
	} else if (pid == 0) {
		printf("%d: %d ", n, n);
      		while (n > 1) {
            		if (n%2 == 0) {
				n = n/2;
			} else {
				n = 3*n+1;
			}
			printf("%d ", n);
		}
		printf("\n");
	} else {
      	  	pid_t finished = wait(NULL);
          	printf("Child %d finished\n", finished);
	}
	return 0;
}

