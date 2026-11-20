#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

int main (int argc, char* argv[]) {
    char buf[101];
    int fd1 = open(argv[1], O_RDONLY | O_CREAT, S_IRUSR);
    if (fd1 < 0) {
        perror(argv[1]);
        return errno;
    }
    int fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);
    if (fd2 < 0) {
        perror(argv[2]);
        return errno;
    }
    
    ssize_t n;
    n = read(fd1, buf, 100);
    while (n > 0) {
        write(fd2, buf, n);
        n = read(fd1, buf, 100);
    }
    if (n < 0) {
        perror("read");
        return errno;
    }

    close(fd1);
    close(fd2);
    
    return 0;
}
