/*
* File:         customerQueue.c
*
* Description:  Implementation of some functions to read the input from the input file and verify them.
*
* Autor:        gowth6m
*
* Date:         30.01.2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRING_SIZE 40

/* Function to read lines and ignore lines that starts with # */
int readParameter(FILE * fp, char * parameterName, int * parameter)
{
    char s[MAX_STRING_SIZE];
    int c, auxSize = strlen(parameterName);

    /* loop to ignore comments */
    while(1)
    {
        /* read the first char of the line */
        if((c = fgetc(fp)) == EOF)
            return -1;

        /* ignore empty lines or spaces */
        if(c == '\n' || c == '\r' || isspace(c))
        {
            continue;
        }
        /* exit loop if this line is not a comment */
        if(c != '#')
        {
            s[0] = (char) c;
            break;
        }

        /* otherwise ignore the line  */
        fscanf(fp, "%*[^\n]\n");
    }

    /* read the parameter */
    if(fscanf(fp, "%s %d", (s+1), parameter) < 2)
    {
        return -1;
    }

    /* check format */
    if(s[auxSize] != '\0' || strcmp(s, parameterName))
    {
        return -1;
    }
    return 0;
}


/* Function to read all the parameters from the input file */
int getInfoFromInput(char *fileName, int *maxQueLen, int *numServicePoints, int *closingTime, int *maxNewCustomers, int *minNewCustomers, 
    int *maxServeTime, int *minServeTime, int *maxWaitingTolerance, int *minWaitingTolerance, int *distributionType, int *meanForNewCustomers, 
    int *standardDeviationForNewCustomers, int *meanForServingTime, int *standardDeviationForServingTime, int *meanForWaitingTolerance, 
    int *standardDeviationForWaitingTolerance) 
{
    /* Pointer to the file */
    FILE *fp;
    fp = fopen (fileName, "r");
    
    if(fp == NULL){
        /* failed opening file */
        return -3;
    }

    /* 
        ERROR MEANING
        -1: wrong input file format
        -2: parameters in input file must be positive integers
        -3: failed opening input file
        -4: max value of limits for uniform distribution lower than min value
        -5: max queue length can't be less than -1. set as -1 only for queue with no limit
        -6: standard deviation can't be larger than mean
        -7: distributionType must be either 0 or 1 where 0 for uniform & 1 for gaussian
        -8: standard deviation can't be negative
    */

    /* read the maxQueLen parameter */
    if(readParameter(fp, "maxQueueLength", maxQueLen) == -1)
    {
        return -1;
    }

    if(*maxQueLen <= -2)
    {
        return -5;
    }

    /* read the numServicePoints parameter */
    if(readParameter(fp, "numServicePoints", numServicePoints) == -1)
    {
        return -1;
    }

    if(*numServicePoints <= 0)
    {
        return -2;
    }
    
    /* read the closingTime parameter */
    if(readParameter(fp, "closingTime", closingTime) == -1)
    {
        return -1;
    }

    if(*closingTime <= 0)
    {
        return -2;
    }

    /* read the distributionType parameter */
    if(readParameter(fp, "distributionType", distributionType) == -1)
    {
        return -1;
    }

    if(*distributionType > 1 || *distributionType < 0)
    {
        return -7;
    }

    /* read the maxNewCustomers parameter */
    if(readParameter(fp, "maxNewCustomers", maxNewCustomers) == -1)
    {
        return -1;
    }

    if(*maxNewCustomers < 0)
    {
        return -2;
    }

    /* read the minNewCustomers parameter */
    if(readParameter(fp, "minNewCustomers", minNewCustomers) == -1)
    {
        return -1;
    }

    if(*minNewCustomers < 0)
    {
        return -2;
    }

    if(*maxNewCustomers < *minNewCustomers)
    {
        return -4;
    }

    /* read the maxServeTime parameter */
    if(readParameter(fp, "maxServeTime", maxServeTime) == -1)
    {
        return -1;
    }

    if(*maxServeTime <= 0)
    {
        return -2;
    }

    /* read the minServeTime parameter */
    if(readParameter(fp, "minServeTime", minServeTime) == -1)
    {
        return -1;
    }

    if(*minServeTime <= 0)
    {
        return -2;
    }

    if(*maxServeTime < *minServeTime)
    {
        return -4;
    }

    /* read the maxWaitingTolerance parameter */
    if(readParameter(fp, "maxWaitingTolerance", maxWaitingTolerance) == -1)
    {
        return -1;
    }

    if(*maxWaitingTolerance <= 0)
    {
        return -2;
    }

    /* read the maxServeTime parameter */
    if(readParameter(fp, "minWaitingTolerance", minWaitingTolerance) == -1)
    {
        return -1;
    }

    if(*minWaitingTolerance <= 0)
    {
        return -2;
    }

    if(*maxWaitingTolerance < *minWaitingTolerance)
    {
        return -4;
    }

    /* read the meanForNewCustomers parameter */
    if(readParameter(fp, "meanForNewCustomers", meanForNewCustomers) == -1)
    {
        return -1;
    }

    /* read the standardDeviationForNewCustomers parameter */
    if(readParameter(fp, "standardDeviationForNewCustomers", standardDeviationForNewCustomers) == -1)
    {
        return -1;
    }

    if(*standardDeviationForNewCustomers > *meanForNewCustomers)
    {
        return -6;
    }

    if(*standardDeviationForNewCustomers < 0)
    {
        return -8;
    }

    /* read the meanForServingTime parameter */
    if(readParameter(fp, "meanForServingTime", meanForServingTime) == -1)
    {
        return -1;
    }

    /* read the standardDeviationForServingTime parameter */
    if(readParameter(fp, "standardDeviationForServingTime", standardDeviationForServingTime) == -1)
    {
        return -1;
    }

    if(*standardDeviationForServingTime > *meanForServingTime)
    {
        return -6;
    }

    if(*standardDeviationForServingTime < 0)
    {
        return -8;
    }


    /* read the meanForWaitingTolerance parameter */
    if(readParameter(fp, "meanForWaitingTolerance", meanForWaitingTolerance) == -1)
    {
        return -1;
    }

    /* read the standardDeviationForWaitingTolerance parameter */
    if(readParameter(fp, "standardDeviationForWaitingTolerance", standardDeviationForWaitingTolerance) == -1)
    {
        return -1;
    }

    if(*standardDeviationForWaitingTolerance > *meanForWaitingTolerance)
    {
        return -6;
    }

    if(*standardDeviationForWaitingTolerance < 0)
    {
        return -8;
    }

    fclose(fp);
    return 0;
}

