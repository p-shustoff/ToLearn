#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include "dict_handling.h"
#include "term_handling.h"

int main(int argc, char const *argv[])
{
	// 1. Checking correct input 
	if (argc != 3) {
		printf("Unexpected amount of argumnets. Example: './prog dict.txt output.txt'\n");
		exit(1);
	}
	
	// 2. Opening file and error handling
	int fd = open("dict.txt", O_RDONLY);

	if (fd == -1) {
		perror("Error opening file");
		exit(2);
	}

	// 3.Mapping strings from file to RAM and closing fd 
	char buffer[DICT_LEN][COMMAND_LEN] = {0};
	read_string_from_file_to_dict(fd, buffer);
	close(fd);

	// 4.Starting terminal session
	start_terminal(buffer);

    return 0;
}
