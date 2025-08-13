#ifndef DICT_HANDLING_H
#define DICT_HANDLING_H

#include <stdbool.h>

#define DICT_LEN 1024
#define COMMAND_LEN 20

#define ALPHABET_SIZE 26

struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;
};

struct TrieNode *getNode();

bool search(struct TrieNode *root, const char *key);

void read_string_from_file_to_dict(FILE *file, struct TrieNode *root);

void print_strings_from_buffer(struct TrieNode *root);

#endif
