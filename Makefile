# Makefile - Simulador de Misiones Artemis (Escenario 2: Orbita LEO)
# Uso:
#   make          -> compila el programa
#   make run      -> compila y ejecuta
#   make clean    -> borra los archivos generados

CC      = gcc
CFLAGS  = -Wall -Wextra -pedantic -std=c99
LDLIBS  = -lm
TARGET  = simulador_artemis
OBJS    = main.o simulador.o validaciones.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDLIBS)

# Cada .o se recompila si cambia su .c o alguno de los encabezados
main.o: main.c simulador.h validaciones.h
	$(CC) $(CFLAGS) -c main.c

simulador.o: simulador.c simulador.h
	$(CC) $(CFLAGS) -c simulador.c

validaciones.o: validaciones.c validaciones.h
	$(CC) $(CFLAGS) -c validaciones.c

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).exe

.PHONY: all run clean
