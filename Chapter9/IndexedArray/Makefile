CC=clang
GENPATH=../../../../Git/ADTs/General
COMMON= -Wall -Wextra -Wfloat-equal -Wvla -Wpedantic -std=c99 -Werror
DEBUG= -g3
SANITIZE= $(COMMON) -fsanitize=undefined -fsanitize=address $(DEBUG)
VALGRIND= $(COMMON) $(DEBUG)
PRODUCTION= $(COMMON) -O3
LDLIBS =

all: testrealloc_s testrealloc_v testrealloc

testrealloc : arr.h Realloc.c testarr.c 
	$(CC) testarr.c Realloc.c  -o testrealloc $(PRODUCTION) $(LDLIBS)

testrealloc_s : arr.h Realloc.c testarr.c 
	$(CC) testarr.c Realloc.c  -o testrealloc_s $(SANITIZE) $(LDLIBS)
	
testrealloc_v : arr.h Realloc.c testarr.c 
	$(CC) testarr.c Realloc.c  -o testrealloc_v $(VALGRIND) $(LDLIBS)


clean:
	rm -f testrealloc_s testrealloc_v testrealloc

run: testrealloc
	testrealloc_s
	testrealloc_v
	

runall: all
	./testrealloc
	./testrealloc_s
	./testrealloc_v