/* Function to print the read parameters */
void printReadParameters(int maxQueLen, int numServicePoints, int closingTime, int maxNewCustomers, int minNewCustomers, int maxServeTime,
    int minServeTime, int maxWaitingTolerance, int minWaitingTolerance, int distributionType, int meanForNewCustomers, int standardDeviationForNewCustomers, 
    int meanForServingTime, int standardDeviationForServingTime, int meanForWaitingTolerance, int standardDeviationForWaitingTolerance)
{   
    /* Printing for Uniform distribution */
    if(distributionType == 0)
    {
        printf("\nRead parameters:\n\n");
        printf("maxQueueLength %d\n", maxQueLen);
        printf("numServicePoints %d\n", numServicePoints);  
        printf("closingTime %d\n", closingTime);
        printf("distributionType %d (Uniform distribution)\n", distributionType);
        printf("\n");
        printf("maxNewCustomers %d\n", maxNewCustomers);
        printf("minNewCustomers %d\n", minNewCustomers);
        printf("maxServeTime %d\n", maxServeTime);
        printf("minServeTime %d\n", minServeTime);
        printf("maxWaitingTolerance %d\n", maxWaitingTolerance);
        printf("minWaitingTolerance %d\n", minWaitingTolerance);
    }
    /* Printing for Gaussian distribution */
    if(distributionType == 1)
    {
        printf("\nRead parameters:\n\n");
        printf("maxQueueLength %d\n", maxQueLen);
        printf("numServicePoints %d\n", numServicePoints);  
        printf("closingTime %d\n", closingTime);
        printf("distributionType %d (Gaussian distribution)\n", distributionType);
        printf("\n");
        printf("meanForNewCustomers %d\n", meanForNewCustomers);
        printf("standardDeviationForNewCustomers %d\n", standardDeviationForNewCustomers);
        printf("meanForServingTime %d\n", meanForServingTime);
        printf("standardDeviationForServingTime %d\n", standardDeviationForServingTime);
        printf("meanForWaitingTolerance %d\n", meanForWaitingTolerance);
        printf("standardDeviationForWaitingTolerance %d\n", standardDeviationForWaitingTolerance);
    }
}
