#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{

	if (argc != 2) {
		perror("Invalid number of arguments\n");
		exit(1);
	}
	int sd = socket(AF_INET, SOCK_DGRAM, 0);

	if (sd == -1) {
    	perror("Error creating socket\n");
        exit(2);
    }

	struct sockaddr_in server, client;
    socklen_t addr_len = sizeof(client);

	int port = atoi(argv[1]);

	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	int res = bind(sd, (struct sockaddr*)&server, sizeof(server));
	if (res == -1) {
		perror("Error when binding IP to socket\n");
		exit(3);
	}
	
	char buffer[512];
	memset(buffer, 0, sizeof(buffer));

	int bytes_received = recvfrom(sd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&client, &addr_len);

	if (bytes_received < 0) {
		printf("Error receiving data\n");
		exit(4);	
	}
	
	buffer[bytes_received] = '\0';

	char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client.sin_addr, client_ip, INET_ADDRSTRLEN);


	printf("Получено от %s:%d - %s\n", client_ip, ntohs(client.sin_port), buffer);

	return 0;
}

