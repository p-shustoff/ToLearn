#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "term_handling.h"
#include "str_handling.h"

#define BUFFER_SIZE 20

void start_terminal(char dict[DICT_LEN][COMMAND_LEN], int fd_dest) {
    struct termios old_termios, new_termios;
    char buffer[BUFFER_SIZE] = {0};
    int i = 0;
    bool should_print_prompt = true;  // Controls when to print "> "

    // Save old terminal settings
    tcgetattr(STDIN_FILENO, &old_termios);
    new_termios = old_termios;

    // Configure new terminal settings
    new_termios.c_lflag &= ~(ICANON | ECHO);
    new_termios.c_cc[VMIN] = 1;
    new_termios.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    while (1) {
        if (should_print_prompt) {
            printf("> ");
            if (strlen(buffer) > 0) {
                printf("%s", buffer);
            }
            fflush(stdout);
            should_print_prompt = false;  // Reset until next Enter/Tab
        }

        char c = getchar();

        switch (c) {
            case '\n':  // Enter key
                if (i < BUFFER_SIZE - 1) {
                    buffer[i] = '\n';
                    putchar('\n');
                    
                    ssize_t bytes_written = write(fd_dest, buffer, sizeof(buffer));
                    if (bytes_written == -1) {
                        perror("Error writing to destination file");
                        exit(4);
                    }
                    
                    memset(buffer, 0, sizeof(buffer));
                    i = 0;
                }
                should_print_prompt = true;  // Print prompt again after Enter
                break;
                
            case '\t':  // Tab key
                buffer[i] = '\0';
				unsigned int res = 0;
                if (strlen(buffer) >= 1) {
                    res = compare_and_suggest(buffer, dict); 
                } else {
                    printf("Buffer is empty\n");
                }
				if (res == 1) {
                	should_print_prompt = false;  // Print prompt again after Tab
				} else {
					if (res == 0) {
						putchar('\n');
					}
					should_print_prompt = true;
				}
				i = strlen(buffer);
                break;
                
            case ' ':
				putchar('\n');
				for (int k = 0; k < BUFFER_SIZE; k++) {
					printf("%c\n", buffer[k]);
				}   // Backspace (Linux/Unix)
            case '\b':  // Backspace (some terminals)
                if (i > 0) {
                    i--;
                    buffer[i] = '\0';
                    // Move cursor back, erase character, move cursor back again
                    printf("\b \b");
                    fflush(stdout);
                }
                break;
                
            default:
                if (isalpha(c) && i < BUFFER_SIZE - 1) {
                    buffer[i++] = c;
                    putchar(c);
                    fflush(stdout);
                } else if (i >= BUFFER_SIZE - 1) {
                    printf("\n[!] Input limit reached (%d chars)\n", BUFFER_SIZE - 1);
                    memset(buffer, 0, sizeof(buffer));
                    i = 0;
                    should_print_prompt = true;  // Print prompt after overflow
                }
                break;
        }
    }

    // Restore original terminal settings (unreachable in this example)
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
}
