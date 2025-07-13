#include <stdio.h>
#include <string.h>
#include "str_handling.h"

struct Found_Str {
	char *string;
	struct Found_Str *next;
	int pos;
};

struct Found_Str *initialize(char *buffer) 
{
	struct Found_Str *data = malloc(sizeof(struct Found_Str));
	if (buffer == NULL) {
		perror("Empty string passed\n");
		exit(1);
	}
	data->string = buffer;
	data->next = NULL;
	data->pos = 0;
	return data;
}

struct Found_Str *add_element(char *buffer, struct Found_Str *stored_data)
{
	if (stored_data == NULL) {
		stored_data = initialize(buffer);
		return stored_data;
	}
	else {
		struct Found_Str *tmp = add_element(buffer, stored_data->next);
		next->pos = stored_data->pos =+ 1;
		stored_data->next = tmp;
		free(tmp);
		return stored_data;
	}
}

void compare_and_suggest(char buffer[COMMAND_LEN], char dict[DICT_LEN][COMMAND_LEN])
{
	int counter = 0;
	for (int i = 0; i < DICT_LEN; i++) {
		if (strncmp(buffer, dict[i], strlen(buffer)) == 0) {
			counter++;
			printf("%s\n", dict[i]);
		}	
	}
	if (counter) {;
		printf("%s", buffer);
	}
}
