/* COPYRIGHT RUSU BOGDAN, 312CA, 2022-2023 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helper_functions.h"
#define CMD_LEN 40

enum command {
	INSERT,
	LOAD,
	REMOVE,
	AUTOCORRECT,
	AUTOCOMPLETE,
	DEALLOC,
	UNKNOWN
};

enum command get_command(const char *cmd)
{
	if (strcmp(cmd, "INSERT") == 0)
		return INSERT;
	else if (strcmp(cmd, "LOAD") == 0)
		return LOAD;
	else if (strcmp(cmd, "REMOVE") == 0)
		return REMOVE;
	else if (strcmp(cmd, "AUTOCORRECT") == 0)
		return AUTOCORRECT;
	else if (strcmp(cmd, "AUTOCOMPLETE") == 0)
		return AUTOCOMPLETE;
	else if (strcmp(cmd, "EXIT") == 0)
		return DEALLOC;
	else
		return UNKNOWN;
}

int main(void)
{
	char cmd[CMD_LEN];

	trie_t *trie = trie_create(sizeof(int), ALPHABET_SIZE, ALPHABET, free);
	DIE(!trie, "err alloc trie\n");

	while (1) {
		scanf("%s", cmd);

		enum command comm = get_command(cmd);

		switch (comm) {
		case INSERT:
			insert_helper(trie);
			break;

		case LOAD:
			load_helper(trie);
			break;

		case REMOVE:
			remove_helper(trie);
			break;

		case AUTOCORRECT:
			autocorrect_helper(trie);
			break;

		case AUTOCOMPLETE:
			autocomplete_helper(trie);
			break;

		case DEALLOC:
			exit_helper(&trie);
			return 0;

		default:
			printf("Unrecognized command. Try again!\n");
			break;
		}
	}

	return 0;
}
