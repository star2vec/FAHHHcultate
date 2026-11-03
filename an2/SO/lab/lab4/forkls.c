
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(void) {
	pid_t pid = fork();
	if (pid < 0) {
		return errno;
	} else if (pid == 0) {
		char *argv[] = {"/bin/ls" , NULL};
		execve("/bin/pwd", argv , NULL);
		perror(NULL);
	} else {
		printf("eu: %d copil: %d\n", getpid(), pid);
      	  	pid_t finished = wait(NULL);
          	printf("%d finished\n", finished);
	}
	return 0;
}

