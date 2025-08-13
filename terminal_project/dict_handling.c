#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "dict_handling.h"

struct TrieNode *getNode()
{
	struct TrieNode *pNode = malloc(sizeof(struct TrieNode));
	pNode->isEndOfWord = false;

	for (int i = 0; i < ALPHABET_SIZE; i++) {
		pNode->children[i] = NULL;
	}

	return pNode;
}

static void insert(struct TrieNode *root, const char *key)
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



void read_string_from_file_to_dict(FILE *file, struct TrieNode *root) {
	char buffer[COMMAND_LEN];
	while (fscanf(file, "%20s", buffer) == 1) {
		insert(root, buffer);
	}
}


static void printTrieHelper(struct TrieNode *root, char *buffer, int depth)
{
	if (root->isEndOfWord) {
		buffer[depth] = '\0';
		printf("%s\n", buffer);
	}
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (root->children[i]) {
			buffer[depth] = 'a' + i;
			printTrieHelper(root->children[i], buffer, depth+1);
		}
	}
}

void print_strings_from_buffer(struct TrieNode *root) 
{
	char buffer[256];
	printTrieHelper(root, buffer, 0);
}
