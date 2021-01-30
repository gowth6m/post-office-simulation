/*
* File:         customerQueue.c
*
* Description:  Post office simulation implementation.
*
* Autor:        Gowthaman Ravindrathas
*
* Date:         27.01.2021
*/

#include <stdio.h>
#include <stdlib.h>
#include "customerQueue.c"
#include "simulation.h"

// customers related counters
int fulfilledCustomers;
int unfulfilledCustomers;
int timedOutCustomers;
int nextId;
int totalQueueWaitTime;
// average variables
int avgFulfilledCust;
int avgUnfulfilledCust;
int avgTimedOutCust;
int avgTimeleft;
int avgQueueWaitTime;

/* Function to swap two integer variables */
void swap(int *a, int *b)
{
    (*a) = (*a) + (*b);
    (*b) = (*a) - (*b);
    (*a) = (*a) - (*b);
}

/* Function that returns a random integer with uniform distribution in the given range */
int random_integer(int l, int r)
{
    if (l > r)
        swap(&l, &r);
    return rand() % (r - l + 1) + l;
}

/* Function to add random number of customers to the queue */
void addCustomers(Queue *queue, int maxQueLen, int maxNewCustomers, int minNewCustomers, int maxServeTime, int maxWaitingTolerance)
{
    int i, toleranceTime, serveTime;
    int noOfCustomers = random_integer(minNewCustomers, maxNewCustomers); /* getting random number of customers to add */

    for (i = 0; i < noOfCustomers; i++)
    {
        toleranceTime = random_integer(1, maxWaitingTolerance); /* customer's tolerance to waiting */
        serveTime = random_integer(1, maxServeTime);            /* time taken to serve the customer */

        /* if there is space in the queue for the new customer, then add new customer, else it will be an unfulfilled customer. */
        if (getQueueLen(queue) < maxQueLen || maxQueLen == -1)
        {
            if (enQueue(queue, nextId++, toleranceTime, serveTime) == -1)
            {
                printf("Error in function enQueue: No memory available.\n");
                exit(-1);
            }
        }
        else
        {
            unfulfilledCustomers++;
        }
    }
}

/* Function to serve the customer at the service point, it returns the number of service points serving a customer. */
int serveCustomer(Queue *queue, int servicePointArr[], int numServicePoints, int timer, int *maxTimeInServPoint)
{
    int i, numCurBeingServed = 0;

    /* iterate over the service points and do the corresponding simulations */
    for (i = 0; i < numServicePoints; i++)
    {
        /* Free up the service point when the time point is reached, release timer clock at that point */
        if (servicePointArr[i] == timer && timer)
        {
            servicePointArr[i] = 0; /* sets as 0, since 0 means the service point is free */
            fulfilledCustomers++;   /* the customer is served and count as fulfilled */
        }

        /* if the service point is free, the dequeue a customer and start serving them */
        if (servicePointArr[i] == 0)
        {
            /* Check if there is a customer in the queue */
            if (queueEmpty(queue))
                continue;

            /*calculating time when to free up the serving point*/
            int finishServingTime = timer + queue->front->timeTakenToServe;
            servicePointArr[i] = finishServingTime;
            /* add the time spent in the queue of this customer */
            totalQueueWaitTime += queue->front->timeSpentInQueue;
            deQueue(queue); /*remove the customer from queue*/
        }

        /* count the number of service points serving a customer */
        if (servicePointArr[i] > 0)
            numCurBeingServed++;

        /* calculate the maximum value in the array */
        if (servicePointArr[i] > (*maxTimeInServPoint))
            (*maxTimeInServPoint) = servicePointArr[i];
    }

    /* return the number of service points serving a customer */
    return numCurBeingServed;
}

