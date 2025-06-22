#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

#include "str_handling.h"

#define BUFFSIZE 20

void start_terminal()
{
	struct termios ts_old, ts_new;
	
	tcgetattr(0, &ts_old);
	memcpy(&ts_new, &ts_old, sizeof(ts_old));
	ts_new.c_lflag &= ~ (ICANON | ECHO);
	tcsetattr(0, TCSANOW, &ts_new);

	printf(">");
	char buffer[BUFFSIZE] = {0};

	for (int i = 0; i < BUFFSIZE - 1; i++) {
		
		ssize_t bytes_read = read(0, &buffer[i], 1);
		
		if (bytes_read == -1) {
			perror("Error of reading);
			exit(1);
		}
		
		if (('a' <= buffer[i] && buffer[i] <= 'z') || ('A' <= buffer[i] && buffer[i] <= 'Z')) {
			putchar(buffer[i]);
		} 
		else {
			if (buffer[i] == '\n') {
				
			}
		}	
	}

	tcsetattr(0, TCSANOW, &ts_old);
}
