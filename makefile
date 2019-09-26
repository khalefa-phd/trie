IDIR =.
CC=g++
CFLAGS= -std=c++11 -march=native
LDIR =../lib
EXPR=../expr
LIBS=
FILES=trie.cc expr.cc gitversion.c
EXPRFLAGS= -O3 -D__EXPR__ $(CFLAGS)
STATFLAGS= -D__STAT__ $(CFLAGS)
TESTFLAGS=-D__TEST__ -D__DEBUG3__ -D__DEBUG2__ -D__DEBUG__ $(CFLAGS)

DIM1FLGAS=-D__1DIM__
DIM2FLGAS=-D__2DIM__

ALL: gitversion.c 1dim 2dim


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

1dim:e1dim s1dim t1dim oe1dim ot1dim

2dim:e2dim s2dim t2dim oe2dim ot2dim

e1dim:$(FILES)
	$(CC) -o $(EXPR)/$@ -D__TOPK__ $(DIM1FLGAS) $(EXPRFLAGS) $(FILES) $(LIBS)

s1dim:$(FILES)
	$(CC) -o $(EXPR)/$@ -D__TOPK__ $(DIM1FLGAS) $(STATFLAGS) $(FILES) $(LIBS)

t1dim:$(FILES)
	$(CC) -o $(EXPR)/$@ -D__TOPK__ $(DIM1FLGAS) $(TESTFLAGS) $(FILES) $(LIBS)

e2dim:$(FILES)
		$(CC) -o $(EXPR)/$@ -D__TOPK__ $(DIM2FLAGS) $(EXPRFLAGS) $(FILES) $(LIBS)

s2dim:$(FILES)
		$(CC) -o $(EXPR)/$@ -D__TOPK__ $(DIM2FLAGS) $(STATFLAGS) $(FILES) $(LIBS)

t2dim:$(FILES)
	$(CC) -O3 -o $(EXPR)/$@  -D__TOPK__ $(DIM2FLAGS) $(TESTFLAGS) $(FILES) $(LIBS)

oe1dim:$(FILES)
	$(CC) -o $(EXPR)/$@ -D__THRESHOLD__ $(DIM1FLGAS) $(EXPRFLAGS) $(FILES) $(LIBS)

ot1dim:$(FILES)
	$(CC) -o $(EXPR)/$@ -D__THRESHOLD__ $(DIM1FLGAS) $(TESTFLAGS) $(FILES) $(LIBS)

oe2dim:$(FILES)
	$(CC) -o $(EXPR)/$@ -D__THRESHOLD__ $(DIM2FLGAS) $(EXPRFLAGS) $(FILES) $(LIBS)

ot2dim:$(FILES)
	$(CC) -o $(EXPR)/$@ -D__THRESHOLD__ $(DIM2FLGAS) $(TESTFLAGS) $(FILES) $(LIBS)

.PHONY: clean

clean:
	rm -f *.o gitversion.c
	rm -f $(EXPR)/e1dim $(EXPR)/oe1dim $(EXPR)/t1dim $(EXPR)/s1dim $(EXPR)/oe1dim
	rm -f $(EXPR)/e2dim $(EXPR)/s2dim $(EXPR)/t2dim 
