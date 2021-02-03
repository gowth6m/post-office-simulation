/*
* File:         customerQueue.c
*
* Description:  Implementation of some functions to read the input from the input file.
*
* Autor:        Gowthaman Ravindrathas
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

        /* otherwise ignore this line  */
        fscanf(fp, "%*[^\n]\n");
    }

    /* read the parameter*/
    if(fscanf(fp, "%s %d", (s+1), parameter) < 2)
    {
        return -1;
    }

    /* Check format */
    if(s[auxSize] != '\0' || strcmp(s, parameterName))
    {
        return -1;
    }
    return 0;
}


/* Function to read all the parameters from the input file */
int getInfoFromInput(char *fileName, int *maxQueLen, int *numServicePoints, int *closingTime, int *maxNewCustomers, int *minNewCustomers, 
    int *maxServeTime, int *maxWaitingTolerance, int *distributionType, int *meanForNewCustomers, int *standardDeviationForNewCustomers, 
    int *meanForServingTime, int *standardDeviationForServingTime, int *meanForWaitingTolerance, int *standardDeviationForWaitingTolerance) 
{
    /* Pointer to the file */
    FILE *fp;
    /* Opening a file in r mode */
    fp = fopen (fileName, "r");
    
    if(fp == NULL){
        /* failed opening file */
        return -3;
    }

    /* read the maxQueLen parameter */
    if(readParameter(fp, "maxQueueLength", maxQueLen) == -1)
    {
        /*wrong input file format*/
        return -1;
    }

    /* Check parameter is within valid range */
    if(*maxQueLen <= -2)
    {
        return -5;
    }

    /* read the numServicePoints parameter */
    if(readParameter(fp, "numServicePoints", numServicePoints) == -1)
    {
        /*wrong input file format*/
        return -1;
    }

    /* Check parameter is positive */
    if(*numServicePoints <= 0)
    {
        return -2;
    }
    
    /* read the closingTime parameter*/
    if(readParameter(fp, "closingTime", closingTime) == -1)
    {
        /*wrong input file format*/
        return -1;
    }

    /* Check parameter is positive */
    if(*closingTime <= 0)
    {
        return -2;
    }

    /* read the distributionType parameter */
    if(readParameter(fp, "distributionType", distributionType) == -1)
    {
        /*wrong input file format*/
        return -1;
    }

    /* checking if its 0 or 1 */
    if(*distributionType > 1 || *distributionType < 0)
    {
        printf("TEST: %d\n", *distributionType);
        return -7;
    }

    /* read the maxNewCustomers parameter*/
    if(readParameter(fp, "maxNewCustomers", maxNewCustomers) == -1)
    {
        /*wrong input file format*/
        return -1;
    }

    /* Check parameter is positive */
    if(*maxNewCustomers <= 0)
    {
        return -2;
    }

    /* read the minNewCustomers parameter*/
    if(readParameter(fp, "minNewCustomers", minNewCustomers) == -1)
    {
        /*wrong input file format*/
        return -1;
    }

    /* Check parameter is not negative */
    if(*minNewCustomers < 0)
    {
        return -2;
    }

    /* Check that max isn't lower than min value */
    if(*maxNewCustomers < *minNewCustomers)
    {
        return -4;
    }

    /* read the maxServeTime parameter*/
    if(readParameter(fp, "maxServeTime", maxServeTime) == -1)
    {
        /*wrong input file format*/
        return -1;
    }

    /* Check parameter is positive */
    if(*maxServeTime <= 0)
    {
        return -2;
    }

    /* read the maxWaitingTolerance parameter */
    if(readParameter(fp, "maxWaitingTolerance", maxWaitingTolerance) == -1)
    {
        /*wrong input file format*/
        return -1;
    }

    /* Check parameter is positive */
    if(*maxWaitingTolerance <= 0)
    {
        return -2;
    }

    /* read the meanForNewCustomers parameter */
    if(readParameter(fp, "meanForNewCustomers", meanForNewCustomers) == -1)
    {
        /*wrong input file format*/
        return -1;
    }

    /* read the standardDeviationForNewCustomers parameter */
    if(readParameter(fp, "standardDeviationForNewCustomers", standardDeviationForNewCustomers) == -1)
    {
        /*wrong input file format*/
        return -1;
    }

    if(*standardDeviationForNewCustomers > *meanForNewCustomers)
    {
        return -6;
    }

    /* read the meanForServingTime parameter */
    if(readParameter(fp, "meanForServingTime", meanForServingTime) == -1)
    {
        /*wrong input file format*/
        return -1;
    }

    /* read the standardDeviationForServingTime parameter */
    if(readParameter(fp, "standardDeviationForServingTime", standardDeviationForServingTime) == -1)
    {
        /*wrong input file format*/
        return -1;
    }

    if(*standardDeviationForServingTime > *meanForServingTime)
    {
        return -6;
    }


    /* read the meanForWaitingTolerance parameter */
    if(readParameter(fp, "meanForWaitingTolerance", meanForWaitingTolerance) == -1)
    {
        /*wrong input file format*/
        return -1;
    }

    /* read the standardDeviationForWaitingTolerance parameter */
    if(readParameter(fp, "standardDeviationForWaitingTolerance", standardDeviationForWaitingTolerance) == -1)
    {
        /*wrong input file format*/
        return -1;
    }

    if(*standardDeviationForWaitingTolerance > *meanForWaitingTolerance)
    {
        return -6;
    }


    /* close the file */
    fclose(fp);
    return 0;
}

/* Function to print the readed parameters */
void printReadParameters(int maxQueLen, int numServicePoints, int closingTime, int maxNewCustomers, int minNewCustomers, int maxServeTime,
    int maxWaitingTolerance, int distributionType, int meanForNewCustomers, int standardDeviationForNewCustomers, int meanForServingTime,
    int standardDeviationForServingTime, int meanForWaitingTolerance, int standardDeviationForWaitingTolerance)
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
        printf("maxWaitingTolerance %d\n", maxWaitingTolerance);
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
