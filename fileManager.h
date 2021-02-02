/*
* File:			customerQueue.c
*
* Description:  Implementation of some functions to read the input from the input file. header file
*
* Autor: 		Gowthaman Ravindrathas
*
* Date:			30.01.2021
*/

#ifndef __FILE_MANAGER_H
#define __FILE_MANAGER_H

/* Function to read all the parameters from the input file */
int getInfoFromInput(char *fileName, int *maxQueLen, int *numServicePoints, int *closingTime, int *maxNewCustomers, 
    int *minNewCustomers, int *maxServeTime, int *maxWaitingTolerance, int *distributionType, int *meanForNewCustomers,
    int *standardDeviationForNewCustomers, int *meanForServingTime, int *standardDeviationForServingTime, 
    int *meanForWaitingTolerance, int *standardDeviationForWaitingTolerance);

/*Function to print the read parameters */
void printReadParameters(int maxQueLen, int numServicePoints, int closingTime, int maxNewCustomers, int minNewCustomers, int maxServeTime,
    int maxWaitingTolerance, int distributionType, int meanForNewCustomers, int standardDeviationForNewCustomers, int meanForServingTime,
    int standardDeviationForServingTime, int meanForWaitingTolerance, int standardDeviationForWaitingTolerance);

#endif