IDIR =.
CC=g++
CFLAGS=-O3 -std=c++11 -march=native
LDIR =../lib
EXPR=../expr
LIBS=

ALL: prepare  gitversion.c v1dim v2dim

#s1dim t1dim


prepare:
	mkdir -p ../data
	cp data/* ../data
	mkdir -p $(EXPR)
	mkdir -p ../results
	cp expr/*.sh $(EXPR)
	cp expr/load.sql $(EXPR)
	cp vs/random $(EXPR)
	cp vs/test $(EXPR)

gitversion.c: .git/HEAD .git/index
	echo "const char *gitversion = \"$(shell git rev-parse HEAD)\";" > $@

v1dim:trie.cc 1dimv0.cc gitversion.c
	$(CC) -o $(EXPR)/$@ -D__1DIM__ -D__EXPR__ trie.cc 1dimv0.cc gitversion.c $(CFLAGS) $(LIBS)

s1dim:trie.cc 1dimv0.cc gitversion.c
		$(CC) -o $(EXPR)/$@  -D__1DIM__ -D__STAT__ trie.cc 1dimv0.cc gitversion.c $(CFLAGS) $(LIBS)

t1dim:trie.cc 1dimv0.cc gitversion.c
				$(CC) -o $(EXPR)/$@  -D1__1DIM__ -D__TEST__ trie.cc 1dimv0.cc gitversion.c $(CFLAGS) $(LIBS)



v2dim:trie.cc 1dimv0.cc gitversion.c
		$(CC) -o $(EXPR)/$@ -D__2DIM__ -D__EXPR__ trie.cc 1dimv0.cc gitversion.c $(CFLAGS) $(LIBS)

s2dim:trie.cc 1dimv0.cc gitversion.c
		$(CC) -o $(EXPR)/$@  -D__2DIM__ -D__STAT__ trie.cc 1dimv0.cc gitversion.c $(CFLAGS) $(LIBS)

t2dim:trie.cc 1dimv0.cc gitversion.c
	$(CC) -o $(EXPR)/$@  -D1__2DIM__ -D__TEST__ trie.cc 1dimv0.cc gitversion.c $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *.o b1dim magdy/m1dim magdy/m1dimo magdy/md1dim gitversion.c
