/**
* File:			main.c
*
* Description:  Main function of the post office simulator.
*
* Autor: 		Gowthaman Ravindrathas
*
* Date:			27.01.2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include "fileManager.h"
#include "simulation.h"

/* Check format fo the command line args - function prototype */
void verifyCommandLineFormat(int argc, char **argv, int *numSims);

/* Function that takes in error type and outputs the error to stderr - function prototype */
void errChecker(int err);

/* Main function */
int main(int argc, char ** argv)
{
	int numSims, maxQueLen, numServicePoints, closingTime, err, maxNewCustomers, minNewCustomers, maxServeTime, minServeTime, 
		maxWaitingTolerance, minWaitingTolerance, distributionType, meanForNewCustomers, standardDeviationForNewCustomers, 
		meanForServingTime, standardDeviationForServingTime, meanForWaitingTolerance, standardDeviationForWaitingTolerance;

	char *inputFileName;
	char *outputFileName;
	FILE *fp;

	/* set the seed for the pseudo random numbers with uniform distribution */
	srand(time(NULL));

	/* check format fo the command line args */
	verifyCommandLineFormat(argc, argv, &numSims);

	inputFileName = argv[1];
	outputFileName = argv[3];

	/* read input parameters from the given file */
	err = getInfoFromInput(inputFileName, &maxQueLen, &numServicePoints, &closingTime, &maxNewCustomers, &minNewCustomers, 
		&maxServeTime, &minServeTime, &maxWaitingTolerance, &minWaitingTolerance, &distributionType, &meanForNewCustomers, 
		&standardDeviationForNewCustomers, &meanForServingTime, &standardDeviationForServingTime, &meanForWaitingTolerance, 
		&standardDeviationForWaitingTolerance);
	
	/* taking in error number and halt program if errors */	
	errChecker(err);

	/* redirect output to show results to the given output file */
	if(freopen(outputFileName, "w", stdout) == NULL)
	{
		fprintf(stderr, "Failed opening file: %s, error %d: %s %s\n", outputFileName, errno, strerror(errno));
		exit(-1);
	}

	/* print the readed parameters */
	printReadParameters(maxQueLen,  numServicePoints,  closingTime, maxNewCustomers,  minNewCustomers,  maxServeTime, minServeTime,
		maxWaitingTolerance, minWaitingTolerance, distributionType, meanForNewCustomers, standardDeviationForNewCustomers, meanForServingTime, 
		standardDeviationForServingTime, meanForWaitingTolerance, standardDeviationForWaitingTolerance);

	/* make numSims simulations */
	runSimulation(numSims, maxQueLen,  numServicePoints,  closingTime, maxNewCustomers,  minNewCustomers,  maxServeTime, minServeTime, 
		maxWaitingTolerance, minWaitingTolerance, distributionType, meanForNewCustomers, standardDeviationForNewCustomers, meanForServingTime, 
		standardDeviationForServingTime, meanForWaitingTolerance, standardDeviationForWaitingTolerance);

	return EXIT_SUCCESS;
}

/* Check format fo the command line args */
void verifyCommandLineFormat(int argc, char **argv, int *numSims)
{

	/* verify format */
	if(argc != 4)
	{
		fprintf(stderr, "Invalid format. The correcct format is:\n./simQ <fileIn> <numSims> <fileOut>\n");
		exit(-1);
	}

	/* extract number of simulations */
	(*numSims) = atoi(argv[2]);

	/* verify format */
	if((*numSims) == 0 && strcmp(argv[2],"0"))
	{
		fprintf(stderr, "Invalid format. The number of simulations must be a positive integer.\n");
		exit(-1);
	}
	else if((*numSims) == 0)
	{
		fprintf(stderr, "Invalid format. The correcct format is:\n./simQ <fileIn> <numSims> <fileOut>\n");
		exit(-1);
	}
}

/* Function that takes in error type and outputs the error to stderr */
void errChecker(int err)
{
	if(err == -1)	
	{
		fprintf(stderr, "Wrong format in input file.\n");
		exit(1);
	}

	if(err == -2)
	{
		fprintf(stderr, "Parameters in input file must be positive integers. (except minNewCustomers could be 0)\n");
		exit(1);
	}

	if(err == -3)
	{
		fprintf(stderr, "Failed opening input file, error %d: %s\n", errno, strerror(errno));
		exit(1);
	}

	if(err == -4)
	{
		fprintf(stderr, "Max value of limits for uniform distribution lower than min value.\n");
		exit(1);
	}

	if(err == -5)
	{
		fprintf(stderr, "Max queue length can't be less than -1. Set as -1 only for queue with no limit.\n");
		exit(1);
	}

	if(err == -6)
	{
		fprintf(stderr, "Standard deviation can't be larger than mean.\n");
		exit(1);
	}

	if(err == -7)
	{
		fprintf(stderr, "DistributionType must be either 0 or 1. 0 for uniform & 1 for gaussian.\n");
		exit(1);
	}
}