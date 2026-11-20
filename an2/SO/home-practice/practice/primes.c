
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <signal.h>

int now;
int nr;
int *zonch;

void handler (int signum) {
    zonch[0] = nr;
    zonch[1] = 1;
    zonch[2] = now;
    exit(0);
}

int verifprim(int x) {
    int d;
    if (x < 2) {
        return 0;
    }
    for (d=2; d*d <= x; d++) {
        if (x%d == 0) {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char* argv[]) {
    char shm_name[] = "/myshm";
    char *shm_ptr;
    int shm_fd, i, x;
    
    struct sigaction sa = {0};
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = SIG_IGN;
    sigaction(SIGINT, &sa, NULL);
    
    shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (shm_fd < 0) {
        perror(NULL);
        return errno;
    }

    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    size_t page = getpagesize();
    size_t shm_size = k * page;

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

    int slice = n/k;
    int s, f, t, lung;
    for (t=0; t<k; t++) {
        pid_t pid = fork();
        s = t*slice+1;
        f = (t+1)*slice;
        if (t==k-1) {
            f = n;
        }
        lung = f-s+1;

        if (pid > 0) {
            printf("COPIL: %d, PARINTE: %d\n", pid, getpid());
        } else if (pid==0) {
            zonch = mmap(0, page, PROT_WRITE, MAP_SHARED, shm_fd, t*page);
            if (zonch == MAP_FAILED) {
                perror(NULL);
                exit(errno);
            }
            
            sa.sa_handler = handler;
            sigemptyset(&sa.sa_mask);
            sigaction(SIGINT, &sa, NULL);
            
            nr = 0;
            now = 0;
            zonch[1] = 0;
            for (i=s; i<=f; i++) {
                now = i;
                if (verifprim(i)==1) {
                    nr++;
                }
            }
            zonch[0] = nr;

            munmap(zonch, page);
            exit(0);
        } else {
            perror(NULL);
            return errno;
        }
    }

    for (t=0; t<k; t++) {
        wait(NULL);
    }
    
    int nrtot = 0;
    for (t=0; t<k; t++) {
        int *zonch = (int*)(shm_ptr + t*page);
        nrtot += zonch[0];
        s = t*slice+1;
        f = (t+1)*slice;
        if (t==k-1) {
            f = n;
        }
        printf("copil %d: [%d, %d] a gasit %d numere prime\n", t, s, f, zonch[0]);
        if (zonch[1]==1) {
            printf("si a fost oprit la %d\n", zonch[2]);
        }
    }
    
    printf("in total %d numere prime\n", nrtot);

    munmap(shm_ptr, shm_size);
    shm_unlink(shm_name);
    
    return 0;
}
