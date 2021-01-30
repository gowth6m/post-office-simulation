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


/* customers related counters */
int fulfilledCustomers;
int unfulfilledCustomers;
int timedOutCustomers;
int nextId;
int totalQueueWaitTime;
/* average variables */
int avgFulfilledCust;
int avgUnfulfilledCust;
int avgTimedOutCust;
int avgTimeleft;
int avgQueueWaitTime;

/* Function to swap two integer variables */
void swap(int * a, int * b){
    (*a)=(*a)+(*b);    
    (*b)=(*a)-(*b);    
    (*a)=(*a)-(*b);   
}

/* Function that returns a random integer 
   with uniform distribution in the given range */
int random_integer(int l, int r){
    if(l > r) swap(&l, &r);
    return rand()%(r-l+1) + l;
}


/* Function to add random number of customers to the queue */
void addCustomers(Queue* queue, int maxQueLen, int mxNewCustomers, int mnNewCustomers, int mxServTime, int mxWaitingTolerance) 
{
    
    int i, toleranceTime, serveTime;
    int noOfCustomers = random_integer(mnNewCustomers, mxNewCustomers); /* number of new customers to add */

    for(i=0; i < noOfCustomers; i++) 
    {
        toleranceTime = random_integer(1,mxWaitingTolerance); /* tolerance of the customer */
        serveTime = random_integer(1, mxServTime); /* time taken to serve the customer */
        
        /* 
            if there is space in the queue for the new customer, 
            then enqueue the new customer, otherwise it will be
            a unfulfilled customer.
        */
        if(queueGetLength(queue) < maxQueLen || maxQueLen==-1)
        {
            if(enQueue(queue, nextId++, toleranceTime, serveTime) == -1)
            {
                printf("Error in function enQueue: No memory available.\n");
                exit(-1);
            }
        }
        else /* there is no space for this new customer in the queue */
        {
            unfulfilledCustomers++; /* then is counted as unfulfilled */
        }

    }

}


/*Function that updates the time customer has waited and if it's past the customer's tolerance then removed*/
void customerWaitToleranceManager(Queue* queue) 
{
    timedOutCustomers += getTimedOutCustomers(queue);
    
} 


/*
    Function to serve the customer at the service point,
    it returns the number of service points serving a customer.
*/
int serveCustomer(Queue* queue, int servicePointArr[], int numServicePoints, int timer, int * maxTimeInServPoint) 
{
    int i, curServCust = 0;

    /* iterate over the service points and do the corresponding simulations */
    for(i = 0; i < numServicePoints; i++) 
    {
        /*Free up the service point when the time point is reached*/
        if(servicePointArr[i] == timer && timer) /* if equal to timer clock then release */
        { 
            servicePointArr[i] = 0;
            fulfilledCustomers++; /* the customer is served and count as fulfilled */
        }

        /* if the service point is free, the dequeue a customer and start serving them*/
        if(servicePointArr[i] == 0) 
        {

            /* Check if there is a customer in the queue */
            if(queueEmpty(queue))
                continue;

            /*calculating time when to free up the serving point*/
            int finishServingTime = timer + queue->front->timeTakenToServe;
            servicePointArr[i] = finishServingTime;
            /* add the time spent in the queue of this customer */
            totalQueueWaitTime += queue->front->timeSpentInQueue;
            deQueue(queue);  /*remove the customer from queue*/
        }

        /* count the number of service points serving a customer */
        if(servicePointArr[i] > 0)
            curServCust++;

        /* calculate the maximum value in the array */
        if(servicePointArr[i] > (* maxTimeInServPoint))
            (* maxTimeInServPoint) = servicePointArr[i];

    }

    /* return the number of service points serving a customer */
    return curServCust;

}

/* Function that does the main time loop for dealingn with customers in one simulation */
void loopForManagingCustomers(int closingTime, int numServicePoints, int maxQueLen, int mxNewCustomers,
                                    int mnNewCustomers, int mxServTime, int mxWaitingTolerance, int verb) 
{

    int i, timer, curServCust, maxTimeInServPoint = 0, timeleft = 0;
    /* Array to simulate the service points */
    int servicePointArr[numServicePoints];

    /* Creating the customer queue */
    Queue* queue = createQueue();

    /* Initialize the customers related counters */
    fulfilledCustomers = 0;
    unfulfilledCustomers = 0;
    timedOutCustomers = 0;
    nextId = 0;
    totalQueueWaitTime = 0;

    /* Initialize the service points, where 0 means not occupied */
    for (i = 0; i < numServicePoints; i++) servicePointArr[i] = 0;

    /*This loop runs until closing time, represents the countdown clock until closing time*/
    for(timer = 0; (timer < closingTime) || !queueEmpty(queue) || (timer < maxTimeInServPoint); timer++)
    {

        /*fulfilled customers leave the system, then
        available service points serve the first customers in the queue*/
        curServCust = serveCustomer(queue, servicePointArr, numServicePoints, timer, & maxTimeInServPoint);

        /*update customer tolerance and remove if exceeded*/
        customerWaitToleranceManager(queue);

        /*Adding random number of customers every time interval*/
        if(timer < closingTime)
        {
            addCustomers(queue, maxQueLen, mxNewCustomers, mnNewCustomers, mxServTime, mxWaitingTolerance);
        }

        /* count the time after the closing time */
        if(timer >= closingTime)
        {
            timeleft++;
        }

        /*  
            If there is only one simulation (numSims == 1)
            then print the corresponding record for 
            each time interval
        */  
        if(verb)
        {
            /* mark the closing time */
            if(timer == closingTime){
                printf("\n-------------------------------\n");
                printf("\n-------------------------------\n");
                printf("_________ CLOSING TIME ________\n");
                printf("\n-------------------------------\n");
            }

            printf("\n-------------------------------\n");
            printf("\nClock time : %d\n", timer);
            printf("Number of customers currently being served: %d\n", curServCust);
            printf("Number of customers currently in the queue: %d\n", queueGetLength(queue));
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
void runSimulation(int numSims, int  maxQueLen, int numServicePoints, int closingTime, 
         int mxNewCustomers, int mnNewCustomers, int mxServTime, int mxWaitingTolerance)
{
    int i;
    int verb = (numSims==1?1:0); /* verbose mode if there is only one simulation */

    /* Initialize the average variables */
    avgFulfilledCust = 0;
    avgUnfulfilledCust = 0;
    avgTimedOutCust = 0;
    avgTimeleft = 0;
    avgQueueWaitTime = 0;
    
    
    /* Run the numSims simulations */
    for(i = 0; i < numSims; i++)
    {
        loopForManagingCustomers(closingTime, numServicePoints, maxQueLen,
            mxNewCustomers, mnNewCustomers, mxServTime, mxWaitingTolerance, verb);
    }

    /* Print the final results */
    printf("\n-------------------------------\n");
    printf("\nFINAL RESULTS:\n\n");
    
    if(!verb)
        printf("Averages:\n\n");

    printf("Fulfilled customers: %.2f\n", (double) avgFulfilledCust / numSims);
    printf("Unfulfilled customers: %.2f\n", (double) avgUnfulfilledCust / numSims);
    printf("Timed-out customers: %.2f\n", (double) avgTimedOutCust / numSims);
    printf("\nTime it took from closing time until all remaining customers were served: %.2f\n",
                (double) avgTimeleft / numSims);
    printf("\nAverage waiting time (in the queue) for fulfilled customers: %.2f\n\n", (double) avgQueueWaitTime / avgFulfilledCust);

}