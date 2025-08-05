#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "term_handling.h"
#include "str_handling.h"

#define BUFFER_SIZE 20

void start_terminal(char dict[DICT_LEN][COMMAND_LEN], int fd_dest) {
    struct termios old_termios, new_termios;
    char buffer[BUFFER_SIZE] = {0};
    int i = 0;

    // Save old terminal settings
    tcgetattr(STDIN_FILENO, &old_termios);
    new_termios = old_termios;

    // Configure new terminal settings
    new_termios.c_lflag &= ~(ICANON | ECHO);  // Non-canonical mode, no echo
    new_termios.c_cc[VMIN] = 1;  // Read at least 1 character
    new_termios.c_cc[VTIME] = 0; // No timeout
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    // printf("> ");
    // fflush(stdout);

    while (1) {
		printf("> ");
		if (strlen(buffer) > 0) {
			printf("%s", buffer);
		}
		fflush(stdout);
        char c = getchar();

        if (i < BUFFER_SIZE - 1) {  // Leave space for null terminator
            if (isalpha(c)) {  // More portable than range checks
                buffer[i++] = c;
                putchar(c);
                fflush(stdout);
            }
            else if (c == '\n') {
                buffer[i] = '\n';  // Proper null termination
                
                // Process completed input
                
				/* Debugging print */
				// printf("\nFirst character: %c\n", buffer[0]);
                // printf("Full input: %s\n", buffer);

				putchar('\n');

                ssize_t bytes_written = write(fd_dest, buffer, sizeof(buffer));

				if (bytes_written == -1) {
					perror("Error writing to destination file");
					exit(4);
				}

                // Reset for next input
                memset(buffer, 0, sizeof(buffer));
                i = 0;
                
                // printf("> ");
                // fflush(stdout);
            }
			else if (c == '\t') {
				buffer[i] = '\0';
				if (strlen(buffer) >= 1) {
					compare_and_suggest(buffer, dict);
					i = strlen(buffer) + 1;
				}
				else {
					printf("Buffer is empty\n");
				}
			}
            // Add other character handlers (backspace, tabs, etc.) here
        }
        else {
            // Handle buffer overflow
            printf("\n[!] Input limit reached (%d chars)\n", BUFFER_SIZE - 1);
            memset(buffer, 0, sizeof(buffer));
            i = 0;
            // printf("> ");
    		// fflush(stdout);
        }
    }

    // Restore original terminal settings (unreachable in this example)
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
}
