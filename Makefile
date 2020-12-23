CC ?= cc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -o
SRC = hxr.c

hxr: $(SRC)
	@$(CC) $(SRC) $(CFLAGS) $@

install: hxr
	@mv hxr /bin

clean:
	@rm -f hxr; rm -f /bin/hxr

.PHONY: clean install
