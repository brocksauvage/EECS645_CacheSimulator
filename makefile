
CC=gcc
CFLAGS= -ansi -std=c99 -pedantic -Wall -m32

cache_simulator : cache_simulator.c
	$(CC) $(CFLAGS) $^ -o $@
clean:
	rm cache_simulator