###################################
### 	--GRUP ELEMANLARI--      ## 
###################################
#_1_ Eysd Almansour (B141210127)
#_2_ Zaher Khirullah(B151210568)
#_3_ Mohammad Almahamid (B141210263)
#_4_ Mumin Othman (G151210563)
#_5_ Abdulrahamn hamidi (G151210551)
####################################

INC = ./libfdr
LIB = ./libfdr 
CC  = gcc
SRC = prog.c  shell.c Siparis.c
CFLAGS  = -Wall -g
OBJ = shell.o  prog.o Siparis.o

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