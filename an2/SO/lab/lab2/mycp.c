#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	int nrb, nrw, file1, file2;
	char citire[4096];

	if (argc!=3) {
		write(1, "argumente faulty\n", 17);
		return errno;
	}

	file1 = open(argv[1], O_RDONLY|O_TRUNC);
	if (file1==-1) {
		write(1, "fisier faulty\n", 16);
		return errno;
	}

	file2 = open(argv[2], O_WRONLY);
	if (file2==-1) {
		write(1, "fisier faulty\n", 14);
		return errno;
	}


	nrb = 32;
	while (nrb!=0) {
		nrb = read(file1, citire, sizeof(citire));
		if (nrb < 0) {
			write(1,"eroare citire\n", 14);
			return errno;
		}
		nrw = write(file2, citire, nrb);
		if (nrw < 0) {
			write(1,"eroare scriere\n", 15);
			return errno;
		}
	}

	close(file1);
	close(file2);

	return 0;
}

