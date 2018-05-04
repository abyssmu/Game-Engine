#include "RNG.h"

//Return a random integer between A and B
int RNG::Range(int A, int B)
{
	//Mod random value by B and offset by A
	return Value() % B + A;
}

//Return a random double between A and B
double RNG::RangeD(double A, double B)
{
	double random = ValueD();

	//Creates temporary value to use in getting exponent
	double temp = random;

	int i = 0;

	//Divide until temp is less than B
	while (!(temp < B))
	{
		temp /= B;
		++i;
	}

	//Mod the random value by B
	random = random / pow(B, i);
	random = B - random;

	//Offset by A
	random += A;

	return random;
}

//Return a random integer between 0 and INT_MAX
int RNG::Value()
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> dist(0, INT_MAX);

	return dist(generator);
}

//Return a random double between 0 and INT_MAX
double RNG::ValueD()
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_real_distribution<double> dist(0, INT_MAX);

	return dist(generator);
}

//Return a random double between 0 and 1
double RNG::ZeroToOne()
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_real_distribution<double> dist(0, 1);

	return dist(generator);
}