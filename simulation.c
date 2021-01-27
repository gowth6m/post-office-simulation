#include <stdio.h> 
#include <stdlib.h> 
#include "randGenerator.c"
#include "customerQueue.c"

int fulfilledCustomers = 0;
int unfulfilledCustomers = 0;
int timedOutCustomers = 0;

// Function to add random number of customers to the queue
void addCustomers(struct Queue* customerQueue, int timer) 
{
    // int noOfCustomers = random_number(10,20);
    int noOfCustomers = 5;

    for(int i=0; i < noOfCustomers; i++) 
    {
        int toleranceTime = random_number(1,40); // tolerance of the customer
        int serveTime = random_number(10, 20); // time taken to serve the customer
        // printf("%c %d %d\n", i, toleranceTime, serveTime); 
        // enQueue(customerQueue, i, toleranceTime, serveTime);
        enQueue(customerQueue, i, toleranceTime, 10, timer);
    }   
}


// Function that updates the time customer has waited and if it's past the customer's tolerance then removed
void customerWaitToleranceManager(struct Queue* customerQueue, int timer) 
{
    if(customerQueue->front != NULL) // ensure the queue isn't empty
    {
        customerQueue->front->timeSpentInQueue = customerQueue->front->timeAddedToQueue - timer;
        if(customerQueue->front->waitingToleranceLimit <= customerQueue->front->timeSpentInQueue) 
        {
            // remove from queue if tolerance exceeds the limit
            deQueue(customerQueue);
            timedOutCustomers++;
            unfulfilledCustomers++;
        }
    }
}


// Function to serve the customer at the service point
void serveCustomer(struct Queue* customerQueue, int servicePointArr[], int numServicePoints, int timer) 
{
    for(int i = 0; i < numServicePoints; i++) 
    {
        if(servicePointArr[i] == 0) 
        {
            printf("    Service Point Number : %d\n", i);
            if(customerQueue->front != NULL) // checking if the customer queue is not empty
            {   
                // calculating time when to free up the serving point
                int finishServingTime = timer - customerQueue->front->timeTakenToServe;
                servicePointArr[i] = finishServingTime;
                printf("        * finishing time: %d\n", finishServingTime);
                printf("        * removing customer: %d\n", customerQueue->front->key);
                deQueue(customerQueue); // remove the customer from queue
                fulfilledCustomers++;
            }
        }
        // Free up the service point when the time point is reached
        if (servicePointArr[i] == timer) // if equal to timer clock then release
        { 
            servicePointArr[i] = 0;
            unfulfilledCustomers++;
            printf(" >> SERVICE POINT IS FREEE >>\n");
        }
    }
}

// Function that does the main time loop for dealingn with customers
void loopForManagingCustomers(int closingTime, int customerSpawnInterval, struct Queue* customerQueue, int servicePointArr[], int numServicePoints) 
{
    int counter = 0;
    // This loop runs until closing time, represents the countdown clock until closing time
    for(int timer = closingTime; 0 < timer; timer--)
    {
        // update customer tolerance and remove if exceeded
        customerWaitToleranceManager(customerQueue, timer);

        printf("Clock time : %d\n", timer);
        // Serving the first customer in the customer queue
        serveCustomer(customerQueue, servicePointArr, numServicePoints, timer);

        // Adding random number of customers every interval
        if(counter == customerSpawnInterval) 
        {
            addCustomers(customerQueue, timer);
            counter = 0;    
        }
        counter++;
    }
}


void runSimulation(int maxQueueLength, int numServicePoints, int closingTime) 
{
    int servicePointArr[numServicePoints];
    // Populate the service points, where 0 means not occupied
    for (int i = 0; i < numServicePoints; i++) { servicePointArr[i] = 0;}

    // Creating the customer queue 
    struct Queue* customerQueue = createQueue();
    // queue, key, waitTolerance, serveTime, timeAdded
    enQueue(customerQueue, 0, 50, 10, closingTime);
    enQueue(customerQueue, 1, 50, 10, closingTime);
    enQueue(customerQueue, 2, 20, 20, closingTime);
    enQueue(customerQueue, 3, 50, 10, closingTime);

    loopForManagingCustomers(closingTime, 20, customerQueue, servicePointArr, numServicePoints);
    unfulfilledCustomers += customerQueue->queueLength;
    printf("Queue Length : %d\n", customerQueue->queueLength); 
    printf("Unfulfilled Customers : %d\n", unfulfilledCustomers); 
    printf("Fulfilled Customers : %d\n", fulfilledCustomers); 
    printf("Timed-out Customers : %d\n", fulfilledCustomers); 
}