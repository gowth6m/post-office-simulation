/*
* File:			randGenerator.h
*
* Description:  Implementation of some functions to produce random numbers using a Gaussian distribution from uniformly distributed numbers. header file.
*
* Autor: 		gowth6m
*
* Date:			30.01.2021
*/

#ifndef __RAND_GENERATOR_H
#define __RAND_GENERATOR_H

/* Function that returns a random integer with uniform distribution in the given range */
int getUniformRandNum(int l, int r);

/* Function that returns a random double from a Gaussian distribution. It uses the Marsaglia polar method where
   firstly, U and V are drawn from the uniform distribution, and then S = U^2 + V^2 is computed.
   
   If S is greater or equal to 1, then the method starts over, otherwise the function X = U (-2*ln(S)/S)^(1/2)
   is used and the result multiplied by the standard deviation value given in and added to the maen to produce
   a random number. 

   Sources:
   https://en.wikipedia.org/wiki/Normal_distribution
   https://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform)
   https://github.com/wgrocha/gaussian_random
   */
long double getGaussianRandNum (long double mean, long double sigma);

/* Function to test out random functions */
void testGaussianRandom(long double mean, long double sigma, int amount, int min, int max);

#endif