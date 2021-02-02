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

void swap(int *a, int *b);

int random_integer(int l, int r);

long double g_rand (long double mi, long double sigma);

#endif