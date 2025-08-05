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
	data->len = 1;
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

unsigned int compare_and_suggest(char buffer[COMMAND_LEN], char dict[DICT_LEN][COMMAND_LEN])
{
	struct Found_Str *data = NULL;
	unsigned int result = 0;
	for (int i = 0; i < DICT_LEN; i++) {
		if (strncmp(buffer, dict[i], strlen(buffer)) == 0) {
			data = add_element(dict[i], data);
			result++;
			/* Debugging print here to verify len value*/
			// printf("\n%d", data->len);
		}
	}

	/* If only one match is found, fill the buffer with leftover symbols and push them to stdout */
	if (result == 0) {
		return 0;
	} else if (result == 1) {
		char *temp_str = data->string;
		temp_str += strlen(buffer);
		if (*temp_str) {
			printf("%s", temp_str);
		} else {
			return 0;
		}
		strcat(buffer, temp_str);
	} else if (result > 1) {
		print_list(data);
		putchar('\n');
		// fflush(stdout);
	}

	// Emptying dynamically allocated list
	empty_list(data);
	return result;
}

