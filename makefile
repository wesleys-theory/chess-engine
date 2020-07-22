CC=gcc
CFLAGS=-Wall
DEPS = definitions.h initialise.h bitboards.h
OBJ = main.o chess.o initialise.o bitboards.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o *.exe