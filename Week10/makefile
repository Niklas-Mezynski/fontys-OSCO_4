CC=gcc
CFLAGS=-I.
DEP=LL.h
OBJECTS=LL.o main.o

main: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c $(DEP)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJECTS)