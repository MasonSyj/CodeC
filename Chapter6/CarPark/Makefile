CC=clang
COMMON= -Wall -Wextra -Wfloat-equal -pedantic -std=c99 -Werror -Wvla
DEBUG= -g3
SANITIZE= $(COMMON) -fsanitize=undefined -fsanitize=address $(DEBUG)
VALGRIND= $(COMMON) $(DEBUG)
PRODUCTION= $(COMMON) -O3
LDLIBS = -lm

all : prk16t prknonet1 prk1t prk3t prk11t prk13t nocars
all_extension : prk16t_ex prknonet1_ex prk1t_ex prk3t_ex prk11t_ex prk13t_ex nocars_ex nonconsec_ex prk26t_ex prkself_ex prkself2_ex

prk16t : main.c
	$(CC) main.c -o prk16t $(SANITIZE) $(LDLIBS)

prknonet1 : main.c
	$(CC) main.c -o prknonet1 $(SANITIZE) $(LDLIBS)

prk1t: main.c
	$(CC) main.c -o prk1t $(SANITIZE) $(LDLIBS)
	
prk3t: main.c
	$(CC) main.c -o prk3t $(SANITIZE) $(LDLIBS)
	
prk11t: main.c
	$(CC) main.c -o prk11t $(SANITIZE) $(LDLIBS)
	
prk13t: main.c
	$(CC) main.c -o prk13t $(SANITIZE) $(LDLIBS)
	
nocars: main.c
	$(CC) main.c -o nocars $(SANITIZE) $(LDLIBS)
	
nonconsec: main.c
	$(CC) main.c -o nonconsec $(SANITIZE) $(LDLIBS)
	
wrongshape: main.c
	$(CC) main.c -o wrongshape $(SANITIZE) $(LDLIBS)
	
wrongshape2: main.c
	$(CC) main2.c -o wrongshape2 $(SANITIZE) $(LDLIBS)

prk26t: main.c
	$(CC) main2.c -o prk26t $(SANITIZE) $(LDLIBS)
	
prk26: prk26t
	./prk26t 11x9_10c_26t.prk
	
	
prk16t_ex : extension.c
	$(CC) extension.c -o prk16t_ex $(SANITIZE) $(LDLIBS)

prknonet1_ex : extension.c
	$(CC) extension.c -o prknonet1_ex $(SANITIZE) $(LDLIBS)

prk1t_ex : extension.c
	$(CC) extension.c -o prk1t_ex $(SANITIZE) $(LDLIBS)
	
prk3t_ex : extension.c
	$(CC) extension.c -o prk3t_ex $(SANITIZE) $(LDLIBS)
	
prk11t_ex : extension.c
	$(CC) extension.c -o prk11t_ex $(SANITIZE) $(LDLIBS)
	
prk13t_ex : extension.c
	$(CC) extension.c -o prk13t_ex $(SANITIZE) $(LDLIBS)
	
nocars_ex : extension.c
	$(CC) extension.c -o nocars_ex $(SANITIZE) $(LDLIBS)
	
nonconsec_ex : extension.c
	$(CC) extension.c -o nonconsec_ex $(SANITIZE) $(LDLIBS)
	
wrongshape_ex : extension.c
	$(CC) extension.c -o wrongshape_ex $(SANITIZE) $(LDLIBS)
	
wrongshape2_ex : extension.c
	$(CC) extension.c -o wrongshape2_ex $(SANITIZE) $(LDLIBS)

prk26t_ex : extension.c
	$(CC) extension.c -o prk26t_ex $(SANITIZE) $(LDLIBS)
	
prkself_ex: extension.c 
	$(CC) extension.c -o prkself_ex $(SANITIZE) $(LDLIBS)

prkself2_ex: extension.c 
	$(CC) extension.c -o prkself2_ex $(SANITIZE) $(LDLIBS)
	
w1: wrongshape2
	./wrongshape2 wrongshape2.prk
w2: wrongshape
	./wrongshape wrongshpae.prk
	
run : all
	./prk16t 10x7_8c_16t.prk
	./prknonet1 10x7_8c_none.prk
	./prk1t 4x4_1c_1t.prk
	./prk3t 6x6_2c_3t.prk
	./prk11t 7x7_4c_11t.prk
	./prk13t 10x8_5c_13t.prk
	./nocars nocars.prk

run_show : all
	./prk16t -show 10x7_8c_16t.prk
	./prknonet1 -show 10x7_8c_none.prk
	./prk1t -show 4x4_1c_1t.prk
	./prk3t -show 6x6_2c_3t.prk
	./prk11t -show 7x7_4c_11t.prk
	./prk13t -show 10x8_5c_13t.prk
	./nocars -show nocars.prk
	
run_ex : all_extension
	./prk16t_ex 10x7_8c_16t.prk
	./prknonet1_ex 10x7_8c_none.prk
	./prk1t_ex 4x4_1c_1t.prk
	./prk3t_ex 6x6_2c_3t.prk
	./prk11t_ex 7x7_4c_11t.prk
	./prk13t_ex 10x8_5c_13t.prk
	./nocars_ex nocars.prk
	./nonconsec_ex nonconsec.prk
	./prk26t_ex 11x9_10c_26t.prk
	./prkself_ex 11x20_26c_142t.prk
	./prkself2_ex 20x20_26c_186t.prk
	
run_ex_show : all_extension
	./prk16t_ex -show 10x7_8c_16t.prk
	./prknonet1_ex -show 10x7_8c_none.prk
	./prk1t_ex -show 4x4_1c_1t.prk
	./prk3t_ex -show 6x6_2c_3t.prk
	./prk11t_ex -show 7x7_4c_11t.prk
	./prk13t_ex -show 10x8_5c_13t.prk
	./nocars_ex -show nocars.prk
	./nonconsec_ex -show nonconsec.prk
	./prk26t_ex -show 11x9_10c_26t.prk
	./prkself_ex -show 11x20_26c_142t.prk
	./prkself2_ex -show 20x20_26c_186t.prk

	

clean:
	rm -fr prk16t prknonet1 prk1t prk3t prk11t prk13t nocars nonconsec wrongshape wrongshape2 prk26t prk16t_ex prknonet1_ex prk1t_ex prk3t_ex prk11t_ex prk13t_ex nocars_ex nonconsec_ex wrongshape_ex wrongshape2_ex prk26t_ex prkself2_ex prkself_ex
