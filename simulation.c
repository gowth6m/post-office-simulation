#include <stdio.h> 
#include <stdlib.h> 
#include "randGenerator.c"
#include "customerQueue.c"
#include "fileManager.c"

// Declare settings for simulation to adjust
extern int minServeTime;
extern int maxServeTime;
extern int minToleranceTime;
extern int maxToleranceTime;
extern int minNoOfCustomerAdded;
extern int maxNoOfCustomerAdded;
extern int customerSpawnInterval;

// Pointer to write file
FILE *fpWrite;

// Check if multi-sim
bool isMultiSim = false;

// Globals for tracking
int fulfilledCustomers = 0;
int unfulfilledCustomers = 0;
int timedOutCustomers = 0;
int totalTimeSpentInQueAllFulfillCus = 0;

// Function to add random number of customers to the queue
void addCustomers(struct Queue* queue, int timer, int maxQueLen) 
{
    // Checking if the queue hasn't reached its limit and if max length is -1 then it has no limit
    if((queue->length <= maxQueLen) || (maxQueLen == -1))
    {
        int noOfCustomers = random_number(minNoOfCustomerAdded, maxNoOfCustomerAdded);
        for(int i=0; i < noOfCustomers; i++) 
        {
            int toleranceTime = random_number(minToleranceTime, maxToleranceTime); // tolerance of the customer
            int serveTime = random_number(minServeTime, maxServeTime); // time taken to serve the customer
            enQueue(queue, i, toleranceTime, serveTime, timer);
        }
    }   
}

// Function that updates the time customer has waited and if it's past the customer's tolerance then removed
void customerWaitToleranceManager(struct Queue* queue, int timer) 
{
    if(queue->front != NULL) // ensure the queue isn't empty to avoid seg error
    {
        queue->front->timeSpentInQueue = queue->front->timeAddedToQueue - timer;
        if(queue->front->waitingToleranceLimit <= queue->front->timeSpentInQueue) 
        {
            timedOutCustomers++;
            unfulfilledCustomers++;
            // remove from queue if tolerance exceeds the limit
            deQueue(queue);
            
        }
    }
}

// Function to serve the customer at the service point
void serveCustomer(struct Queue* queue, int servicePointArr[], int numServicePoints, int timer) 
{
    for(int i = 0; i < numServicePoints; i++) 
    {
        if(servicePointArr[i] == 0) 
        {
            printf("    Service Point Number : %d\n", i);
            if(queue->front != NULL) // checking if the customer queue is not empty to avoid seg error
            {   
                // calculating time when to free up the serving point
                int finishServingTime = timer - queue->front->timeTakenToServe;
                servicePointArr[i] = finishServingTime;
                printf("        * serving customer: %d\n", queue->front->key);
                printf("        * finishing time for customer: %d\n", finishServingTime);
                printf("        * time waited in queue : %d\n", queue->front->timeSpentInQueue);
                // to calculate the average later
                totalTimeSpentInQueAllFulfillCus += queue->front->timeSpentInQueue;
                deQueue(queue); // remove the customer from queue
                fulfilledCustomers++;
            }
        }
        // Free up the service point when the time point is reached
        if (servicePointArr[i] == timer) // if equal to timer clock then release
        { 
            servicePointArr[i] = 0;
            printf(" >> SERVICE POINT IS FREEE >>\n");
        }
    }
}

// Function that does the main time loop for dealingn with customers
void loopForManagingCustomers(int closingTime, int customerSpawnInterval, struct Queue* queue, int servicePointArr[], int numServicePoints, int maxQueLen) 
{
    int counter = 0;
    // This loop runs until closing time, represents the countdown clock until closing time
    for(int timer = closingTime; 0 < timer; timer--)
    {
        // update customer tolerance and remove if exceeded
        customerWaitToleranceManager(queue, timer);

        printf("CLOCK : %d\n", timer);
        if(isMultiSim == false) 
        { 
            writeToFile("CLOCK: ", timer, fpWrite); 
            // writeToFile("   Number of customer being served: ", timer, fpWrite);
            writeToFile("   Number of people in queue: ", queue->length, fpWrite);
            writeToFile("   Number of fulfilled customers: ", fulfilledCustomers, fpWrite);
            writeToFile("   Number of unfulfilled customers: ", unfulfilledCustomers, fpWrite);
            writeToFile("   Number of timed-out customers: ", timedOutCustomers, fpWrite);
        }
        // Serving the first customer in the customer queue
        serveCustomer(queue, servicePointArr, numServicePoints, timer);

        // Adding random number of customers every interval
        if(counter == customerSpawnInterval) 
        {
            addCustomers(queue, timer, maxQueLen);
            counter = 0;    
        }
        counter++;
    }
}

