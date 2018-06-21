/*
RNG is used to randomly generate numbers. It can generate random integer values using normal int
distribution, random double values using exponential distribution,
*/

#pragma once

//Includes
#include <random>
#include <time.h>

namespace RNG
{
	//Return a random integer between A and B
	int Range(int A, int B);

	//Return a random double between A and B
	double RangeD(double A, double B);

	//Return a random integer between 0 and INT_MAX
	int Value();

	//Return a random double between 0 and INT_MAX
	double ValueD();

	//Return a random double between 0 and 1
	double ZeroToOne();
}