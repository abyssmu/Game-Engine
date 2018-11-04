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
		double r = 0.0, g = 0.0;
		double b = 0.0, a = 0.0;
	};

	class Color
	{
	public:		
		Color(
			const Color& other);
		Color(
			double r,
			double g,
			double b,
			double a);

		//Brighten or dim color by amt
		void Brightness(
			double amt);
		void Add(
			Color B);
		bool Compare(
			Color B);
		void Divide(
			Color B);
		void Equal(
			Color B);
		void Multiply(
			Color B);
		void Subtract(
			Color B);

		//Check color values for greater than 1 or less than 0
		void checkValues();
		ColorVec color = { 0.0, 0.0, 0.0, 0.0 };
	};

	Color Black();
	Color Blue();
	Color Cyan();
	Color Green();
	Color Grey();
	Color Magenta();
	Color Red();
	Color White();
	Color Yellow();
}