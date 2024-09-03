PROG=main.c
CC=gcc
CFLAGS= -Wall -Werror -O3

.PHONY: build
build: 
	mkdir -p build
	$(CC) $(CFLAGS) $(PROG) -o ./build/$(basename $(notdir $(PROG)))

.PHONY: clean
clean: 
	rm -rf ./build
