/*
* File:			randGenerator.h
*
* Description:  Implementation of some functions to produce random numbers using a Gaussian distribution from uniformly distributed numbers. header file.
*
* Autor: 		Gowthaman Ravindrathas
*
* Date:			30.01.2021
*/

#ifndef __RAND_GENERATOR_H
#define __RAND_GENERATOR_H

/* Function that returns a random integer with uniform distribution in the given range */
int getUniformRandNum(int l, int r);

/* Function that returns a random double from a Gaussian distribution */
long double getGaussianRandNum (long double mi, long double sigma);

#endif