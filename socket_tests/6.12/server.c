#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct client_node {
	int socket;
	struct sockaddr_in address;
	struct client_node *next;
} client_node_t;

client_node_t *clients_head = NULL;

void add_client(int socket, struct sockaddr_in address)
{
	client_node_t *new_client = malloc(sizeof(client_node_t));
	new_client->socket = socket;
	new_client->address = address;
	new_clent->next = clients_head;
	clients_head = new_client;
}

void remove_client(int socket)
{
	client_node_t *prev = NULL;
	client_node_t *current = clients_head;

	while(current != NULL) {
		if (current->socket == socket) {
			if (prev == NULL) {
				clients_head = current->next;
			} else {
				prev->next = current->next;
			}
			shutdown(current->socket, SHUT_RDWR);
			close(current->socket);
			free(current);
			return;
		}
		prev = current;
		current = current->next;
	}
	printf("Client with socket %d was not found\n", socket);
}

void free_all_clients()
{
	client_node_t *current = clients_head;
	while (current != NULL) {
		client_node_t *next = current->next;
		close(current->socket);
		free(current);
		current = next;
	}
	clients_head = NULL;
}

int get_client_count()
{
	int count = 0;
	client_node_t *current = clients_head;
	while (current != NULL) {
		count++:
		current = current->next;
	}
	return count;
}

int main(int argc, char *argv[])
{
	// TODO

	if (argc != 2) {
		printf("Example: %s <server_port>\n", argv[0]);
		exit(1);
	}

	int ls = socket(AF_INET, SOCK_STREAM, 0);

	if (ls == -1) {
    	perror("Error creating listening socket\n");
        exit(2);
    }

	struct sockaddr_in server, client;
    socklen_t addr_len = sizeof(client);

	int port = atoi(argv[1]);

	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	int res = bind(ls, (struct sockaddr*)&server, sizeof(server));
	if (res == -1) {
		perror("Error when binding IP to socket\n");
		exit(3);
	}

	int sd_list = listen(ls, 128);
	if (sd_list != 0) {
		perror("Error listenting\n");
		exit(4);
	}

	const char *message = "Ok";

	while(1) {
	
		int fd, res;
		fd_set readfds, writefds;
		int max_d = ls;

		FD_ZERO(&readfds);
		FD_ZERO(&writefds);
		FD_SET(ls, &readfds);

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

