#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "str_handling.h"

struct Found_Str {
	char *string;
	struct Found_Str *prev;
	int len;
};

struct Found_Str *initialize(char *buffer) 
{
	struct Found_Str *data = malloc(sizeof(struct Found_Str));
	if (buffer == NULL) {
		perror("Empty string passed\n");
		exit(1);
	}
	data->string = buffer;
	data->prev = NULL;
	data->len = 0;
	return data;
}

struct Found_Str *add_element(char *buffer, struct Found_Str *cur)
{
	if (!cur) {
		struct Found_Str *new_curr = initialize(buffer); 
		return new_curr;
	}
	struct Found_Str *tmp = initialize(buffer);
	tmp->prev = cur;
	tmp->len = cur->len += 1;
	return cur = tmp;
}

void empty_list(struct Found_Str *cur)
{
	while (cur->prev) {
		struct Found_Str *tmp = cur;
		cur = cur->prev;
		free(tmp);
	}
	free(cur);
}

void print_list(struct Found_Str *cur)
{
	while (cur->prev) {
		printf("\n%s", cur->string);
		cur = cur->prev;
	}
	printf("\n%s", cur->string);
}

void compare_and_suggest(char buffer[COMMAND_LEN], char dict[DICT_LEN][COMMAND_LEN])
{
	struct Found_Str *data = NULL;
	
	for (int i = 0; i < DICT_LEN; i++) {
		if (strncmp(buffer, dict[i], strlen(buffer)) == 0) {
			data = add_element(dict[i], data);
			
			/* Debugging print here to verify len value*/
			// printf("\n%d", data->len);

		}
	}

	/* If only one match is found, fill the buffer with leftover symbols and push them to stdout */
	
	if (data->len == 0) {
		char *temp_str = data->string;
		temp_str += strlen(buffer);
		printf("%s", temp_str);
		strcat(buffer, temp_str);
	}

	if (data->len > 0) {
		print_list(data);
		printf("\n> %s", buffer);
		fflush(stdout);
	}

	// Emptying dynamically allocated list
	empty_list(data);
}

