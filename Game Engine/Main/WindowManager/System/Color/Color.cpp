#include "Color.h"

/////////////////////////////////////////////////////////
//Color
/////////////////////////////////////////////////////////

//Default constructor
Colors::Color::Color()
{}

//Copy constructor
Colors::Color::Color(const Color& other)
{
	color.r = other.color.r;
	color.g = other.color.g;
	color.b = other.color.b;
	color.a = other.color.a;
}

//Unit constructor
Colors::Color::Color(double r, double g, double b, double a)
{
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
}

//Default destructor
Colors::Color::~Color()
{}

//Brighten or dim color by amt
void Colors::Color::Brightness(double amt)
{
	color.r *= amt;
	color.g *= amt;
	color.b *= amt;
}

//Add colors
//A(this) + B
void Colors::Color::Add(Color B)
{
	color.r += B.color.r;
	color.g += B.color.g;
	color.b += B.color.b;
}

//Compare colors
//A(this) == B
bool Colors::Color::Compare(Color B)
{
	if (color.r != B.color.r)
	{
		return false;
	}

	if (color.g != B.color.g)
	{
		return false;
	}

	if (color.b != B.color.b)
	{
		return false;
	}

	if (color.a != B.color.a)
	{
		return false;
	}

	return true;
}

//Divide colors
//A(this) / B
void Colors::Color::Divide(Color B)
{
	color.r /= B.color.r;
	color.g /= B.color.g;
	color.b /= B.color.b;
}

//Equalize colors
//A(this) = B
void Colors::Color::Equal(Color B)
{
	color.r = B.color.r;
	color.g = B.color.g;
	color.b = B.color.b;
	color.a = B.color.a;
}

//Multiply colors
//A(this) * B
void Colors::Color::Multiply(Color B)
{
	color.r *= B.color.r;
	color.g *= B.color.g;
	color.b *= B.color.b;
}

//Subtract colors
//A(this) - B
void Colors::Color::Subtract(Color B)
{
	color.r -= B.color.r;
	color.g -= B.color.g;
	color.b -= B.color.b;
}

//Check color values for greater than 1 or less than 0
void Colors::Color::checkValues()
{
	//Check if greater than 1
	if (color.r > 1.0)
	{
		color.r = 1.0;
	}

	if (color.g > 1.0)
	{
		color.g = 1.0;
	}

	if (color.b > 1.0)
	{
		color.b = 1.0;
	}

	if (color.a > 1.0)
	{
		color.a = 1.0;
	}

	//Check if less than 0
	if (color.r < 0.0)
	{
		color.r = 0.0;
	}

	if (color.g < 0.0)
	{
		color.g = 0.0;
	}

	if (color.b < 0.0)
	{
		color.b = 0.0;
	}

	if (color.a < 0.0)
	{
		color.a = 0.0;
	}
}

/////////////////////////////////////////////////////////
//Constants
/////////////////////////////////////////////////////////

//Return black
Colors::Color Colors::Black()
{
	return Color(0.0, 0.0, 0.0, 1.0);
}

//Return blue
Colors::Color Colors::Blue()
{
	return Color(0.0, 0.0, 1.0, 1.0);
}

//Return cyan
Colors::Color Colors::Cyan()
{
	return Color(0.0, 1.0, 1.0, 1.0);
}

//Return green
Colors::Color Colors::Green()
{
	return Color(0.0, 1.0, 0.0, 1.0);
}

//Return grey
Colors::Color Colors::Grey()
{
	return Color(0.5, 0.5, 0.5, 1.0);
}

//Return magenta
Colors::Color Colors::Magenta()
{
	return Color(1.0, 0.0, 1.0, 1.0);
}

//Return red
Colors::Color Colors::Red()
{
	return Color(1.0, 0.0, 0.0, 1.0);
}

//Return white
Colors::Color Colors::White()
{
	return Color(1.0, 1.0, 1.0, 1.0);
}

//Return yellow
Colors::Color Colors::Yellow()
{
	return Color(1.0, 1.0, 0.0, 1.0);
}