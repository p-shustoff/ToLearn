#include <termios.h>
#include <unistd.h>
#include <string.h>

#include "str_handling.h"

void start_terminal()
{
	struct termios ts_old, ts_new;
	
	tcgetattr(0, &ts_old);
	memcpy(&ts_new, &ts_old, sizeof(ts_old));
	ts_new.c_lflag &= ~ (ICANON | ECHO);
	tcsetattr(0, TCSANOW, &ts_new);

	printf(">");
	while (
	tcsetattr(0, TCSANOW, &ts_old);
}
