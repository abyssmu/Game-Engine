/*
RNG is used to randomly generate numbers. It can generate random integer values using normal int
distribution, random double values using exponential distribution,
*/

#pragma once

#include <random>
#include <time.h>

namespace RNG
{
	int Range(
		int A,
		int B);
	double RangeD(
		double A,
		double B);
	int Value();
	double ValueD();
	double ZeroToOne();
}