/**
* File:			main.c
*
* Description:  main function of the post office queue simulator.
*
* Autor: 		Gowthaman Ravindrathas
*
* Date:			27.01.2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "fileManager.c"
#include "simulation.c"

/* check format fo the command line args */
void verifyCommandLineFormat(int argc, char ** argv, int * numSims);


int main(int argc, char ** argv){

	int numSims, maxQueLen, numServicePoints, closingTime, err,
		mxNewCustomers, mnNewCustomers, mxServTime, mxWaitingTolerance;
	char * inputFileName;
	char * outputFileName;
	FILE * fp;

	/* Set the seed for the pseudo random numbers with uniform distribution */
	srand(time(NULL));

	/* check format fo the command line args */
	verifyCommandLineFormat(argc, argv, & numSims);

	inputFileName = argv[1];
	outputFileName = argv[3];

	/* read input parameters from the given file */
	err = getInfoFromInput(inputFileName, & maxQueLen, & numServicePoints, & closingTime, 
		& mxNewCustomers, & mnNewCustomers, & mxServTime, & mxWaitingTolerance);

	if(err == -1)
	{
		printf("Wrong format in input file.\n");
		exit(-1);
	}

	if(err == -2)
	{
		printf("Parameters in input file must be positive integers. (except mnNewCustomers could be 0)\n");
		exit(-1);
	}

	if(err == -3)
	{
		printf("Failed opening input file.\n");
		exit(-1);
	}

	/* redirect output to show results to the given output file */
	if(freopen(outputFileName, "w", stdout) == NULL)
	{
		printf("Failed opening file %s\n", outputFileName);
		exit(-1);
	}

	/* print the readed parameters */
	printReadedParameters(maxQueLen,  numServicePoints,  closingTime, 
		 mxNewCustomers,  mnNewCustomers,  mxServTime,  mxWaitingTolerance);

	/* make numSims simulations */
	runSimulation(numSims, maxQueLen,  numServicePoints,  closingTime, 
		 mxNewCustomers,  mnNewCustomers,  mxServTime,  mxWaitingTolerance);

	return 0;
}

/* check format fo the command line args */
void verifyCommandLineFormat(int argc, char ** argv, int * numSims)
{

	/* verify format */
	if(argc != 4)
	{
		printf("Invalid format. The correcct format is:\n./simQ <fileIn> <numSims> <fileOut>\n");
		exit(-1);
	}

	/* extract number of simulations */
	(*numSims) = atoi(argv[2]);

	/* verify format */
	if((*numSims) == 0 && strcmp(argv[2],"0"))
	{
		printf("Invalid format. The number of simulations must be a positive integer.\n");
		exit(-1);
	}
	else if((*numSims) == 0)
	{
		printf("Invalid format. The correcct format is:\n./simQ <fileIn> <numSims> <fileOut>\n");
		exit(-1);
	}

}

