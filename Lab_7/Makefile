CC = gcc
CFLAGS = -g -Wall

TARGET_SERVER = server
TARGET_CLIENT = client

all: $(TARGET_SERVER) $(TARGET_CLIENT) 

$(TARGET_SERVER): server.o
	$(CC) $(CFLAGS) $^ -o $(TARGET_SERVER)

$(TARGET_CLIENT): client.o
	$(CC) $(CFLAGS) $^ -o $(TARGET_CLIENT)

server.o: server.c
	$(CC) $(CFLAGS) -c $< -o $@

client.o: client.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET_SERVER) $(TARGET_CLIENT)

debug_server: $(TARGET_SERVER)
	gdb $(TARGET_SERVER)

debug_client: $(TARGET_CLIENT)
	gdb $(TARGET_CLIENT)

.PHONY: all clean debug_server debug_client
