#include <stdio.h>
#include <string.h>
#include "str_handling.h"

void compare_and_suggest(char buffer[COMMAND_LEN], char dict[DICT_LEN][COMMAND_LEN])
{
	int counter = 0;
	for (int i = 0; i < DICT_LEN; i++) {
		if ( !strncmp(buffer, dict[i], strlen(buffer))) {
			counter++;
			putchar('\n');
			printf("%s\n", dict[i]);
		}
	}
	if (counter) {
		putchar('>');
		printf("%s", buffer);
	}
}
