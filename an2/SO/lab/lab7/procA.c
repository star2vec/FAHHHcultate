#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int fd1 = open("fifo1", O_RDWR);
    int fd2 = open("fifo2", O_RDWR);
    char buf[100];

    while (1+1==2) {
        printf("A: ");
        fflush(stdout);

        scanf("%s", buf);
        write(fd1, buf, strlen(buf)+1);

        read(fd2, buf, sizeof(buf));
        printf("from B: %s\n", buf);
    }

    close(fd1);
    close(fd2);
}