# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -ansi -g 

# the build target executable:
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

# gcc -ansi -g -o simQ main.c