// C Family : CA1 by Gowthaman Ravindrathas
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "simulation.c"
#include "fileManager.c"


bool inputCheck(int argc, char const *argv[]) {
    for (int i = 0; i<argc; i++) {
        printf("%d \t %s \n", i, argv[i]);
    }
    
    // Checks if valid amout of args given
    if(argc != 4) {
        printf("Error, invalid amount of arguments.");
    }
    return true;
}


int main(int argc, char const *argv[])
{
    runSimulation(10, 1, 80);

    
}