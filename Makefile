shafa=shafa.c
modulo_b=modulo_b/modulo_t.c
modulo_a=modulo_a/modulo_a.c
debug=-g
#errors=-std=gnu11 -Wall -Wextra -pedantic-errors

all:
	gcc $(debug) -o shafa $(shafa) $(modulo_b) $(modulo_a)