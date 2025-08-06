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
	FILE *file = fdopen(argv[1], "r");

	if (file == NULL) {
		perror("Error opening dict file");
		exit(2);
	}

	// 3.Mapping strings from file to RAM and closing fd 

	read_string_from_file_to_dict(fd_dict, buffer);
	fclose(file);

	// 4. Open destination file and error handling
	int fd_dest = open(argv[2], O_WRONLY | O_APPEND | O_CREAT);
	
	if (fd_dest == -1) {
		perror("Error opening destination file");
		exit(3);
	}

	// 5.Starting terminal session
	start_terminal(buffer, fd_dest);
	
	// 6.Closing open descriptor
	close(fd_dest);

    return 0;
}
