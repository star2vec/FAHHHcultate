
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	char shm_name[] = "/myshm";
    char *shm_ptr;
	int shm_fd, t, i, pid, x;

    int parentid = getpid();
	printf("Starting parent: %d\n", parentid);
    fflush(stdout);
	
	shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (shm_fd < 0) {
        perror(NULL);
        return errno;
    }

    int n = argc - 1;
    size_t page = getpagesize();
	size_t shm_size = n * page;

	if (ftruncate(shm_fd, shm_size) == -1) {
        perror(NULL);
        shm_unlink(shm_name);
        return errno;
    }

	shm_ptr = mmap(0, shm_size, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror(NULL);
        shm_unlink(shm_name);
        return errno;
    }

    for (t=0; t<n; t++) { 
        pid = fork();

        if (pid==0) {
            int* zonch = mmap(0, page, PROT_WRITE, MAP_SHARED, shm_fd, t*page);
            if (zonch == MAP_FAILED ) {
                perror(NULL);
                shm_unlink(shm_name);
                exit(errno);
            }  

            x = atoi(argv[t+1]);
            zonch[0] = x;
            i = 1;
            while (zonch[i-1]!=1) {
                if (x%2==0) {
                    x = x/2;
                } else {
                    x = 3*x+1;
                }
                zonch[i] = x;
                i++;
            }
            zonch[i] = 0;

            printf("Done Parent %d Me %d\n", getppid(), getpid());
            munmap(zonch, page);
            exit(0);
        }
    }

    for (t=0; t<n; t++) {
        wait(NULL);
    }

    for (t=0; t<n; t++) {
        int *zonch = (int*)(shm_ptr + t*page);
        printf("%s:", argv[t+1]);
        i=0;
        while (zonch[i]!=0) {
            printf(" %d", zonch[i]);
            i++;
        }
        printf("\n");
    }

    munmap(shm_ptr, shm_size);
    shm_unlink(shm_name);
    printf("Done Parent %d Me %d\n", getppid(), parentid);
	
	return 0;
}