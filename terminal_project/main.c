#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define COMMAND_LEN 20
#define DICT_LEN 1024

void read_string_from_file_to_dict(int fd, char buffer[DICT_LEN][COMMAND_LEN]) {
    
	ssize_t bytes_read;
    int dict_ind = 0;
    int command_ind = 0;

    while (dict_ind < DICT_LEN && 
           (bytes_read = read(fd, &buffer[dict_ind][command_ind], 1)) > 0) {
        if (bytes_read == -1) {
            perror("Error reading file");
            exit(3);
        }

        if (buffer[dict_ind][command_ind] == '\n') {
            buffer[dict_ind][command_ind] = '\0';  // Replace '\n' to '\0'
            dict_ind++;
            command_ind = 0;  // Reset for the new sring
        } else {
            command_ind++;
            if (command_ind >= COMMAND_LEN - 1) {  //  Overflow handling
                buffer[dict_ind][COMMAND_LEN - 1] = '\0'; 
                dict_ind++;
                command_ind = 0;
            }
        }
    }

    if (command_ind > 0 && dict_ind < DICT_LEN) {
        buffer[dict_ind][command_ind] = '\0';
    }
}

void print_strings_from_buffer(char buffer[DICT_LEN][COMMAND_LEN])
{
	char (*tmp)[COMMAND_LEN] = buffer;
	for (int j = 0; j < DICT_LEN; j++, tmp++) {
		if((*tmp)[0] != '\0') {
			printf("%s\n", *tmp);
		}
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
	read_string_from_file_to_dict(fd, buffer);
	close(fd);
	print_strings_from_buffer(buffer);
    return 0;
}
