#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

#include "dict_handling.h"

#define ALPHABET_SIZE 26

struct Trie_Node {
	struct Trie_Node *children[ALPHABET_SIZE]
	bool isEndOfWord;
};

struct Trie_Node *get_Node() 
{
	struct Trie_Node *pNode = malloc(sizeof(struct Trie_Node));
	pNode->isEndOfWord = false;

	for (int i = 0; i < ALPHABET_SIZE; i++) {
		pNode->children[i] = NULL;
	}

	return pNode;
}

void insert(struct TrieNode *root, const char *key)
{
	struct TrieNode *pCrawl = root;

	for (int i = 0; i < strlen(key); i++)
	{
		int index = key[i] - 'a';
		if (!pCrawl->children[index])
			pCrawl->children[index] = getNode();

		pCrawl = pCrawl->children[index];
	}

	pCrawl->isEndOfWord = true;
}

bool search(struct TrieNode *root, const char *key)
{
	struct TrieNode *pCrawl = root;

	for (int i = 0; i < strlen(key); i++)
	{
		int index = key[i] - 'a';
		if (!pCrawl->children[index])
			return false;

		pCrawl = pCrawl->children[index];
	}

	return (pCrawl->isEndOfWord);
}



void read_string_from_file_to_dict(int fd, char buffer[DICT_LEN][COMMAND_LEN]) {
    
	ssize_t bytes_read;
    int dict_ind = 0;
    int command_ind = 0;

    while (dict_ind < DICT_LEN && 
           (bytes_read = read(fd, &buffer[dict_ind][command_ind], 1)) > 0) {
        if (bytes_read == -1) {
            perror("Error reading file");
            exit(3);
        }

        if (buffer[dict_ind][command_ind] == '\n') {
            buffer[dict_ind][command_ind] = '\0';  // Replace '\n' to '\0'
            dict_ind++;
            command_ind = 0;  // Reset for the new sring
        } else {
            command_ind++;
            if (command_ind >= COMMAND_LEN - 1) {  //  Overflow handling
                buffer[dict_ind][COMMAND_LEN - 1] = '\0'; 
                dict_ind++;
                command_ind = 0;
            }
        }
    }

    if (command_ind > 0 && dict_ind < DICT_LEN) {
        buffer[dict_ind][command_ind] = '\0';
    }
}

void print_strings_from_buffer(char buffer[DICT_LEN][COMMAND_LEN])
{
	char (*tmp)[COMMAND_LEN] = buffer;
	for (int j = 0; j < DICT_LEN; j++, tmp++) {
		if((*tmp)[0] != '\0') {
			printf("%s\n", *tmp);
		}
	}
}
