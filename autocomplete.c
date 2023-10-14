/*COPYRIGHT RUSU BOGDAN, 312CA, 2022-2023*/
#include "autocomplete.h"

void autocomplete_least_lex(trie_t *trie,
							trie_node_t **node,
							char *word,
							char *match,
							int pos,
							int *found)
{
	if (!(*node))
		return;

	if (*found == 1)
		return;

	if ((*node)->end_of_word && (*node) != trie->root &&
		strlen(match) >= strlen(word)) {
		printf("%s\n", match);
		*found = 1;
		return;
	}

	if (strlen(match) < strlen(word)) {
		trie_node_t *next = (*node)->children[word[pos] - 'a'];
		if (next) {
			match[pos] = word[pos];
			match[pos + 1] = 0;
			autocomplete_least_lex(trie, &next, word, match, pos + 1, found);
		}
		return;

	} else {
		int count = 0;
		for (int i = 0; i < ALPHABET_SIZE; i++) {
			trie_node_t *next = (*node)->children[i];
			if (next) {
				count++;
				match[pos] = i + 'a';
				match[pos + 1] = 0;
				autocomplete_least_lex(trie, &next, word, match,
									   pos + 1, found);
			}
		}
		if (!count)
			return;
	}
}

void autocomplete_shortest(trie_t *trie,
						   trie_node_t **node,
						   char *word,
						   char *match,
						   int pos,
						   int *found)
{
	int shortest = 10 * WORD_LEN;
	autocomplete_shortest_getter(trie, node, word, match,
								 pos, found, &shortest);
	match[0] = 0;
	*found = 0;

	autocomplete_shortest_helper(trie, node, word, match,
								 pos, found, shortest);
}

void autocomplete_most_freq(trie_t *trie,
							trie_node_t **node,
							char *word,
							char *match,
							int pos,
							int *found)
{
	int most_freq = -10 * WORD_LEN;
	autocomplete_most_freq_getter(trie, node, word, match,
								  pos, found, &most_freq);

	match[0] = 0;
	*found = 0;

	autocomplete_most_freq_helper(trie, node, word, match,
								  pos, found, most_freq);
}

void autocomplete_shortest_getter(trie_t *trie,
								  trie_node_t **node,
								  char *word,
								  char *match,
								  int pos,
								  int *found,
								  int *shortest)
{
	if (!(*node))
		return;

	if ((*node)->end_of_word && (*node) != trie->root &&
		strlen(match) >= strlen(word)) {
		if ((int)strlen(match) < *shortest)
			*shortest = (int)strlen(match);
		*found = 1;
		return;
	}

	if (strlen(match) < strlen(word)) {
		trie_node_t *next = (*node)->children[word[pos] - 'a'];
		if (next) {
			match[pos] = word[pos];
			match[pos + 1] = 0;
			autocomplete_shortest_getter(trie, &next, word, match,
										 pos + 1, found, shortest);
		}
		return;

	} else {
		int count = 0;
		for (int i = 0; i < ALPHABET_SIZE; i++) {
			trie_node_t *next = (*node)->children[i];
			if (next) {
				count++;
				match[pos] = i + 'a';
				match[pos + 1] = 0;
				autocomplete_shortest_getter(trie, &next, word, match,
											 pos + 1, found, shortest);
			}
		}
		if (!count)
			return;
	}
}

void autocomplete_most_freq_getter(trie_t *trie,
								   trie_node_t **node,
								   char *word,
								   char *match,
								   int pos,
								   int *found,
								   int *most_freq)
{
	if (!(*node))
		return;

	if ((*node)->end_of_word && (*node) != trie->root &&
		strlen(match) >= strlen(word)) {
		if (*(int *)(*node)->value > *most_freq)
			*most_freq = *(int *)(*node)->value;
		*found = 1;
	}

	if (strlen(match) < strlen(word)) {
		trie_node_t *next = (*node)->children[word[pos] - 'a'];
		if (next) {
			match[pos] = word[pos];
			match[pos + 1] = 0;
			autocomplete_most_freq_getter(trie, &next, word, match,
										  pos + 1, found, most_freq);
		}
		return;

	} else {
		int count = 0;
		for (int i = 0; i < ALPHABET_SIZE; i++) {
			trie_node_t *next = (*node)->children[i];
			if (next) {
				count++;
				match[pos] = i + 'a';
				match[pos + 1] = 0;
				autocomplete_most_freq_getter(trie, &next, word, match,
											  pos + 1, found, most_freq);
			}
		}
		if (!count)
			return;
	}
}

void autocomplete_shortest_helper(trie_t *trie,
								  trie_node_t **node,
								  char *word,
								  char *match,
								  int pos,
								  int *found,
								  int shortest)
{
	if (!(*node) || *found)
		return;

	if ((*node)->end_of_word && (*node) != trie->root &&
		strlen(match) >= strlen(word)) {
		if ((int)strlen(match) == shortest) {
			printf("%s\n", match);
			*found = 1;
		}
		return;
	}

	if (strlen(match) < strlen(word)) {
		trie_node_t *next = (*node)->children[word[pos] - 'a'];
		if (next) {
			match[pos] = word[pos];
			match[pos + 1] = 0;
			autocomplete_shortest_helper(trie, &next, word, match,
										 pos + 1, found, shortest);
		}
		return;

	} else {
		int count = 0;
		for (int i = 0; i < ALPHABET_SIZE; i++) {
			trie_node_t *next = (*node)->children[i];
			if (next) {
				count++;
				match[pos] = i + 'a';
				match[pos + 1] = 0;
				autocomplete_shortest_helper(trie, &next, word, match,
											 pos + 1, found, shortest);
			}
		}
		if (!count)
			return;
	}
}

void autocomplete_most_freq_helper(trie_t *trie,
								   trie_node_t **node,
								   char *word,
								   char *match,
								   int pos,
								   int *found,
								   int most_freq)
{
	if (!(*node) || *found)
		return;

	if ((*node)->end_of_word && (*node) != trie->root &&
		strlen(match) >= strlen(word)) {
		if (*(int *)(*node)->value == most_freq) {
			printf("%s\n", match);
			*found = 1;
		}
	}

	if (strlen(match) < strlen(word)) {
		trie_node_t *next = (*node)->children[word[pos] - 'a'];
		if (next) {
			match[pos] = word[pos];
			match[pos + 1] = 0;
			autocomplete_most_freq_helper(trie, &next, word, match,
										  pos + 1, found, most_freq);
		}
		return;

	} else {
		int count = 0;
		for (int i = 0; i < ALPHABET_SIZE; i++) {
			trie_node_t *next = (*node)->children[i];
			if (next) {
				count++;
				match[pos] = i + 'a';
				match[pos + 1] = 0;
				autocomplete_most_freq_helper(trie, &next, word, match,
											  pos + 1, found, most_freq);
			}
		}
		if (!count)
			return;
	}
}
