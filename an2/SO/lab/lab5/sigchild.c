#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>

int nr;

void handler(const int signum) {
    int pid;
	pid = waitpid(-1, NULL, 0);
	while (pid > 0) {
		nr++;
		printf("copil cleared: %d (%d so far)\n", pid, nr);

		pid = waitpid(-1, NULL, 0);
	}
}

int main(void) {
	struct sigaction sa = {0};
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGCHLD, &sa, NULL);

	int i, NUMCH, pid;

	NUMCH = 300;
	for (i=0; i<NUMCH; i++) {
		pid = fork();
		if (pid == 0) {
			sleep(3);
			exit(0);
		}
	}

	i = 0;
	while (1+1==2) {
		if (i%2763873==0) {
			printf("A");
		}
		i++;
		i%=2763875;
	}

	return 0;
}

