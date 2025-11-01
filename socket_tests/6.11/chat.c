#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <errno.h>


int main(int argc, char *argv[])
{
	int read_fifo = mkfifo(argv[1], 0666);

	if (read_fifo == -1 && errno != EEXIST) {
        perror("read fifo creation error\n");
        exit(1);
    }

	int write_fifo = mkfifo(argv[2], 0666);

    if (write_fifo == -1 && errno != EEXIST) {
        perror("write fifo creation error\n");
        exit(2);
    }

	int fd_read = open(argv[1], O_RDONLY);
	
	if (fd_read == -1) {
		perror("Error opening reading pipe\n");
		exit(3);
	}

	int fd_write = open(argv[2], O_WRONLLY | O_NONBLOCK);
	
	if (fd_write == -1) {
		perror("Error opening writing pipe");
		exit(4);
	}

	int max_fd = (fd_read > fd_write) ? fd_read : fd_write;

	fd_set readfds, writefds;

	FD_ZERO(&readfds);
	FD_ZERO(&writefds);

	FD_SET(fd_read, &readfds);
	FD_SET(fd_write, &writefds);

	while(1) {

		fd_set readfds_cp = readfds;
		fd_set writefds_cp = writefds;

		int ready = select(max_fd + 1, &readfds_cp, &writefds_cp, NULL, NULL);

		
	}
	
	close(fd_read);
	close(fd_write);
	return 0;
}
