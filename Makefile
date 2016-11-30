CC = gcc
CFLAGS =-O3 -Wall -ansi
DEPS = datastructs.h words.h utils.h stack.h
OBJ = datastructs.o stack.o utils.o words.o main.o

%.o: %.c $(DEPS)
		$(CC) $(CFLAGS) -c -o $@ $< 
		
wordmorph: $(OBJ)
		$(CC) $(CFLAGS) -o wordmorph $(OBJ)
		
clean:
		rm -f *.o *.path wordmorph *~
