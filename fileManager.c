/*
* File:         customerQueue.c
*
* Description:  implementation of some functions to read the input from the input file.
*
* Autor:        Gowthaman Ravindrathas
*
* Date:         30.01.2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function that read one parameter from the input file 
    with the correct format. 
*/
int readParameter(FILE *fp, char *parameterName, int *parameter)
{

    char s[20];
    int auxSize = strlen(parameterName);

    /* read the parameter*/
    if(fscanf(fp, "%s %d", s, parameter) < 2)
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
int getInfoFromInput(char *fileName, int *maxQueLen, int *numServicePoints, int *closingTime, int *maxNewCustomers, int *minNewCustomers, int *maxServeTime, int *maxWaitingTolerance) 
{
    
    /* Pointer to the file */
    FILE *fp;
    /* Opening a file in r mode*/
    fp = fopen (fileName, "r");

    if(fp == NULL){
        /* failed opening file */
        return -3;
    }

    /* read the maxQueLen parameter*/
    if(readParameter(fp, "maxQueueLength", maxQueLen) == -1)
    {
        /*wrong input file format*/
        return -1;
    }

    /* Check parameter is positive */
    if(maxQueLen <= 0){
        return -2;
    }

    /* read the numServicePoints parameter*/
    if(readParameter(fp, "numServicePoints", numServicePoints) == -1)
    {
        /*wrong input file format*/
        return -1;
    }

    /* Check parameter is positive */
    if(numServicePoints <= 0){
        return -2;
    }
    
    /* read the closingTime parameter*/
    if(readParameter(fp, "closingTime", closingTime) == -1)
    {
        /*wrong input file format*/
        return -1;
    }

    /* Check parameter is positive */
    if(closingTime <= 0){
        return -2;
    }

    /* read the maxNewCustomers parameter*/
    if(readParameter(fp, "maxNewCustomers", maxNewCustomers) == -1)
    {
        /*wrong input file format*/
        return -1;
    }

    /* Check parameter is positive */
    if(maxNewCustomers <= 0){
        return -2;
    }

    /* read the minNewCustomers parameter*/
    if(readParameter(fp, "minNewCustomers", minNewCustomers) == -1)
    {
        /*wrong input file format*/
        return -1;
    }

    /* Check parameter is not negative */
    if(minNewCustomers < 0){
        return -2;
    }

    /* read the maxServeTime parameter*/
    if(readParameter(fp, "maxServeTime", maxServeTime) == -1)
    {
        /*wrong input file format*/
        return -1;
    }

    /* Check parameter is positive */
    if(maxServeTime <= 0){
        return -2;
    }

    /* read the maxWaitingTolerance parameter*/
    if(readParameter(fp, "maxWaitingTolerance", maxWaitingTolerance) == -1)
    {
        /*wrong input file format*/
        return -1;
    }

    /* Check parameter is positive */
    if(maxWaitingTolerance <= 0){
        return -2;
    }
    
    /* close the file */
    fclose(fp);

    return 0;
}

/*Function to print the readed parameters */
void printReadedParameters(int maxQueLen, int numServicePoints, int closingTime, int maxNewCustomers, int minNewCustomers, int maxServeTime, int maxWaitingTolerance)
{
    printf("\nReaded parameters:\n\n");

    printf("maxQueueLength %d\n", maxQueLen);
    
    printf("numServicePoints %d\n", numServicePoints);
    
    printf("closingTime %d\n", closingTime);
    
    printf("maxNewCustomers %d\n", maxNewCustomers);
    
    printf("minNewCustomers %d\n", minNewCustomers);
    
    printf("maxServeTime %d\n", maxServeTime);
    
    printf("maxWaitingTolerance %d\n", maxWaitingTolerance);
}