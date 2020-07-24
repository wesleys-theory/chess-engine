CC=gcc
CFLAGS=-Wall
DEPS = definitions.h initialise.h bitboards.h hashkeys.h board.h
OBJ = main.o initialise.o bitboards.o hashkeys.o board.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o *.exe