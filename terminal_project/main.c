#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define COMMAND_LEN 20
#define DICT_LEN 1024

int cur_line_is_mt(char buffer[DICT_LEN][COMMAND_LEN])
{
	for (int i = 0; i < DICT_LEN; i++) {
		if (buffer[i][0] == '\0') {
			return i;
		}
	}
	return -1;
}

void read_string_from_dict(int fd, char buffer[DICT_LEN][COMMAND_LEN])
{
	size_t bytes_read;
	while ((bytes_read = read(fd, buffer, 1)) != EOF) {
		if (bytes_read == -1) {
			perror("Error reading file\n");
			exit(3);
		}
}

int main(int argc, char const *argv[])
{
	if (argc != 3) {
		printf("Unexpected amount of argumnets. Example: './prog dict.txt output.txt'\n");
		exit(1);
	}

	int fd = open("dict.txt", O_RDONLY);

	if (fd == -1) {
		perror("Error opening file");
		exit(2);
	}
	char buffer[DICT_LEN][COMMAND_LEN] = {0};
	close(fd);
    return 0;
}
