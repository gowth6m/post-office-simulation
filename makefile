# # the compiler: gcc for C program, define as g++ for C++
# CC = gcc

# # compiler flags:
# #  -g    adds debugging information to the executable file
# #  -Wall turns on most, but not all, compiler warnings
# CFLAGS  = -ansi -g 

# # # the build target executable:
# TARGET = simQ

# OBJS = simulation.o fileManager.o customerQueue.o

# all: $(TARGET)

# $(TARGET): main.c $(OBJS)
# 	$(CC) $(CFLAGS) -o $(TARGET) main.c $(OBJS)

# simulation.o: simulation.c customerQueue.o
# 	$(CC) -c $(CFLAGS) simulation.c

# fileManager.o: fileManager.c
# 	$(CC) -c $(CFLAGS) fileManager.c

# customerQueue.o: customerQueue.c
# 	$(CC) -c $(CFLAGS) customerQueue.c

# clean:
# 	rm $(TARGET)
# 	rm $(OBJS)

all: main

program1: main.c
	gcc -ansi -g -o main main.c