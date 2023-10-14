/*COPYRIGHT RUSU BOGDAN, 312CA, 2022-2023*/
#ifndef AUTOCOMPLETE_H_
#define AUTOCOMPLETE_H_

#include "trie.h"

/*
	recursive function that starts from the root of the trie
	and is based on the principles of the depth-first search
	and it first goes on the described path by the query prefix
	if the path is not found within the trie, we rewind the recursion
	and a message will be printed, if the found variable is not modified
	after the path is found we find the first word starting from that new
	root and print it and mark that this word has been found as the
	minimum lexicographical match by setting the value at address found
	to 1 and we rewind the recursion back
*/

void autocomplete_least_lex(trie_t *trie,
							trie_node_t **node,
							char *word,
							char *match,
							int pos,
							int *found);

/*
	function that makes use of the shortest_getter function to
	compute the minimum length of a matching word in the trie
	and after that we use the helper function to print the
	first lexicographically shortest matching word
	it is important to note that the same dfs principle is used
	in this case as well, and we will not go further down the trie
	if we find a node representing the end of word, it is impossible
	we get a shortest word by going down further
*/

void autocomplete_shortest(trie_t *trie,
						   trie_node_t **node,
						   char *word,
						   char *match,
						   int pos,
						   int *found);

/*
	function that makes use of the most_freq_getter function to
	compute the maximum frequency of a matching word in the trie
	and after that we use the helper function to print the
	first lexicographically maximum frequency word
	in this case, however, we need to go as deep as possible
	in the trie because there might be the case that the word
	with the most frequency is a very long one (which in real life
	is most likely impossible)
*/

void autocomplete_most_freq(trie_t *trie,
							trie_node_t **node,
							char *word,
							char *match,
							int pos,
							int *found);

void autocomplete_shortest_getter(trie_t *trie,
								  trie_node_t **node,
								  char *word,
								  char *match,
								  int pos,
								  int *found,
								  int *shortest);

void autocomplete_most_freq_getter(trie_t *trie,
								   trie_node_t **node,
								   char *word,
								   char *match,
								   int pos,
								   int *found,
								   int *most_freq);

void autocomplete_shortest_helper(trie_t *trie,
								  trie_node_t **node,
								  char *word,
								  char *match,
								  int pos,
								  int *found,
								  int shortest);

void autocomplete_most_freq_helper(trie_t *trie,
								   trie_node_t **node,
								   char *word,
								   char *match,
								   int pos,
								   int *found,
								   int most_freq);

#endif //  AUTOCOMPLETE_H_
