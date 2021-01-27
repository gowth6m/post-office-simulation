// Linked list based implementation of customer queue
#include <stdio.h> 
#include <stdlib.h>
  

// Linked list node to store a queue entry 
struct CustomerNode { 
    int key; // customerID
    int timeSpentInQueue; // time spent waiting in the queue
    int waitingToleranceLimit; // max time the customer waits before leaving queue
    int timeTakenToServe; // time it takes to serve a customer
    int timeAddedToQueue; // time at which the customer was added to the queue
    struct CustomerNode* next; // pointer to next node/customer in queue
}; 
  
// The queue, front stores the front node of LL and rear stores the last node of LL 
struct Queue { 
    int queueLength; // the lenght of the queue/amount of people in queue
    struct CustomerNode *front, *rear; // first customer and last customer of queue
}; 
 
// A utility function to create a new linked list node. 
struct CustomerNode* newNode(int k, int waitTolerance, int serveTime, int timeAdded) 
{ 
    struct CustomerNode* temp = (struct CustomerNode*)malloc(sizeof(struct CustomerNode)); 
    temp->key = k; 
    temp->waitingToleranceLimit = waitTolerance;
    temp->timeTakenToServe = serveTime;
    temp->timeAddedToQueue = timeAdded;
    temp->timeSpentInQueue = 0; // How can I increase this?
    temp->next = NULL; 
    return temp; 
} 
  
// A utility function to create an empty queue 
struct Queue* createQueue() 
{ 
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue)); 
    q->front = q->rear = NULL; 
    q->queueLength = 0;
    return q; 
}
  
// The function to add a key k to q 
void enQueue(struct Queue* q, int k, int waitTolerance, int serveTime, int timeAdded) 
{ 
    // Increase queue length
    q->queueLength++;
    // Create a new LL node 
    struct CustomerNode* temp = newNode(k, waitTolerance, serveTime, timeAdded); 
    
    // If queue is empty, then new node is front and rear both 
    if (q->rear == NULL) { 
        q->front = q->rear = temp; 
        return; 
    } 

    // Add the new node at the end of queue and change rear 
    q->rear->next = temp; 
    q->rear = temp; 
} 
  
// Function to remove a key from given queue q 
void deQueue(struct Queue* q) 
{   
    // Decrease queue length
    q->queueLength--;
    // If queue is empty, return NULL. 
    if (q->front == NULL) 
        return; 

    // Store previous front and move front one node ahead 
    struct CustomerNode* temp = q->front; 
    q->front = q->front->next; 
  
    // If front becomes NULL, then change rear also as NULL 
    if (q->front == NULL) 
        q->rear = NULL; 
  
    free(temp); // Free allocated memory for the node
}

// int main(int argc, char const *argv[])
// {
//     struct Queue* q = createQueue();
//     int a;
//     for(a=0; a < 10; a++) {
//         int wTime = random_number(1,40);
//         int sTime = random_number(50,100);
//         printf("%c %d %d\n", a, wTime, sTime); 
//         enQueue(q, a, wTime, sTime);
//     }
//     printf("\n");
//     printf("Queue Front : %d \n", q->front->key); 
//     printf("Queue Rear : %d", q->rear->key); 
//     printf("\n");
//     printf("Customer wait time : %d", q->rear->maxWaitTime); 
//     printf("\n");
//     printf("Queue Length : %d", q->queueLength); 
//     printf("\n");
//     deQueue(q);
//     printf("Queue Length : %d", q->queueLength); 
//     printf("\n");
//     deQueue(q);
//     printf("Queue Length : %d", q->queueLength); 
//     printf("\n");
//     printf("Queue Front : %d \n", q->front->key); 
//     printf("Queue Rear : %d", q->rear->key); 
//     printf("\n");
//     return 0;
// }


// A utility function to count the number of nodes in the LL
// int getCount(struct CustomerNode* node) 
// { 
//     // Base case 
//     if (node == NULL) 
//         return 0; 
  
//     // count is 1 + count of remaining list 
//     return 1 + getCount(node->next); 
// }