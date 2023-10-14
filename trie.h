/*COPYRIGHT RUSU BOGDAN, 312CA, 2022-2023*/
#ifndef TRIE_H_
#define TRIE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

#define ALPHABET_SIZE 26
#define ALPHABET "abcdefghijklmnopqrstuvwxyz"
#define WORD_LEN 100
#define LINE_LEN 1000

typedef struct trie_node_t trie_node_t;
struct trie_node_t {
	void *value;

	int end_of_word;

	trie_node_t **children;
	int n_children;
};

typedef struct trie_t trie_t;
struct trie_t {
	trie_node_t *root;

	int size;

	int data_size;

	int alphabet_size;

	char *alphabet;

	void (*free_value_cb)(void *data);

	int n_nodes;
};

trie_node_t *trie_create_node(trie_t *trie);

trie_t *trie_create(int data_size, int alphabet_size,
					char *alphabet,
					void (*free_value_cb)(void *));

void node_insert(trie_t *trie, trie_node_t **node,
				 char *key, char *value);

void trie_insert(trie_t *trie, char *key, void *value);

void *trie_search(trie_t *trie, char *key);

int remove_node(trie_t *trie, trie_node_t **node, char *key);

void trie_remove(trie_t *trie, char *key);

void free_all_nodes(trie_t *trie, trie_node_t **node);

void trie_free(trie_t **ptrie);

#endif  // TRIE_H_
