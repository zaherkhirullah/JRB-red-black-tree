###################################
###################################
# Zaher Khirullah
####################################

INC = ./libfdr
LIB = ./libfdr
CC  = gcc
SRC = prog.c  shell.c siparis.c
CFLAGS  = -Wall -g
OBJ = shell.o  prog.o siparis.o

EX = clean shell
all: $(EX)

shell: $(SRC)
	$(CC) $(SRC) -I$(INC) -o test -L$(LIB) -lfdr
	@echo " “Compile completed” "

.SUFFIXES: .c .o
%.o: %.c
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f $(EX) *.o
	@echo " “Clean completed” "

# $(CC) $(CFLAGS) -o shell $(OBJ)