/*
* File:			customerQueue.h
*
* Description:  Linked list based implementation of customer queue. Header file.
*
* Autor: 		gowth6m
*
* Date:			27.01.2021
*/

#ifndef __CUSTOMER_QUEUE_H
#define __CUSTOMER_QUEUE_H

/* Linked list node to store a queue entry */
typedef struct CustomerNode { 
    
    int key;                                    /* CustomerID. */
    int timeSpentInQueue; 						/* time spent waiting in the queue */
    int waitingToleranceLimit;                  /* Max time the customer waits before leaving queue. */
    int timeTakenToServe;                       /* Time it takes to serve a customer. */
    struct CustomerNode* next;                  /* Pointer to next node/customer in queue. */

} CustomerNode; 
  
/* The queue, front stores the front node of LL and rear stores the last node of LL */
typedef struct Queue {

    int queueLength;                            /* the lenght of the queue/amount of people in queue */
    CustomerNode *front, *rear;          		/* first customer and last customer of queue */

} Queue; 
 
/* A utility function to create a new linked list node. */
CustomerNode* newNode(int key_, int waitTolerance, int serveTime);
  
/* A utility function to create an empty queue */
Queue* createQueue();

/* The function to add a key k to q */
int enQueue(Queue* q, int k, int waitTolerance, int serveTime);

/* Function to remove front node from given queue q */
void deQueue(Queue* q);

/* Function to get the length of the queue */
int getQueueLen(Queue* q);

/* Function to check if the queue is empty */
int queueEmpty(Queue * q);

/* Function that iterate over the customers in the queue. Delete time-out customers, otherwise increase the time spent in the queue */
int getTimedOutCustomers(Queue * q);

#endif