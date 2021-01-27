#include <stdio.h> 
#include <stdlib.h> 
#include "randGenerator.c"
#include "customerQueue.c"

int unfulfilledCustomer = 0;

// Function to add random number of customers to the queue
void addCustomers(struct Queue* customerQueue) {
    int noOfCustomers = random_number(10,20);

    for(int i=0; i < 1; i++) {
        int toleranceTime = random_number(1,40); // tolerance of the customer
        int serveTime = random_number(10, 20); // time taken to serve the customer
        // printf("%c %d %d\n", i, toleranceTime, serveTime); 
        // enQueue(customerQueue, i, toleranceTime, serveTime);
        enQueue(customerQueue, i, toleranceTime, 10);
    }   
}


// Function to serve the customer at the service point
void servingCustomer(struct Queue* customerQueue, int servicePointArr[], int numServicePoints, int timer) {
    for(int i = 0; i < numServicePoints; i++) {
        if(servicePointArr[i] == 0) {
            printf("    Service Point Number : %d\n", i);
            // calculating time when to free up the serving point
            // int currentCustomerServeTime = customerQueue->front->timeTakenToServe;
            int finishServingTime = timer - customerQueue->front->timeTakenToServe;
            servicePointArr[i] = finishServingTime;
            // remove the customer from queue
            printf("        * finishing time: %d\n", finishServingTime);
            printf("        * removing customer: %d\n", customerQueue->front->key);
            deQueue(customerQueue);
        }
        if (servicePointArr[i] == timer) {  // if equal to timer clock then release
            servicePointArr[i] = 0;
            printf(" >>SERVICE POINT IS FREEE>>\n");
        }
    }
}


void timeLoopForAddingCustomers(int closingTime, int customerSpawnInterval, struct Queue* customerQueue, int servicePointArr[], int numServicePoints) {
    int counter = 0;
    for(int timer = closingTime; 0 < timer; timer--){
        printf("Clock time : %d\n", timer);
        servingCustomer(customerQueue, servicePointArr, numServicePoints, timer);

        if(counter == customerSpawnInterval) {
            // Adding random number of customers every interval
            printf(">>>>>>>> adding customers to queue\n");
            addCustomers(customerQueue);
            printf(">>>>>>>>>>>>>>>>>>>>>>>> length of queue: %d\n", customerQueue->queueLength);
            counter = 0;    
        }
        counter++;
    }
}


void runSimulation(int maxQueueLength, int numServicePoints, int closingTime) {
    int servicePointArr[numServicePoints];
    // Populate the service points, where 0 means not occupied
    for (int i = 0; i < numServicePoints; i++) { servicePointArr[i] = 0;}

    // Creating the customer queue 
    struct Queue* customerQueue = createQueue();
    enQueue(customerQueue, 0, 10, 10);
    enQueue(customerQueue, 1, 10, 10);
    enQueue(customerQueue, 2, 10, 10);
    enQueue(customerQueue, 3, 10, 10);

    timeLoopForAddingCustomers(closingTime, 30, customerQueue, servicePointArr, numServicePoints);
    printf("Queue Length : %d\n", customerQueue->queueLength); 
}