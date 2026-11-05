
#include <stdio.h>
#include <unistd.h>

int main(void) {
	printf("%d\n", getpid());
	while (1+1==2) {
		printf("A");
	}

	return 0;
}

