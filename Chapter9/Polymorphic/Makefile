CC=clang
COMMON= -Wall -Wextra -Wfloat-equal -Wvla -Wpedantic -std=c99 -Werror
DEBUG= -g3
SANITIZE= $(COMMON) -fsanitize=undefined -fsanitize=address $(DEBUG)
VALGRIND= $(COMMON) $(DEBUG)
PRODUCTION= $(COMMON) -O3
LDLIBS =

all: testrealloc_s testrealloc_v testrealloc

testrealloc : varr.h realloc.c testarr.c
	$(CC) testarr.c realloc.c -o testrealloc $(PRODUCTION) $(LDLIBS)

testrealloc_s : varr.h realloc.c testarr.c 
	$(CC) testarr.c realloc.c -o testrealloc_s $(SANITIZE) $(LDLIBS)

testrealloc_v : varr.h realloc.c testarr.c 
	$(CC) testarr.c realloc.c -o testrealloc_v  $(VALGRIND) $(LDLIBS)


clean:
	rm -f testrealloc_s testrealloc_v testrealloc

run: testrealloc
	./testrealloc

runall: all
	./testrealloc
	./testrealloc_s
	valgrind ./testrealloc_v
