
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/time.h>

int main(int argc, char* argv[]) {
    char shm_name[] = "/myshm";
    char *shm_ptr;
    int shm_fd, i, j, n;
    struct timeval* zonch;
    struct timeval end;
    double timp;
    
    char buf[100];
    char* com[100];
    int nrcom, start;
    
    shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (shm_fd < 0) {
        perror(NULL);
        return errno;
    }

    printf("me %s\n", argv[1]);
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror(argv[1]);
        return errno;
    }
    n = read(fd, buf, sizeof(buf)-1);
    if (n<0) {
        perror(NULL);
        return errno;
    }
    buf[n] = '\0';
    close(fd);
    
    start = 0;
    nrcom = 0;
    for (i=0; i<n; i++) {
        if (buf[i]=='\n') {
            buf[i] = '\0';
            if (i > start) {
                com[nrcom] = buf+start;
                nrcom++;
            }
            start = i+1;
        }
    }
    if (start < n) {
        com[nrcom] = buf+start;
        nrcom++;
    }

    size_t page = getpagesize();
    size_t shm_size = nrcom * page;

    if (ftruncate(shm_fd, shm_size) == -1) {
        perror(NULL);
        shm_unlink(shm_name);
        return errno;
    }

    shm_ptr = mmap(0, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror(NULL);
        shm_unlink(shm_name);
        return errno;
    }

    for (i=0; i<nrcom; i++) {
        pid_t pid = fork();

        if (pid > 0) {
            wait(NULL);
            printf("%s\n", com[i]);
            gettimeofday(&end, NULL);
            zonch = (struct timeval *)(shm_ptr + i * page);
            timp = (end.tv_sec - zonch->tv_sec) + (end.tv_usec - zonch->tv_usec) / 1000000.0;
            printf("de executie: %f s\nde iesire: 0\n\n", timp);
        } else if (pid==0) {
            zonch = mmap(0, page, PROT_WRITE, MAP_SHARED, shm_fd, i*page);
            if (zonch == MAP_FAILED) {
                perror(NULL);
                exit(errno);
            }
            char *args[20];
            int na = 0;
            args[na] = com[i];
            na++;
            for (j = 0; com[i][j] != '\0'; j++) {
                if (com[i][j] == ' ') {
                    com[i][j] = '\0';
                    args[na] = com[i] + j + 1;
                    na++;
                }
            }
            args[na] = NULL;

            gettimeofday(zonch, NULL);
            execve(args[0], args, NULL);
            perror(NULL);
            exit(errno);
        } else {
            perror(NULL);
            return errno;
        }
    }

    munmap(shm_ptr, shm_size);
    shm_unlink(shm_name);
    
    return 0;
}
