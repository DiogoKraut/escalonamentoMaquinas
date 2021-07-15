# Diogo Paris Kraut - GRR 20166365

TARGET = tempo
CC = gcc
CFLAGS = -Wall -g

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

default: $(TARGET)
all: default

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o $@

clean:
	-rm -f *.o core

purge:
	-rm -f *.o core
	-rm -f $(TARGET)