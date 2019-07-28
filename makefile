IDIR =.
CC=g++
CFLAGS=-O3 -std=c++11 -march=native
LDIR =../lib
EXPR=../expr
LIBS=

ALL: prepare  gitversion.c v1dim s1dim


prepare:
	cp expr/*.sh $(EXPR)
	cp expr/load.sql $(EXPR)

gitversion.c: .git/HEAD .git/index
	echo "const char *gitversion = \"$(shell git rev-parse HEAD)\";" > $@

v1dim:trie.cc 1dimv0.cc gitversion.c
	$(CC) -o $(EXPR)/$@ -D__EXPR__ trie.cc 1dimv0.cc gitversion.c $(CFLAGS) $(LIBS)

s1dim:trie.cc 1dimv0.cc gitversion.c
		$(CC) -o $(EXPR)/$@  -D__STAT__ trie.cc 1dimv0.cc gitversion.c $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *.o b1dim magdy/m1dim magdy/m1dimo magdy/md1dim gitversion.c
