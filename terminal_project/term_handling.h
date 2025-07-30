#ifndef TERM_HANDLING_H
#define TERM_HANDLING_H

#define DICT_LEN 1024
#define COMMAND_LEN 20

void start_terminal(char dict[DICT_LEN][COMMAND_LEN], int fd_dest);

#endif

