CC=gcc
CFLAGS=-I.
DEP=ntk_5.4.h
OBJECTS=ntk_5.4.o main.o

mainProgram: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c $(DEP)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJECTS) mainProgram