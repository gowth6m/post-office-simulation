/*
* File:         randGenerator.c
*
* Description:  Implementation of some functions to produce random numbers using a Gaussian distribution from uniformly distributed numbers.
*
* Autor:        gowth6m
*
* Date:         01.02.2021
*/
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

/* Function to swap two integer variables */
void swap(int *a, int *b)
{
    (*a) = (*a) + (*b);
    (*b) = (*a) - (*b);
    (*a) = (*a) - (*b);
}

/* Function that returns a random integer with uniform distribution in the given range */
int getUniformRandNum(int l, int r)
{
    if (l > r)
    {
        swap(&l, &r);
    }

    return rand() % (r - l + 1) + l;
}

/* Function that returns a random double from a Gaussian distribution. It uses the Marsaglia polar method where
   firstly, U and V are drawn from the uniform distribution, and then S = U^2 + V^2 is computed.
   If S is greater or equal to 1, then the method starts over, otherwise the function X = U (-2*ln(S)/S)^(1/2)
   is used and the result multiplied by the standard deviation value given in and added to the maen to produce
   a random number.
   */
long double getGaussianRandNum(long double mean, long double sigma) 
{
    long double u, v, s, result;

    u = ((long double) rand() / (RAND_MAX)) * 2 - 1;
    v = ((long double) rand() / (RAND_MAX)) * 2 - 1;
    s = u * u + v * v;

    if (s == 0 || s >= 1) 
    {
        return getGaussianRandNum (mean, sigma);
    }

    result = u * sqrt(-2.0 * log(s)/s);
    
    return (result * sigma + mean);
}

/* Function to test out random functions */
void testGaussianRandom(long double mean, long double sigma, int amount, int min, int max) {
    int i;
    for(i=0; i < amount; i++)
    {
        fprintf(stdout, "%.2Lf,", getGaussianRandNum(mean, sigma));
    }

	fprintf(stderr, "\n\n");

    int j;
    for(j=0; j < amount; j++)
    {
        fprintf(stdout, "%d,", getUniformRandNum(min, max));
    }
}

