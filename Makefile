CC = cc
CFLAGS = -std=c99 -pedantic -Wall -Wextra

all: ls

clean:
	rm -f ls

.PHONY: all clean
