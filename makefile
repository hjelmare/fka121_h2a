

CC = gcc
CFLAGS = -O3 -g
LIBS = -lm

HEADERS = ba_func.h
OBJECTS = ba_func.o ba_main.o
PROGRAM = ba

%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -f *.o
	touch *.c

