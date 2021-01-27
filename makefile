# the compiler: gcc for C program, define as g++ for C++
# CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
# CFLAGS  = -ansi -g 

# # the build target executable:
# TARGET = main

# all: $(TARGET)

# $(TARGET): $(TARGET).c
# 	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

# clean:
# 	$(RM) $(TARGET)

all: main

program1: main.c
	gcc -ansi -g -o main main.c
