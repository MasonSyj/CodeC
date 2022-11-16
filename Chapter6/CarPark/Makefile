CC=clang
COMMON= -Wall -Wextra -Wfloat-equal -pedantic -std=c99 -Werror -Wvla
DEBUG= -g3
SANITIZE= $(COMMON) -fsanitize=undefined -fsanitize=address $(DEBUG)
VALGRIND= $(COMMON) $(DEBUG)
PRODUCTION= $(COMMON) -O3
LDLIBS = -lm

all : prk16t prknonet1 prk1t prk3t prk11t prk13t nocars nonconsec

prk16t : main2.c
	$(CC) main2.c -o prk16t $(PRODUCTION)

prknonet1 : main2.c
	$(CC) main2.c -o prknonet1 $(SANITIZE) $(LDLIBS)

prk1t: main2.c
	$(CC) main2.c -o prk1t $(COMMON) $(LDLIBS)
	
prk3t: main2.c
	$(CC) main2.c -o prk3t $(SANITIZE) $(LDLIBS)
	
prk11t: main2.c
	$(CC) main2.c -o prk11t $(SANITIZE) $(LDLIBS)
	
prk13t: main2.c
	$(CC) main2.c -o prk13t $(SANITIZE) $(LDLIBS)
	
nocars: main2.c
	$(CC) main2.c -o nocars $(SANITIZE) $(LDLIBS)
	
nonconsec: main2.c
	$(CC) main2.c -o nonconsec $(SANITIZE) $(LDLIBS)
	
wrongshape: main2.c
	$(CC) main2.c -o wrongshape $(SANITIZE) $(LDLIBS)
	
wrongshape2: main2.c
	$(CC) main2.c -o wrongshape2 $(SANITIZE) $(LDLIBS)

prk26t: main2.c
	$(CC) main2.c -o prk26t $(SANITIZE) $(LDLIBS)
	
run: all
	./prk16t 10x7_8c_16t.prk
	./prknonet1 10x7_8c_none.prk
	./prk1t 4x4_1c_1t.prk
	./prk3t 6x6_2c_3t.prk
	./prk11t 7x7_4c_11t.prk
	./prk13t 10x8_5c_13t.prk
	./nocars nocars.prk
	./nonconsec nonconsec.prk

prk26: prk26t
	./prk26t 11x9_10c_26t.prk
	
w1: wrongshape2
	./wrongshape2 wrongshape2.prk
w2: wrongshape
	./wrongshape wrongshpae.prk
	

clean:
	rm -fr prk16t prknonet1 prk1t prk3t prk11t prk13t nocars nonconsec wrongshape wrongshape2 prk26t
