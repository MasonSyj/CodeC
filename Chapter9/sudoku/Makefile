# Use clang in the labs & not gcc, especially for sanitizer...
CC= clang

# Our 'core' set of flags used for everything
COREFLAGS= -Wall -Wextra -Wpedantic -std=c99 -Wvla -Wfloat-equal -Werror

# 'Standard' compilation
STANFLAGS= $(COREFLAGS) -O1

# Sanitizer Flags
SANIFLAGS= $(COREFLAGS) -fsanitize=address -fsanitize=undefined -g3 

# Don't think anyone will actually need the maths lib...
LDLIBS= -lm

all : sudoku sudoku sudoku_s sudoku_s

# Standard Build: type "make conceal" or "make inkblot"
sudoku : sudoku.c 
	$(CC) sudoku.c  -o sudoku $(STANFLAGS) $(LDLIBS)
sudoku2 : sudoku2.c 
	$(CC) sudoku2.c -o sudoku2 $(STANFLAGS) $(LDLIBS)

# Sanitizer Code: type "make conceal_s" or "make inkblot_s"
sudoku_s : sudoku.c 
	$(CC) sudoku.c  -o sudoku_s $(SANIFLAGS) $(LDLIBS)
sudoku2_s : sudoku2.c 
	$(CC) sudoku2.c -o sudoku2_s $(SANIFLAGS) $(LDLIBS)



clean:
	rm -f sudoku sudoku2 sudoku_s sudoku2_s