// Function to run one simulation of the post office system
void simulation(int maxQueLen, int numServicePoints, int closingTime) 
{
    int servicePointArr[numServicePoints];

    // Populate the service points, where 0 means not occupied
    for (int i = 0; i < numServicePoints; i++) { servicePointArr[i] = 0;}

    // Creating the customer queue 
    struct Queue* queue = createQueue();
    // queue, key, waitTolerance, serveTime, timeAdded
    enQueue(queue, 0, 60, 10, closingTime);
    enQueue(queue, 1, 60, 10, closingTime);
    enQueue(queue, 2, 2, 20, closingTime);
    enQueue(queue, 3, 60, 10, closingTime);

    loopForManagingCustomers(closingTime, customerSpawnInterval, queue, servicePointArr, numServicePoints, maxQueLen);
    unfulfilledCustomers += queue->length;
}

// Function that runs multiple simulations
void multiSimulation(int numSim, int maxQueLen, int numServicePoints, int closingTime) 
{
    if(numSim > 1)
    {
        isMultiSim = true;

        for(int i = 0; i < numSim; i++)
        {
        simulation(maxQueLen, numServicePoints, closingTime);
        }

        // Calculating average before finding averageFulfilled in order to find average
        int averageTimeSpentInQueForFulfilledCus = totalTimeSpentInQueAllFulfillCus/fulfilledCustomers;
        unfulfilledCustomers = unfulfilledCustomers/numSim;
        fulfilledCustomers = fulfilledCustomers/numSim;
        timedOutCustomers = timedOutCustomers/numSim;
        printf("---- STATS (Multiple simulation run) ---\n");
        printf("Average time spent in queue for fulfilled : %d\n", averageTimeSpentInQueForFulfilledCus); 
        printf("Unfulfilled Customers : %d\n", unfulfilledCustomers); 
        printf("Fulfilled Customers : %d\n", fulfilledCustomers); 
        printf("Timed-out Customers : %d\n", timedOutCustomers); 
        writeToFile(">>>> MULTI-SIM STATS >>>: ", 0, fpWrite);
        writeToFile("List of parameter read in: goes here", 0, fpWrite);
        writeToFile("   Average number of fulfilled customers: ", fulfilledCustomers, fpWrite);
        writeToFile("   Average number of unfulfilled customers: ", unfulfilledCustomers, fpWrite);
        writeToFile("   Average number of timed-out customers: ", timedOutCustomers, fpWrite);
        writeToFile("   Average waiting time for fulffilled customer: ", averageTimeSpentInQueForFulfilledCus, fpWrite);
    }
    else 
    {   
        for(int i = 0; i < numSim; i++)
        {
        simulation(maxQueLen, numServicePoints, closingTime);
        }

        // Calculating average
        int averageTimeSpentInQueForFulfilledCus = totalTimeSpentInQueAllFulfillCus/fulfilledCustomers;
        writeToFile(">>>> CLOSING TIME REACHED >>>: ", 0, fpWrite);
        writeToFile("   Average waiting time for fulffilled customer: ", averageTimeSpentInQueForFulfilledCus, fpWrite);
        printf("---- STATS (One sim run) ---\n");
        printf("Average time spent in queue for fulfilled : %d\n", averageTimeSpentInQueForFulfilledCus); 
        printf("Unfulfilled Customers : %d\n", unfulfilledCustomers); 
        printf("Fulfilled Customers : %d\n", fulfilledCustomers); 
        printf("Timed-out Customers : %d\n", timedOutCustomers); 
    }
}

void startSimulation(char *fileName)
{
    fpWrite = fopen(fileName, "w+");
    // Simulation code goes in here
    multiSimulation(5, -1, 1, 100);
    fclose(fpWrite);
}