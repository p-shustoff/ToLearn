#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(int argc, char *argv[])
{
	if (argc != 4) {
		perror("Incorrect number of arguments\n");
		exit(1);
	}
	int sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd == -1) {
		perror("Error creating socket\n");
		exit(2);
	}
	struct sockaddr_in server;
	socklen_t addr_len = sizeof(server);
	

	int port = atoi(argv[2]);

	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	int ok = inet_aton(argv[1], &(server.sin_addr));
	
	if (!ok) {
		perror("Invalid IP\n");
		exit(3);	
	}
	

	int res = sendto(sd, argv[3], strlen(argv[3]), 0, (struct sockaddr *)&server, addr_len);

	if (res < 0) {
        perror("Ошибка отправки сообщения");
        exit(4);
    }
	return 0;
}
