// C Family : CA1
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
// #include "customerQueue.c"
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

// int main(int argc, char const *argv[])
// {
    // checking if valid amount of input in args (4)
    // inputCheck(argc, argv);
    // int noOfSimulationRepeats = atoi(argv[2]);  // number of simulation repeats
    // printf("Testing: %d\n",noOfSimulationRepeats);
    // struct Queue* q = createQueue();
    // int a;
    // for(a=0; a < 10; a++) {
    //     printf("%c",a);
    //     enQueue(q, a);
    // }
    // printf("Queue Front : %d \n", q->front->key); 
    // printf("Queue Rear : %d", q->rear->key); 
    // ====================================
    // char test[15] = "test_input.txt";
    // getInfoFromInput(argv[1]);
    // printf("Min : 1 Max : 40 == %d\n", random_number(1,40));
    // printf("Min : 100 Max : 1000 == %d\n",random_number(100,1000));
//     return 0;
// }

int main(int argc, char const *argv[])
{

}
