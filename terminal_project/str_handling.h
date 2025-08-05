#ifndef STR_HANDLING_H
#define STR_HANDLING_H

#define DICT_LEN 1024
#define COMMAND_LEN 20

unsigned int compare_and_suggest(char buffer[COMMAND_LEN], char dict[DICT_LEN][COMMAND_LEN]);

#endif
