#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
	int sd = socket(AF_INET, SOCK_STREAM, 0);

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

	int sd_list = listen(sd, 128);
	if (sd_list != 0) {
		perror("Error listenting\n");
		exit(4);
	}

	char status[256] = {0};

	while(1) {
	
		memset(status, 0, sizeof(status));

		int accept_fd = accept(sd, (struct sockaddr*)&client, &addr_len);

		if (accept_fd == -1) {
			perror("Error acepting socket\n");
			exit(5);
		}
		
		char client_ip[INET_ADDRSTRLEN];
		uint16_t client_port = ntohs(client.sin_port);
	    inet_ntop(AF_INET, &client.sin_addr, client_ip, INET_ADDRSTRLEN);
		printf("Accepted IP: %s PORT :%d\n", client_ip, client_port);

		snprintf(status, sizeof(status), "IP: %s PORT: %d\n", client_ip, client_port);
		ssize_t bytes_written = write(accept_fd, status, sizeof(status));
		if (bytes_written == -1) {
			perror("Error writing to socket\n");
			exit(6);
		}
		shutdown(accept_fd, 2);
		close(accept_fd);
	}
	close(sd);
	return 0;
}

