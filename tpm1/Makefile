CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
SOURCES = main.c lsobb.c lsobb_f.c abb.c abb_f.c utilidades.c costos.c
HEADERS = tipos.h lsobb.h lsobb_f.h abb.h abb_f.h utilidades.h costos.h
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = padron.exe

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	del /Q *.o *.exe

run: $(EXECUTABLE)
	./$(EXECUTABLE)

.PHONY: all clean run
