CC = gcc
CFLAGS =-O3 -Wall -ansi
DEPS = lists.h words.h utils.h
OBJ = lists.o utils.o utils.o main.o

%.o: %.c $(DEPS)
		$(CC) $(CFLAGS) -c -o $@ $< 
		
wordmorph: $(OBJ)
		$(CC) $(CFLAGS) -o wordmorph $(OBJ)
		
clean:
		rm -f *.o *.path wordmorph *~
