CC      = gcc
CFLAGS  = -std=c99 -Wall -Wextra -pedantic
LDLIBS  = -lm

all: orbita_demo test_orbita

orbita_demo: main_orbita.o orbita.o validaciones.o
	$(CC) $^ -o $@ $(LDLIBS)

test_orbita: test_orbita.o orbita.o
	$(CC) $^ -o $@ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: test_orbita
	./test_orbita

clean:
	rm -f *.o orbita_demo test_orbita

.PHONY: all test clean
