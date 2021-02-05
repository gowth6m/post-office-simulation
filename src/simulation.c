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
#include "customerQueue.h"
#include "simulation.h"
#include "randGenerator.h"

/* customers related counters */
int fulfilledCustomers;
int unfulfilledCustomers;
int timedOutCustomers;
int nextId;
int totalQueueWaitTime;
/* average variables */
int avgFulfilledCust = 0;
int avgUnfulfilledCust = 0;
int avgTimedOutCust = 0;
int avgTimeleft = 0;
int avgQueueWaitTime = 0;

/* Function to add random number of customers to the queue */
void addCustomers(Queue *queue, int maxQueLen, int maxNewCustomers, int minNewCustomers, int maxServeTime, int minServeTime, int maxWaitingTolerance,
    int minWaitingTolerance, int distributionType, int meanForNewCustomers, int standardDeviationForNewCustomers, int meanForServingTime, 
    int standardDeviationForServingTime, int meanForWaitingTolerance, int standardDeviationForWaitingTolerance)
{
    int i, toleranceTime, serveTime, noOfCustomers;

    if(distributionType == 1) /* for Gaussian distribution */
    {
        noOfCustomers = getGaussianRandNum(meanForNewCustomers, standardDeviationForNewCustomers);
    }
    else
    {
        noOfCustomers = getUniformRandNum(minNewCustomers, maxNewCustomers); /* getting random number of customers to add */
    }
    
    for (i = 0; i < noOfCustomers; i++)
    {
        if(distributionType == 1) /* for Gaussian distribution */
        {
            toleranceTime = getGaussianRandNum(meanForWaitingTolerance, standardDeviationForWaitingTolerance);
            serveTime = getGaussianRandNum(meanForServingTime, standardDeviationForServingTime); 
        }
        else /* for Uniform distribution */
        {
            toleranceTime = getUniformRandNum(minWaitingTolerance, maxWaitingTolerance); /* customer's tolerance to waiting */
            serveTime = getUniformRandNum(minServeTime, maxServeTime);                   /* time taken to serve the customer */
        }

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
        /* free up the service point when the time point is reached, release timer clock at that point */
        if (servicePointArr[i] == timer && timer)
        {
            servicePointArr[i] = 0; /* sets as 0, as 0 means the service point is free */
            fulfilledCustomers++;   /* the customer is served and count as fulfilled */
        }

        /* if the service point is free, the dequeue a customer and start serving them */
        if (servicePointArr[i] == 0)
        {
            /* check if there is a customer in the queue, if so then continue the loop */
            if (queueEmpty(queue))
                continue;

            /* calculating time when to free up the serving point*/
            int finishServingTime = timer + queue->front->timeTakenToServe;
            servicePointArr[i] = finishServingTime;
            /* add the time spent in the queue of this customer */
            totalQueueWaitTime += queue->front->timeSpentInQueue;
            /* remove the customer from queue */
            deQueue(queue);
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
void loopForManagingCustomers(int closingTime, int numServicePoints, int maxQueLen, int maxNewCustomers, int minNewCustomers, 
    int maxServeTime, int minServeTime, int maxWaitingTolerance, int minWaitingTolerance, int distributionType, int meanForNewCustomers, 
    int standardDeviationForNewCustomers, int meanForServingTime, int standardDeviationForServingTime, int meanForWaitingTolerance, 
    int standardDeviationForWaitingTolerance, int singleSim)
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

    /* This loop runs until closing time, represents the countdown clock until closing time */
    for (timer = 0; (timer < closingTime) || !queueEmpty(queue) || (timer < maxTimeInServPoint); timer++)
    {

        /*fulfilled customers leave the system, then available service points serve the first customers in the queue */
        numCurBeingServed = serveCustomer(queue, servicePointArr, numServicePoints, timer, &maxTimeInServPoint);

        /* update customer tolerance and remove if exceeded */
        timedOutCustomers += getTimedOutCustomers(queue);

        /*Adding random number of customers every time interval */
        if (timer < closingTime)
        {
            addCustomers(queue, maxQueLen, maxNewCustomers, minNewCustomers, maxServeTime, minServeTime, maxWaitingTolerance, 
                minWaitingTolerance, distributionType, meanForNewCustomers, standardDeviationForNewCustomers, meanForServingTime, 
                standardDeviationForServingTime, meanForWaitingTolerance, standardDeviationForWaitingTolerance);
        }

        /* count the time after the closing time */
        if (timer >= closingTime)
        {
            timeleft++;
        }

        /* if there is only one simulation (numSims == 1) then print the corresponding record for each time interval */
        if (singleSim)
        {
            /* marks the closing time */
            if (timer == closingTime)
            {
                printf("\n------------------------------------------\n");
                printf("\n------------------------------------------\n");
                printf("______________ CLOSING TIME ______________\n");
                printf("\n------------------------------------------\n");
            }

            printf("\n------------------------------------------\n");
            printf("\nClock time : %d\n", timer);
            printf("Number of customers currently being served: %d\n", numCurBeingServed);
            printf("Number of customers currently in the queue: %d\n", getQueueLen(queue));
            printf("Fulfilled customers: %d\n", fulfilledCustomers);
            printf("Unfulfilled customers: %d\n", unfulfilledCustomers);
            printf("Timed-out customers: %d\n", timedOutCustomers);
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
void runSimulation(int numSims, int maxQueLen, int numServicePoints, int closingTime, int maxNewCustomers, int minNewCustomers, 
    int maxServeTime, int minServeTime, int maxWaitingTolerance, int minWaitingTolerance, int distributionType, int meanForNewCustomers, 
    int standardDeviationForNewCustomers, int meanForServingTime, int standardDeviationForServingTime, int meanForWaitingTolerance, 
    int standardDeviationForWaitingTolerance)
{
    int i;
    int singleSim = numSims == 1 ? 1 : 0; /* return 1 if numSims is 1 else return 0 */

    /* initialize the average variables */
    avgFulfilledCust = 0;
    avgUnfulfilledCust = 0;
    avgTimedOutCust = 0;
    avgTimeleft = 0;
    avgQueueWaitTime = 0;

    /* run the numSims simulations */
    for (i = 0; i < numSims; i++)
    {
        loopForManagingCustomers(closingTime, numServicePoints, maxQueLen, maxNewCustomers, minNewCustomers, maxServeTime, 
            minServeTime, maxWaitingTolerance, minWaitingTolerance, distributionType, meanForNewCustomers, standardDeviationForNewCustomers, 
            meanForServingTime, standardDeviationForServingTime, meanForWaitingTolerance, standardDeviationForWaitingTolerance, singleSim);
    }

    /* print the final results */
    printf("\n------------------------------------------\n");
    printf("\nFINAL RESULTS:\n\n");

    if (!singleSim)
        printf("Averages:\n\n");

    printf("Fulfilled customers: %.2f\n", (double)avgFulfilledCust / numSims);
    printf("Unfulfilled customers: %.2f\n", (double)avgUnfulfilledCust / numSims);
    printf("Timed-out customers: %.2f\n", (double)avgTimedOutCust / numSims);
    printf("\nTime it took from closing time until all remaining customers were served: %.2f\n", (double)avgTimeleft / numSims);
    printf("\nAverage waiting time (in the queue) for fulfilled customers: %.2f\n\n", (double)avgQueueWaitTime / avgFulfilledCust);
}