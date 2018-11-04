#include "RNG.h"

int RNG::Range(
	int A,
	int B)
{
	return Value() % B + A;
}

double RNG::RangeD(
	double A,
	double B)
{
	auto random = ValueD();
	auto temp = random;
	auto i = 0;

	while (!(temp < B))
	{
		temp /= B;
		++i;
	}

	random = random / pow(B, i);
	random = B - random;
	random += A;

	return random;
}

int RNG::Value()
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> dist(0, INT_MAX);

	return dist(generator);
}

double RNG::ValueD()
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_real_distribution<double> dist(0, INT_MAX);

	return dist(generator);
}

double RNG::ZeroToOne()
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_real_distribution<double> dist(0, 1);

	return dist(generator);
}