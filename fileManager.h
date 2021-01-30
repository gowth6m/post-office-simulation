/*
* File:			customerQueue.c
*
* Description:  implementation of some functions to read the input from the input file. header file
*
* Autor: 		Gowthaman Ravindrathas
*
* Date:			30.01.2021
*/

#ifndef _FILE_MANAGER_H_
#define _FILE_MANAGER_H_

/* Function to read all the parameters from the input file */
int getInfoFromInput(char *fileName, int * maxQueLen, int * numServicePoints, int * closingTime, int * maxNewCustomers, int * minNewCustomers, int * maxServeTime, int * maxWaitingTolerance);

/*Function to print the readed parameters */
void printReadedParameters(int maxQueLen, int numServicePoints, int closingTime, int maxNewCustomers, int minNewCustomers, int maxServeTime, int maxWaitingTolerance);

#endif