#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>

int main() 
{
	fd_set readfds;
	struct timeval timeout = {15, 0};
	char buffer[256] = {0};

	FD_ZERO(&readfds);
	FD_SET(0, &readfds);

	printf("What is your name, please?\n");
	
	int result = select(1, &readfds, NULL, NULL, &timeout);

	if (result == -1) {
		perror("Select error\n");
		exit(1);
	} else if (result == 0) {
		printf("Sorry i'm terribly busy\n");
		exit(2);
	} else {
		if (FD_ISSET(0, &readfds)) {
			scanf("%s", buffer);
			printf("Nice to meet you, dear %s!\n", buffer);
		}
	}
	return 0;
}
