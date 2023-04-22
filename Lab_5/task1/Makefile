CC = g++
CFLAGS = -g -Wall

TARGET = main

all: $(TARGET)

$(TARGET): main.o
	$(CC) $(CFLAGS) $^ -o $(TARGET)

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET) && rm -f shared.txt

debug: $(TARGET)
	gdb $(TARGET)

.PHONY: all clean debug