/* Function that does the main time loop for dealingn with customers in one simulation */
void loopForManagingCustomers(int closingTime, int numServicePoints, int maxQueLen, int maxNewCustomers, int minNewCustomers, int maxServeTime, int maxWaitingTolerance, int singleSim)
{

    int i, timer, numCurBeingServed, maxTimeInServPoint = 0, timeleft = 0;
    /* Array to simulate the service points */
    int servicePointArr[numServicePoints];

    /* Creating the customer queue */
    Queue *queue = createQueue();

    /* Initialize the customers related counters */
    fulfilledCustomers = 0;
    unfulfilledCustomers = 0;
    timedOutCustomers = 0;
    nextId = 0;
    totalQueueWaitTime = 0;

    /* Initialize the service points, where 0 means not occupied */
    for (i = 0; i < numServicePoints; i++)
        servicePointArr[i] = 0;

    // enQueue(queue, 0, 12, 10);
    // enQueue(queue, 1, 102, 10);
    // enQueue(queue, 2, 102, 10);
    // enQueue(queue, 3, 102, 10);
    // enQueue(queue, 4, 102, 10);

    /* This loop runs until closing time, represents the countdown clock until closing time */
    for (timer = 0; (timer < closingTime) || !queueEmpty(queue) || (timer < maxTimeInServPoint); timer++)
    {

        /*fulfilled customers leave the system, then
        available service points serve the first customers in the queue */
        numCurBeingServed = serveCustomer(queue, servicePointArr, numServicePoints, timer, &maxTimeInServPoint);

        /* update customer tolerance and remove if exceeded */
        timedOutCustomers += getTimedOutCustomers(queue);

        /*Adding random number of customers every time interval */
        if (timer < closingTime)
        {
            addCustomers(queue, maxQueLen, maxNewCustomers, minNewCustomers, maxServeTime, maxWaitingTolerance);
        }

        /* count the time after the closing time */
        if (timer >= closingTime)
        {
            timeleft++;
        }

        /* If there is only one simulation (numSims == 1) then print the corresponding record for each time interval */
        if (singleSim)
        {
            /* marks the closing time */
            if (timer == closingTime)
            {
                printf("\n-------------------------------\n");
                printf("\n-------------------------------\n");
                printf("_________ CLOSING TIME ________\n");
                printf("\n-------------------------------\n");
            }

            printf("\n-------------------------------\n");
            printf("\nClock time : %d\n", timer);
            printf("Number of customers currently being served: %d\n", numCurBeingServed);
            printf("Number of customers currently in the queue: %d\n", getQueueLen(queue));
            printf("Fulfilled customers (aggregate): %d\n", fulfilledCustomers);
            printf("Unfulfilled customers (aggregate): %d\n", unfulfilledCustomers);
            printf("Timed-out customers (aggregate): %d\n", timedOutCustomers);
        }
    }

    /* accumulate the values to print the final results */
    avgFulfilledCust += fulfilledCustomers;
    avgUnfulfilledCust += unfulfilledCustomers;
    avgTimedOutCust += timedOutCustomers;
    avgTimeleft += timeleft;
    avgQueueWaitTime += totalQueueWaitTime;

    /* Free the empty queue */
    free(queue);
}

/* Main function to run all the simulations (numSims) and prints the results */
void runSimulation(int numSims, int maxQueLen, int numServicePoints, int closingTime, int maxNewCustomers, int minNewCustomers, int maxServeTime, int maxWaitingTolerance)
{
    int i;
    int singleSim = numSims == 1 ? 1 : 0; /* return 1 if numSims is 1 else return 0 */

    /* Initialize the average variables */
    avgFulfilledCust = 0;
    avgUnfulfilledCust = 0;
    avgTimedOutCust = 0;
    avgTimeleft = 0;
    avgQueueWaitTime = 0;

    /* Run the numSims simulations */
    for (i = 0; i < numSims; i++)
    {
        loopForManagingCustomers(closingTime, numServicePoints, maxQueLen, maxNewCustomers, minNewCustomers, maxServeTime, maxWaitingTolerance, singleSim);
    }

    /* Print the final results */
    printf("\n-------------------------------\n");
    printf("\nFINAL RESULTS:\n\n");

    if (!singleSim)
        printf("Averages:\n\n");

    printf("Fulfilled customers: %.2f\n", (double)avgFulfilledCust / numSims);
    printf("Unfulfilled customers: %.2f\n", (double)avgUnfulfilledCust / numSims);
    printf("Timed-out customers: %.2f\n", (double)avgTimedOutCust / numSims);
    printf("\nTime it took from closing time until all remaining customers were served: %.2f\n", (double)avgTimeleft / numSims);
    printf("\nAverage waiting time (in the queue) for fulfilled customers: %.2f\n\n", (double)avgQueueWaitTime / avgFulfilledCust);
}