
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>

void collatz(int n) {
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
	return;
}

int main(int argc, char *argv[]) {
	int n, i, k;

	printf("Starting parent %d\n", getpid());	
	for (i=1; i<argc; i++) {
		pid_t pid = fork();
		if (pid < 0) {
			return errno;
		} else if (pid == 0) {
			k = atoi(argv[i]);
			collatz(k);
			printf("Done Parent %d Me %d\n", getppid(), getpid());
			return 0;
		}
		
	}

	for (i=1; i<argc; i++) {
		wait(NULL);
	}
	printf("Done Parent %d Me %d\n", getppid(), getpid());

	
	return 0;
}

