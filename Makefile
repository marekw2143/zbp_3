CC=g++
CFLAGS=-Wall -Wextra -g
main: main.cpp
	$(CC) $< -o$@ $(CFLAGS)
