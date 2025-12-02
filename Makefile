CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11

TARGET = ejercicio1
OBJS = main.o examen.o

all: clear_screen $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c examen.h
	$(CC) $(CFLAGS) -c main.c

examen.o: examen.c examen.h
	$(CC) $(CFLAGS) -c examen.c


clear_screen:
	clear

clean:
	rm -f $(OBJS) $(TARGET)
