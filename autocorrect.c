/*COPYRIGHT RUSU BOGDAN, 312CA, 2022-2023*/
#include "autocorrect.h"

void dfs_to_autocorrect(trie_t *trie, trie_node_t **node,
						char *word,
						int k, char *match, int pos, int *found)
{
	if (k < 0 || !(*node))
		return;

	if ((*node)->end_of_word && (*node) != trie->root &&
		strlen(match) == strlen(word)) {
		*found = 1;
		printf("%s\n", match);
		return;
	}

	if (strlen(match) == strlen(word))
		return;

	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if ((*node)->children[i]) {
			trie_node_t *next = (*node)->children[i];
			match[pos] = i + 'a';
			match[pos + 1] = 0;
			if (word[pos] == i + 'a') {
				dfs_to_autocorrect(trie, &next, word,
								   k, match, pos + 1, found);
			} else {
				dfs_to_autocorrect(trie, &next, word,
								   k - 1, match, pos + 1, found);
			}
		}
	}
}
