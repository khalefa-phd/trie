IDIR =.
CC=g++
CFLAGS= -std=c++11 -march=native
LDIR =../lib
EXPR=../expr
LIBS=

ALL:  gitversion.c v1dim v2dim s1dim t1dim t2dim s2dim


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

v1dim:trie.cc expr.cc gitversion.c meta.h trie.h common.h
	$(CC) -o $(EXPR)/$@ -O3 -D__1DIM__ -D__EXPR__ trie.cc expr.cc gitversion.c $(CFLAGS) $(LIBS)

s1dim:trie.cc expr.cc gitversion.c
		$(CC) -o $(EXPR)/$@  -D__1DIM__ -D__STAT__ trie.cc expr.cc gitversion.c $(CFLAGS) $(LIBS)

t1dim:trie.cc expr.cc gitversion.c
		$(CC) -o $(EXPR)/$@  -D__1DIM__ -D__TEST__ trie.cc expr.cc gitversion.c $(CFLAGS) $(LIBS)


v2dim:trie.cc expr.cc gitversion.c
		$(CC) -o $(EXPR)/$@ -O3 -D__2DIM__ -D__EXPR__ trie.cc expr.cc gitversion.c $(CFLAGS) $(LIBS)

s2dim:trie.cc expr.cc gitversion.c meta.h
		$(CC) -o $(EXPR)/$@  -D__2DIM__ -D__STAT__ trie.cc expr.cc gitversion.c $(CFLAGS) $(LIBS)

t2dim:trie.cc expr.cc gitversion.c meta.h
	$(CC) -O3 -o $(EXPR)/$@ -D__DEBUG3__ -D__DEBUG2__  -D__2DIM__ -D__TEST__ trie.cc expr.cc gitversion.c $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *.o  gitversion.c
