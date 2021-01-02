shafa=shafa.c
modulo_b=modulo_b/modulo_t.c
debug=-g
#errors=-std=gnu11 -Wall -Wextra -pedantic-errors

all:
	gcc $(debug) -o shafa $(shafa) $(modulo_b) 