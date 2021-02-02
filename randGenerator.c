/*
* File:         randGenerator.c
*
* Description:  Implementation of some functions to produce random numbers using a Gaussian distribution from uniformly distributed numbers.
*
* Autor:        Gowthaman Ravindrathas
*
* Date:         30.01.2021
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
int random_integer(int l, int r)
{
    if (l > r)
        swap(&l, &r);
    return rand() % (r - l + 1) + l;
}

/* Function that returns a random double from a Gaussian distribution */
long double g_rand (long double mi, long double sigma) {
    long double v1, v2, s, result;

    v1 = ((long double) rand() / (RAND_MAX)) * 2 - 1;
    v2 = ((long double) rand() / (RAND_MAX)) * 2 - 1;
    s = v1*v1 + v2*v2;

    if (s == 0 || s >= 1) 
    {
        return g_rand (mi, sigma);
    }

    result = v1*sqrt(-2.0* log(s)/s);
    return (mi+result*sigma);
}