# In *my* code, I had the interpreter code added to the parser code.
# This additional code is protected by #ifdef INTERP / #endif clauses.
# This code is only "seen" by the compiler if you have #defined INTERP
# This #define would be annoying to change inside nuclei.c/.h, so instead it is
# set in the gcc/clang statement using -DINTERP
# In this way ./parse & ./interp can both be built from the same source file.

CC      := clang
DEBUG   := -g3
OPTIM   := -O3
CFLAGS  := -Wall -Wextra -Wpedantic -Wfloat-equal -Wvla -std=c99 -Werror
RELEASE := $(CFLAGS) $(OPTIM)
SANI    := $(CFLAGS) -fsanitize=undefined -fsanitize=address $(DEBUG)
VALG    := $(CFLAGS)  $(DEBUG)
NCLS    := $(wildcard *.ncl)
PRES := $(NCLS:.ncl=.pres)
IRES := $(NCLS:.ncl=.ires)
ERES := $(NCLS:.ncl=.eres)
LIBS    := -lm

parse_o: nuclei.c general.c nuclei.h
	$(CC) nuclei.c general.c $(RELEASE) -o parse_o $(LIBS)

parse_s: nuclei.c general.c nuclei.h
	$(CC) nuclei.c general.c $(SANI) -o parse_s $(LIBS)

parse_v: nuclei.c general.c nuclei.h
	$(CC) nuclei.c general.c $(VALG) -o parse_v $(LIBS)

all: parse_o parse_s parse_v interp_o interp_s interp_v extension_o

interp_o: nuclei.c linked.c general.c nuclei.h lisp.h general.h
	$(CC) nuclei.c linked.c general.c $(RELEASE) -DINTERP -o interp_o $(LIBS)

interp_s: nuclei.c linked.c general.c nuclei.h lisp.h general.h
	$(CC) nuclei.c linked.c general.c $(SANI) -DINTERP -o interp_s $(LIBS)

interp_v: nuclei.c linked.c general.c nuclei.h lisp.h general.h
	$(CC) nuclei.c linked.c general.c $(VALG) -DINTERP -o interp_v $(LIBS)

extension_o: extension.c linked.c general.c nuclei.h lisp.h general.h
	$(CC) extension.c linked.c general.c $(SANI) -DINTERP -o extension $(LIBS)
	

functest_driver: functest.c linked.c general.c nuclei.h lisp.h general.h
	$(CC) functest.c linked.c general.c $(SANI) -o functest $(LIBS)


# For all .ncl files, run them and output result to a .pres (prase result) 
# or .ires (interpretted result) file.
runall : ./parse_s ./interp_s $(PRES) $(IRES)
		
	
parse: parse_s ./parse_s $(PRES)
		

interp: interp_s ./interp_s $(IRES)
		

extension: clean extension_o ./extension $(ERES)
	


#extension: extension_o ./extension  $(ERES)

functest: functest_driver
	./functest

error: parse_s ./parse_s $(PRES)
		
correct: interp_s ./interp_s $(IRES)	

	
%.pres:
	-./parse_s  $*.ncl > $*.pres 2>&1
%.ires:
	-./interp_s $*.ncl > $*.ires 2>&1
%.eres:
	-./extension $*.ncl > $*.eres 2>&1
	
clean:
	rm -f parse_o parse_s parse_v interp_o interp_s interp_v extension_o $(PRES) $(IRES) $(ERES) functest_driver $(ERRORTEST) $(CORRECTEST) 
