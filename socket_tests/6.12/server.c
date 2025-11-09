#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

typedef struct client_node {
	int socket;
	struct sockaddr_in address;
	struct client_node *next;
	char buffer[1024];
	size_t buf_len;
} client_node_t;

client_node_t *clients_head = NULL;

void add_client(int socket, struct sockaddr_in address)
{
	client_node_t *new_client = malloc(sizeof(client_node_t));
	new_client->socket = socket;
	new_client->address = address;
	new_client->next = clients_head;
	memset(new_client->buffer, 0, sizeof(new_client->buffer));
	new_client->buf_len = 0;
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
		count++;
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

	struct sockaddr_in server;

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

	const char *greeting_message = "\n>> Ok\n";

	while(1) {
	
		fd_set readfds;

		// Assume max descriptor is server descriptor

		int max_d = ls;
			
		// Setting sets to zero

		FD_ZERO(&readfds);
		FD_SET(ls, &readfds);

		client_node_t *current = clients_head;

		// Adding all clients fd to check readiness to write
		while (current != NULL) {
			FD_SET(current->socket, &readfds);
			if (current->socket > max_d) {
				max_d = current->socket;
			}
			current = current->next;
		}
		
		struct timeval timeout;
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;

		int res = select(max_d + 1, &readfds, NULL, NULL, &timeout);
		
		if (res == -1) {
			if (errno == EINTR) {
				printf("Signal arrived\n");
			} else {
				perror("Select error\n");
			}
			continue;
		}

		if (res == 0) {
			printf("Timeout disconnect\n");
			continue;
		}

		if (FD_ISSET(ls, &readfds)) {

			struct sockaddr_in client;
			socklen_t addr_len = sizeof(client);

			int new_socket = accept(ls, (struct sockaddr*)&client, &addr_len);

			if (new_socket == -1) {
				perror("Error acepting socket\n");
				continue;
			} else {
				add_client(new_socket, client);
				char client_ip[INET_ADDRSTRLEN];
				uint16_t client_port = ntohs(client.sin_port);
				inet_ntop(AF_INET, &client.sin_addr, client_ip, INET_ADDRSTRLEN);
				printf("Accepted! IP: %s PORT: %d\n", client_ip, client_port);
			}
		}

		current = clients_head;

		while (current != NULL) {
			int sd = current->socket;
			client_node_t *next = current->next;

			if (FD_ISSET(sd, &readfds)) {
				char temp_buf[256];
				ssize_t read_bytes = read(sd, temp_buf, sizeof(temp_buf) - 1);

				if (read_bytes == 0) {
					printf("Client with socket %d has disconnected\n", sd);
					remove_client(sd);
				} else if (read_bytes > 0) {
					memcpy(current->buffer + current->buf_len, temp_buf, read_bytes);
					current->buf_len += read_bytes;
					current->buffer[current->buf_len] = '\0';

					char *newline;
        			while ((newline = strchr(current->buffer, '\n')) != NULL) {
            			*newline = '\0';
            			printf("Received FULL message: %s from client %d\n", current->buffer, sd);

			            if (write(sd, greeting_message, strlen(greeting_message)) < 0) {
			                perror("Error writing back to socket\n");
				                remove_client(sd);
			                break;
						}
					    size_t remaining = current->buf_len - (newline - current->buffer) - 1;
					    memmove(current->buffer, newline + 1, remaining);
					    current->buf_len = remaining;
					    current->buffer[current->buf_len] = '\0';
					}
				} else if (read_bytes < 0) {
					perror("Error reading from client\n");
					remove_client(sd);
				}
			}
			current = next;
		}
	}
	close(ls);
	return 0;
}

