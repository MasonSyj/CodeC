CC=clang
COMMON= -Wall -Wextra -Wfloat-equal -pedantic -std=c99 -Werror -Wvla
DEBUG= -g3
SANITIZE= $(COMMON) -fsanitize=undefined -fsanitize=address $(DEBUG)
VALGRIND= $(COMMON) $(DEBUG)
PRODUCTION= $(COMMON) -O3
LDLIBS = -lm

all : fa fa_s fa_v fa_2

fa : pointerarray.c
	$(CC) pointerarray.c -o pa $(PRODUCTION)

fa_s : pointerarray.c
	$(CC) pointerarray.c -o pa $(SANITIZE) $(LDLIBS)

fa_v: pointerarray.c
	$(CC) pointerarray.c -o pa $(COMMON) $(LDLIBS)
	
fa_2: fixedarray2.c
	$(CC) fixedarray2.c -o pa_2 $(SANITIZE) $(LDLIBS)
	
run: all
	./fa
	./fa_s
	./fa_v

clean:
	rm -fr famake famake_s famake_v
