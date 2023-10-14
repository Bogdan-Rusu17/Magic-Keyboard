#COPYRIGHT RUSU BOGDAN, 2023
# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -Wshadow -Wpedantic -std=c99 -O0 -g

# define targets
TARGETS=mk

#define object-files
OBJ=mk.o trie.o helper_functions.o autocorrect.o autocomplete.o

build: $(TARGETS)

mk: mk.o trie.o helper_functions.o autocorrect.o autocomplete.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGETS) $(OBJ)

.PHONY: pack clean
