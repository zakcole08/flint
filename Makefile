CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SRC = src/main.c src/lexer.c
HEADERS = src/token.h src/lexer.h

all: flint

flint: $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) -o flint $(SRC)

clean:
	rm -f flint
	