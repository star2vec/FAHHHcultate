#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handler (const int signum) {
	printf ("signal: %d -> not stopping!! :P\n" , signum);
}

int main(void) {
	printf("%d\n", getpid());

	struct sigaction sa = {0};
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);

	int i;
	i = 0;
	while (1+1==2) {
		if (i%27638==0) {
			printf("A");
		}
		i++;
		i%=2763875;
	}

	return 0;
}

