CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c99 -pedantic
DEPS = grafo.h bfs.h
OBJ = main.o grafo.o bfs.o
%.o: %.c $(DEPS)
				$(CC) -c -o $@ $< $(CFLAGS)

exec: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	$(RM) *.o
