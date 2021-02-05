/*
* File:			customerQueue.c
*
* Description:  Post office simulation implementation. Header file.
*
* Autor: 		Gowthaman Ravindrathas
*
* Date:			27.01.2021
*/

#ifndef __SIMULATION_H
#define __SIMULATION_H

/* Main function to run all the simulations (numSims) and prints the results */
void runSimulation(int numSims, int maxQueLen, int numServicePoints, int closingTime, int maxNewCustomers, int minNewCustomers, 
    int maxServeTime, int minServeTime, int maxWaitingTolerance, int minWaitingTolerance, int distributionType, int meanForNewCustomers, 
    int standardDeviationForNewCustomers, int meanForServingTime, int standardDeviationForServingTime, int meanForWaitingTolerance, 
    int standardDeviationForWaitingTolerance);

#endif