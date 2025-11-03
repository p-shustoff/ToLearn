#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>


int main(int argc, char *argv[])
{
	

	if (argc != 3) {
		printf("Usage: %s <read_fifo> <write_fifo>\n", argv[0]);
		exit(1);
	}

	int read_fifo = mkfifo(argv[1], 0666);
	if (read_fifo == -1 && errno != EEXIST) {
        perror("read fifo creation error\n");
        exit(2);
    }

	int write_fifo = mkfifo(argv[2], 0666);
    if (write_fifo == -1 && errno != EEXIST) {
        perror("write fifo creation error\n");
        exit(3);
    }

	printf("Opening FIFOs: read=%s, write=%s\n", argv[1], argv[2]);

	int fd_read = open(argv[1], O_RDONLY | O_NONBLOCK);
	if (fd_read == -1) {
		perror("Error opening reading pipe\n");
		exit(4);
	}

	int fd_write = open(argv[2], O_WRONLY);
	if (fd_write == -1) {
		perror("Error opening writing pipe\n");
		exit(4);
	}

	printf("Chat started!\n");

	fd_set readfds;
	int max_fd = (fd_read > STDIN_FILENO) ? fd_read : STDIN_FILENO;
	max_fd = (max_fd > fd_write) ? max_fd : fd_write;

	char buffer[256];

	while(1) {

		FD_ZERO(&readfds);
		FD_SET(fd_read, &readfds);
		FD_SET(STDIN_FILENO, &readfds);

		int ready = select(max_fd + 1, &readfds, NULL, NULL, NULL);

		if (ready == -1) {
			perror("select error\n");
			break;
		}

        if (FD_ISSET(fd_read, &readfds)) {
            ssize_t bytes = read(fd_read, buffer, sizeof(buffer) - 1);
            if (bytes > 0) {
                buffer[bytes] = '\0';
                printf("<<: %s\n", buffer);
            } else if (bytes == 0) {
                printf("Other side disconnected\n");
                break;
            }
        }

        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
                size_t len = strlen(buffer);
                if (len > 0 && buffer[len-1] == '\n') {
                    buffer[len-1] = '\0';
                }

                if (strcmp(buffer, "/quit") == 0) {
                    printf("Exiting chat...\n");
                    break;
                }

                if (write(fd_write, buffer, strlen(buffer)) == -1) {
                    perror("write error");
                    break;
                }
                printf(">>: %s\n", buffer);
            }
        }
	}

	close(fd_read);
	close(fd_write);
	return 0;
}
