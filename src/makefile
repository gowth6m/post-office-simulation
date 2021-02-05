# This makefile is to compile the program just incase the executable from above directory isn't working.
CC = gcc

CFLAGS  = -ansi -g 

TARGET = simQ

OBJS = simulation.o fileManager.o customerQueue.o randGenerator.o

all: $(TARGET)

$(TARGET): main.c $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) main.c $(OBJS)

simulation.o: simulation.c customerQueue.o
	$(CC) -c $(CFLAGS) simulation.c

fileManager.o: fileManager.c
	$(CC) -c $(CFLAGS) fileManager.c

customerQueue.o: customerQueue.c
	$(CC) -c $(CFLAGS) customerQueue.c

randGenerator.o: randGenerator.c
	$(CC) -c $(CFLAGS) randGenerator.c

clean:
	rm $(TARGET)
	rm $(OBJS)
