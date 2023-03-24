CC = g++
CFLAGS = -g -Wall

TARGET = lab2

all: $(TARGET)

$(TARGET): main.o funcA.o funcB.o
	$(CC) $(CFLAGS) $^ -o $(TARGET)

main.o: main.c main.h
	$(CC) $(CFLAGS) -c $< -o $@

funcA.o: funcA.c funcA.h
	$(CC) $(CFLAGS) -c $< -o $@

funcB.o: funcB.c funcB.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)

debug: $(TARGET)
	gdb $(TARGET)

.PHONY: all clean debug
