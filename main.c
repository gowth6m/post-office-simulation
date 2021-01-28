// CA
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "simulation.c"
#include "fileManager.c"

// Define settings for simulation to adjust
int minServeTime = 5;
int maxServeTime = 30;
int minToleranceTime = 20;
int maxToleranceTime = 50;
int minNoOfCustomerAdded = 10;
int maxNoOfCustomerAdded = 50;
int customerSpawnInterval = 10;


bool inputCheck(int argc, char const *argv[]) {
    for (int i = 0; i<argc; i++) {
        printf("%d \t %s \n", i, argv[i]);
    }
    
    // Checks if valid amout of args given
    if(argc != 4) {
        printf("Error, invalid amount of arguments.");
    }
    return true;
}


int main(int argc, char const *argv[])
{
    multiSimulation(1, -1, 1, 100);

}

// --------------------------------------------------------
// What happens when its near finish time and the time taken to 
// serve customer exceed fisnish time?

// On the spec it says that the customer will become timed-out customer
// does that mean just remove them?

// Do we have to worry about header files and stuff?

// --------------------------------------------------------
// TASKS TO IMPLEMENT:
// -- Implement file reader
// -- Implement file writer

// --------------------------------------------------------
// EXAMPLE OUT FOR FILE:
// 
// - PER CLOCK CYCLE:
//      * Time inverval number (im guessing this is like a clock)
//      * Number of customers currently being served (check servicePointArr 
//          - if > 0 then the point is being served - maybe forloop it)
//      * Number of people currently in the queue 
//          - use customerQueue->queueLength
//      * Numbers of fulfilled - use the global fulfilledCustomers
//      * Number of unfulfilled - use the global unfulfilledCustomers
//      * Number of timed-out customers so far - use timedOutCustomers
// 
// - Marker showing when closing time has been reached.
// - The time it takes from closing time until all remaining customers have been served.
// - The average waiting time for fulfilled customers over the whole simulation 
//      (i.e. the number of time intervals they spend in the queue).
