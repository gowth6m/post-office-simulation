#include <stdio.h> 
#include <stdlib.h> 
#include "randGenerator.c"
#include "customerQueue.c"


void timeLoopForAddingCustomers(int closingTime, int interval, struct Queue customerQueue) {
    int i;
    int counter;
    for(i = 0; i < closingTime; i++){
        printf("%d\n", i);


        if(counter == interval) {
            printf("adding customers to queue\n");

            counter = 0;
        }
        counter++;
    }
}

void servingCustomer(bool servicePointArr[]) {

}


void runSimulation(int maxQueueLength, int numServicePoints, int closingTime) {
    bool servicePointArr[numServicePoints];

    // Creating the customer queue
    struct Queue* customerQueue = createQueue();
    
}