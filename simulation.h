/*
* File:			customerQueue.c
*
* Description:  Post office simulation implementation. Header file.
*
* Autor: 		Gowthaman Ravindrathas
*
* Date:			27.01.2021
*/

#ifndef _SIMULATION_H_
#define _SIMULATION_H_

/* Main function to run all the simulations (numSims) and prints the results */
void runSimulation(int numSims, int  maxQueLen, int numServicePoints, int closingTime, 
         int mxNewCustomers, int mnNewCustomers, int mxServTime, int mxWaitingTolerance);

#endif