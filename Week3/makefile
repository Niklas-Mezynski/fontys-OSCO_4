CC=gcc
CFLAGS=-I.
DEP=LL.h
OBJECTS=LL.o LLTest.o

linkedlist: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c $(DEP)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJECTS) linkedlist