/*COPYRIGHT RUSU BOGDAN, 312CA, 2022-2023*/
#include "helper_functions.h"

void insert_helper(trie_t *trie)
{
	char word[WORD_LEN];
	char c;
	scanf("%c", &c); // reading space
	scanf("%s", word);
	int value = 1;

	trie_insert(trie, word, &value);
}

void load_helper(trie_t *trie)
{
	char sep[] = " ,.\n\t";
	char filename[WORD_LEN];
	char c;
	scanf("%c", &c); // reading space
	scanf("%s", filename);
	FILE *fp = fopen(filename, "rt");

	if (!fp) {
		printf("File %s does not exist\n", filename);
		return;
	}

	char word[WORD_LEN];

	while (fgets(word, LINE_LEN, fp)) {
		char *tok = strtok(word, sep);
		while (tok) {
			int value = 1;
			trie_insert(trie, tok, &value);
			tok = strtok(NULL, sep);
		}
	}

	fclose(fp);
}

void remove_helper(trie_t *trie)
{
	char word[WORD_LEN];
	char c;
	scanf("%c", &c); // reading space
	scanf("%s", word);

	trie_remove(trie, word);
}

void autocorrect_helper(trie_t *trie)
{
	char word[WORD_LEN];
	char c;
	scanf("%c", &c); // reading space
	scanf("%s", word);

	int k;
	scanf("%d", &k);

	char match[WORD_LEN];
	match[0] = 0;

	int found = 0;

	dfs_to_autocorrect(trie, &trie->root, word, k, match, 0, &found);

	if (found == 0)
		printf("No words found\n");
}

void autocomplete_helper(trie_t *trie)
{
	char word[WORD_LEN];
	char c;
	scanf("%c", &c); // reading space
	scanf("%s", word);

	int criterion;
	scanf("%d", &criterion);

	char match[WORD_LEN];
	match[0] = 0;
	int found = 0;

	switch (criterion) {
	case 0:
		autocomplete_least_lex(trie, &trie->root, word, match, 0, &found);
		if (found == 0)
			printf("No words found\n");
		found = 0;
		match[0] = 0;
		autocomplete_shortest(trie, &trie->root, word, match, 0, &found);
		if (found == 0)
			printf("No words found\n");
		found = 0;
		match[0] = 0;
		autocomplete_most_freq(trie, &trie->root, word, match, 0, &found);
		if (found == 0)
			printf("No words found\n");
		break;
	case 1:
		autocomplete_least_lex(trie, &trie->root, word, match, 0, &found);
		if (found == 0)
			printf("No words found\n");
		break;
	case 2:
		autocomplete_shortest(trie, &trie->root, word, match, 0, &found);
		if (found == 0)
			printf("No words found\n");
		break;
	case 3:
		autocomplete_most_freq(trie, &trie->root, word, match, 0, &found);
		if (found == 0)
			printf("No words found\n");
		break;
	default:
		printf("Wrong criterion number entered. Try again!\n");
		break;
	}
}

void exit_helper(trie_t **trie)
{
	trie_free(trie);
}
