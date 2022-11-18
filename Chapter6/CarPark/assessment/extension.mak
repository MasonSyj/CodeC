CC=clang
COMMON= -Wall -Wextra -Wfloat-equal -pedantic -std=c99 -Werror -Wvla
DEBUG= -g3
SANITIZE= $(COMMON) -fsanitize=undefined -fsanitize=address $(DEBUG)
VALGRIND= $(COMMON) $(DEBUG)
PRODUCTION= $(COMMON) -O3
LDLIBS = -lm

all_extension : prk16t_ex prknonet1_ex prk1t_ex prk3t_ex prk11t_ex prk13t_ex nocars_ex nonconsec_ex prk26t_ex prkself_ex prkself2_ex prkself3_ex

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
	
prkself3_ex: extension.c 
	$(CC) extension.c -o prkself3_ex $(SANITIZE) $(LDLIBS)	
	
run_ex : all_extension
	./prk16t_ex 10x7_8c_16t.prk
	./prknonet1_ex 10x7_8c_none.prk
	./prk1t_ex 4x4_1c_1t.prk
	./prk3t_ex 6x6_2c_3t.prk
	./prk11t_ex 7x7_4c_11t.prk
	./prk13t_ex 10x8_5c_13t.prk
	./nocars_ex nocars.prk
	./prk26t_ex 11x9_10c_26t.prk
	./prkself_ex 11x20_26c_142t.prk
	./prkself2_ex 20x20_26c_186t.prk
	./prkself3_ex 20x20_26c_244t.prk
	
run_ex_show : all_extension
	./prk16t_ex -show 10x7_8c_16t.prk
	./prknonet1_ex -show 10x7_8c_none.prk
	./prk1t_ex -show 4x4_1c_1t.prk
	./prk3t_ex -show 6x6_2c_3t.prk
	./prk11t_ex -show 7x7_4c_11t.prk
	./prk13t_ex -show 10x8_5c_13t.prk
	./nocars_ex -show nocars.prk
	./prk26t_ex -show 11x9_10c_26t.prk
	./prkself_ex -show 11x20_26c_142t.prk
	./prkself2_ex -show 20x20_26c_186t.prk
	./prkself3_ex -show 20x20_26c_244t.prk
	

clean:
	rm -fr  prk16t_ex prknonet1_ex prk1t_ex prk3t_ex prk11t_ex prk13t_ex nocars_ex nonconsec_ex wrongshape_ex wrongshape2_ex prk26t_ex prkself2_ex prkself_ex prkself3_ex
