/*
Color library holds color class and a collection of color constants with a few functions
for modifying colors.
*/

#pragma once

//Color namespace
/*
Current data held:
	Color
	Color Constants
*/

namespace Colors
{
	struct ColorVec
	{
		double r, g, b, a;
	};

	///////Color Vector
	class Color
	{
	public:
		//Default constructor
		Color();
		
		//Copy constructor
		Color(const Color& other);

		//Unit constructor
		Color(double r, double g, double b, double a);

		//Default destructor
		~Color();

		////////Math Operations
		//Brighten or dim color by amt
		void Brightness(double amt);

		////////Math Functions
		//Add colors
		//A(this) + B
		void Add(Color B);

		//Compare colors
		//A(this) == B
		bool Compare(Color B);

		//Divide colors
		//A(this) / B
		void Divide(Color B);

		//Equalize colors
		//A(this) = B
		void Equal(Color B);

		//Multiply colors
		//A(this) * B
		void Multiply(Color B);

		//Subtract colors
		//A(this) - B
		void Subtract(Color B);

		////////Utility Functions
		//Check color values for greater than 1 or less than 0
		void checkValues();

		////////Main Variables
		ColorVec color;
	};

	////////Color Constants
	//Return black
	Color Black();

	//Return blue
	Color Blue();

	//Return cyan
	Color Cyan();

	//Return green
	Color Green();

	//Return grey
	Color Grey();

	//Return magenta
	Color Magenta();

	//Return red
	Color Red();

	//Return white
	Color White();

	//Return yellow
	Color Yellow();
}