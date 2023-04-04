CC = g++
CFLAGS = -g -Wall

TARGET = main

all: $(TARGET)

$(TARGET): main.o
	$(CC) $(CFLAGS) $^ -o $(TARGET)

main.o: main.c main.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)

debug: $(TARGET)
	gdb $(TARGET)

.PHONY: all clean debug
