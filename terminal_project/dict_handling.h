#ifndef DICT_HANDLING_H
#define DICT_HANDLING_H

#define DICT_LEN 1024
#define COMMAND_LEN 20

void read_string_from_file_to_dict(int fd, char buffer[DICT_LEN][COMMAND_LEN]);

#endif
