/*COPYRIGHT RUSU BOGDAN, 312CA, 2022-2023*/
#include "trie.h"

trie_node_t *trie_create_node(trie_t *trie)
{
	trie_node_t *node = malloc(sizeof(trie_node_t));
	DIE(!node, "err alloc node\n");
	node->end_of_word = 0;
	node->n_children = 0;
	node->value = NULL;
	node->children = malloc(trie->alphabet_size * sizeof(trie_node_t *));
	DIE(!node->children, "err alloc node children\n");
	for (int i = 0; i < trie->alphabet_size; i++)
		node->children[i] = NULL;

	return node;
}

trie_t *trie_create(int data_size, int alphabet_size,
					char *alphabet,
					void (*free_value_cb)(void *))
{
	trie_t *trie = malloc(sizeof(trie_t));
	DIE(!trie, "err alloc trie\n");
	trie->free_value_cb = free_value_cb;
	trie->alphabet_size = alphabet_size;
	trie->alphabet = malloc(alphabet_size + 1);
	DIE(!trie->alphabet, "err alloc alphabet\n");
	strcpy(trie->alphabet, alphabet);
	trie->n_nodes = 1;
	trie->root = trie_create_node(trie);
	DIE(!trie->root, "err alloc root\n");
	trie->root->value = malloc(sizeof(int));
	DIE(!trie->root->value, "err alloc root->val\n");
	int x = -1;
	memcpy(trie->root->value, &x, sizeof(int));
	trie->root->end_of_word = 1;
	trie->size = 0;
	trie->data_size = data_size;

	return trie;
}

void node_insert(trie_t *trie, trie_node_t **node,
				 char *key, char *value)
{
	if (strlen(key) == 0) {
		if (!(*node)->value) {
			(*node)->value = malloc(trie->data_size);
			DIE(!(*node)->value, "err value alloc\n");
			memcpy((*node)->value, value, trie->data_size);
		} else {
			int val = *(int *)(*node)->value;
			val++;
			memcpy((*node)->value, &val, trie->data_size);
		}
		(*node)->end_of_word = 1;
		return;
	}

	trie_node_t *next = (*node)->children[key[0] - 'a'];
	if (!next) {
		next = trie_create_node(trie);
		(*node)->n_children++;
		(*node)->children[key[0] - 'a'] = next;
		trie->n_nodes++;
	}

	node_insert(trie, &next, key + 1, value);
}

void trie_insert(trie_t *trie, char *key, void *value)
{
	node_insert(trie, &trie->root, key, value);
}

void *trie_search(trie_t *trie, char *key)
{
	if (key[0] == 0)
		return trie->root->value;

	trie_node_t *root = trie->root;

	int ok = 1;
	int len = strlen(key);

	for (int i = 0; i < len && ok == 1; i++) {
		if (root->children[key[0] - 'a'] == NULL)
			ok = 0;
		else
			root = root->children[key[0] - 'a'];
		key++;
	}

	if (ok == 0)
		return NULL;
	return root->value;
}

int remove_node(trie_t *trie, trie_node_t **node, char *key)
{
	if (strlen(key) == 0) {
		free((*node)->value);
		(*node)->value = NULL;
		if ((*node)->end_of_word == 1) {
			(*node)->end_of_word = 0;
			if ((*node)->n_children == 0) {
				free((*node)->children);
				free((*node));
				return 1;
			}
			return 0;
		}
		return 0;
	}

	trie_node_t *next = (*node)->children[key[0] - 'a'];

	if (next && remove_node(trie, &(*node)->children[key[0] - 'a'], key + 1)) {
		(*node)->n_children--;
		trie->n_nodes--;
		(*node)->children[key[0] - 'a'] = NULL;

		if ((*node)->n_children == 0 && (*node)->end_of_word == 0) {
			free((*node)->children);
			free(*node);
			return 1;
		}

		return 0;
	}

	return 0;
}

void trie_remove(trie_t *trie, char *key)
{
	remove_node(trie, &trie->root, key);
}

void free_all_nodes(trie_t *trie, trie_node_t **node)
{
	if ((*node) == NULL)
		return;

	for (int i = 0; i < trie->alphabet_size; i++) {
		if ((*node)->children[i]) {
			free_all_nodes(trie, &(*node)->children[i]);
			(*node)->children[i] = NULL;
		}
	}

	if ((*node)->end_of_word == 1) {
		(*node)->end_of_word = 0;
		free((*node)->value);
		(*node)->value = NULL;
	}

	free((*node)->children);
	free((*node));
	*node = NULL;
}

void trie_free(trie_t **ptrie)
{
	if (!ptrie || !(*ptrie))
		return;

	trie_t *trie = *ptrie;
	trie_node_t *root = trie->root;

	free_all_nodes(trie, &root);

	free(trie->alphabet);
	free(trie);
	*ptrie = NULL;
}
