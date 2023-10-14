/*COPYRIGHT RUSU BOGDAN, 312CA, 2022-2023*/
#ifndef AUTOCORRECT_H_
#define AUTOCORRECT_H_

#include "trie.h"

/*
	recursive function that starts from the root of the trie
	and is based on the principles of the depth-first search
	and at each step verifies if the current letter matches the
	current letter from the query word; if it does, k is not
	changed (we have no mismatch) and if it is different, k is
	decremented (we have a mismatch at this step)
	if k reaches 0, it means there is no reason to go further from
	this node
	similarly, if the length of the currently constructed word
	is higher than the length of the query word, we don't delve
	deeper into the recursion from the current node
	elsewise, if k is higher or equal to 0 and the length of the
	constructed word is equal to that of the query word, then it
	means the constructed word is a good match, and is printed out
	as the algorithm is based on the english alphabet, which is
	order lexicographically by default, the matches of autocorrect
	will be printed out lexicographically, thus reducing the need
	to store and sort them
*/

void dfs_to_autocorrect(trie_t *trie, trie_node_t **node,
						char *word,
						int k, char *match, int pos, int *found);
#endif //  AUTOCORRECT_H_
