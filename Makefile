CC = cc
CFLAGS = -std=c99 -pedantic -Wall -Wextra
CPPFLAGS = -D_DEFAULT_SOURCE \
     -D_NETBSD_SOURCE \
     -D_BSD_SOURCE \
     -D_XOPEN_SOURCE=700 \
     -D_FILE_OFFSET_BITS=64

all: ls

clean:
	rm -f ls

.PHONY: all clean
