/*COPYRIGHT RUSU BOGDAN, 312CA, 2022-2023*/
#ifndef HELPER_FUNCTIONS_H_
#define HELPER_FUNCTIONS_H_

#include "trie.h"
#include "autocorrect.h"
#include "autocomplete.h"

/*
	helper function that inserts the node into the afore created
    trie and increments its frequency in the structure using the
    value field of the trie node
*/
void insert_helper(trie_t *trie);

/*
	helper function that reads a file and inserts every word found inside
    into the trie
*/

void load_helper(trie_t *trie);

/*
	helper function that removes the given word from the trie
    and sets its frequency to 0, technically removing it from the trie
    regardless of its frequency
*/

void remove_helper(trie_t *trie);

/*
	helper function that makes use of the nature of the trie in order
    to autocorrect a given word, by difference of at most k characters
*/

void autocorrect_helper(trie_t *trie);

/*
	helper function that makes use of the nature of the trie in order
    to autocomplete a given word, based on the criterion given by the user
*/

void autocomplete_helper(trie_t *trie);

/*
	function that deallocates the memory used by the kd_tree and its nodes
    and prepares the program to be exited gracefully
*/

void exit_helper(trie_t **trie);

#endif  // HELPER_FUNCTIONS_H_
