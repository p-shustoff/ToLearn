#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define TIMEOUT_SEC 5

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

	struct timeval timeout;
    timeout.tv_sec = TIMEOUT_SEC;
    timeout.tv_usec = 0;
    setsockopt(sd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

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

	char buffer[256] = {0};

	int bytes_received = recvfrom(sd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&server, &addr_len);

    if (bytes_received < 0) {
        if (errno == EWOULDBLOCK || errno == EAGAIN) {
            printf("Timeout: No response received\n");
        } else {
            perror("recvfrom failed");
        }
    } else {
        buffer[bytes_received] = '\0';
        printf("Received echo: %s\n", buffer);
    }

	close(sd);

	return 0;
}
