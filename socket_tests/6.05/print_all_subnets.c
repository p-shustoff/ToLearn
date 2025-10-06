/* 
	This programm takes a decimal value of IP address as an argument 
	and prints all subnets, which cover this IP address
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef union {
	uint32_t raw;
	uint8_t octets[4];
	struct {
		uint8_t a, b, c ,d;
	};
} ip_address_union_t;

void read_input_to_union(char *input, ip_address_union_t *ip)
{
	char buffer[4] = {0};

	int buffer_index = 0;
	int octet_index = 0;

	for (int i = 0; i <= strlen(input); i++) {
		if (input[i] == '.' || input[i] == '\0') {
			buffer[buffer_index] = '\0';
			ip->octets[octet_index] = atoi(buffer);
			octet_index++;
			memset(buffer, 0, sizeof(buffer));
			buffer_index = 0;
		} else {
			buffer[buffer_index] = input[i];
			buffer_index++;
		}
	}
}

void print_ip(uint32_t ip_raw) {
    printf("%u.%u.%u.%u",
        (ip_raw >> 24) & 0xFF,
        (ip_raw >> 16) & 0xFF,
        (ip_raw >> 8) & 0xFF,
        ip_raw & 0xFF);
}

void print_subnets(const ip_address_union_t *ip) {
    uint32_t ip_raw =
        (ip->octets[0] << 24) |
        (ip->octets[1] << 16) |
        (ip->octets[2] << 8) |
        ip->octets[3];

    for (int prefix = 32; prefix >= 0; prefix--) {
        uint32_t mask = (prefix == 0) ? 0 : 0xFFFFFFFF << (32 - prefix);
        uint32_t network = ip_raw & mask;
        print_ip(network);
        printf("/%d\n", prefix);
    }
}

int main (int argc, char *argv[])
{
	// 1. Simple input checking

	if (argc != 2) {
		perror("Unexpected number of arguments");
		exit(1);
	}

	// 2. Initialize union and fill it up with 0

	ip_address_union_t ip;
	ip.raw = 0;

	// 3. Read input decimal to struct
	read_input_to_union(argv[1], &ip);
	// print to check (if needed)
	// print_ip(&ip);

	// 4. Print all subnets 
	print_subnets(&ip);
	return 0;
}
