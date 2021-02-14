/*
* File:			customerQueue.c
*
* Description:  Linked list based implementation of customer queue.
*
* Autor: 		gowth6m
*
* Date:			27.01.2021
*/

#include <stdlib.h>
#include "customerQueue.h"  

 
/* A utility function to create a new linked list node. */
CustomerNode* newNode(int key_, int waitTolerance, int serveTime) 
{ 
	/* allocation of memory for the new node */
    CustomerNode* temp = (CustomerNode*) malloc(sizeof(CustomerNode));
    /* verify allocation of memory */
    if(temp == NULL)
	{
    	return NULL;
    }

    /* assign initial values to the node attributes */
    temp->key = key_; 
    temp->waitingToleranceLimit = waitTolerance;
    temp->timeTakenToServe = serveTime;
    temp->timeSpentInQueue = 0;
    temp->next = NULL; 

    return temp; 
} 
  
/* A utility function to create an empty queue */
Queue* createQueue() 
{ 
    Queue* q = (Queue*) malloc(sizeof(Queue));
    /* verify allocation of memory */
    if(q == NULL)
	{
    	return NULL;
    }

    q->front = q->rear = NULL; 
    q->queueLength = 0;

    return q; 
}
  
/* The function to add a key k to q */
int enQueue(Queue* q, int k, int waitTolerance, int serveTime)
{ 
	CustomerNode* temp;	/* New customer node */

    /* create a new LL node */
    temp = newNode(k, waitTolerance, serveTime);
    /* verify allocation of memory */
    if(temp == NULL)
	{
    	/* error no memory available */
    	return -1;
    }

    /* ff queue is empty, then new node is front and rear both */
    if (queueEmpty(q)) {
        q->front = q->rear = temp;
        q->queueLength++;
        return 0; 
    } 
  
    /* add the new node at the end of queue and change rear */
    q->rear->next = temp; 
    q->rear = temp; 
    q->queueLength++;

    return 0;
} 
  
/* Function to remove front node from given queue q */
void deQueue(Queue* q) 
{ 
    /* If queue is empty, return. */
    if (queueEmpty(q)) 
	{
        return; 
	}
  
    /* store previous front and move front one node ahead */
    CustomerNode* temp = q->front; 
    q->front = q->front->next; 
  
    /* if front becomes NULL, then change rear also as NULL */
    if (q->front == NULL)
	{
        q->rear = NULL; 
	}

    q->queueLength--;

    free(temp);
}

/* Function to get the length of the queue */
int getQueueLen(Queue* q)
{
	return q->queueLength;
}

/* Function to check if the queue is empty */
int queueEmpty(Queue * q)
{
	return (q->queueLength == 0);
}

/* Function that iterate over the customers in the queue. Delete timed-out customers, otherwise increase the time spent in the queue. 
	Return the number of timed-out customers found in the queue. */
int getTimedOutCustomers(Queue * q)
{
	CustomerNode* prev = NULL;
	CustomerNode* iterator = (q->front);
	CustomerNode* temp = NULL;
	int countTimedOut = 0;

	/* iterate over the customers in the queue with this loop */
	while(iterator != NULL){

		/* if the current customer in iterator is timed-out then delete it from the queue. */
		if(iterator->timeSpentInQueue >= iterator->waitingToleranceLimit)
		{
			/* if it was the first node in the list */
			if(prev == NULL)
			{
				q->front = iterator->next;
				
				/* if it was the only node in the list */
				if(q->front == NULL)
				{
					q->rear = NULL;
				}
			}
			else
			{
				prev->next = iterator->next;
				
				/* if it was the last node in the list */
				if(prev->next == NULL)
				{
					q->rear = prev;
				}
			}

			/* save the pointer and continue the iteration and free mem */
			temp = iterator;
			iterator = iterator->next;
			free(temp);

			/* decrese the length of the queue and count the timed-out customer */
			q->queueLength--;
			countTimedOut++;
		}
		else
		{
			/* if the customer is not timed-out then increase it's timeSpentInQueue attribute and continue iterating over the list */
			iterator->timeSpentInQueue++;
			prev = iterator;
			iterator = iterator->next;
		}
	}

	/* return the number of timed-out customers found in the queue. */
	return countTimedOut;
}
