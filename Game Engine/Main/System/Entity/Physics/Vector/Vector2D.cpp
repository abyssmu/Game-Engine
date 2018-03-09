//Vector2D class
//Operates as container for 2D behavior

#include "Vector.h"

//Constructor
Vector2D::Vector2D()
{
	//Initialize variables
	x = y = 0;
}

//Constructor with input
Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
}

//Copy constructor
Vector2D::Vector2D(const Vector2D& other)
{
	x = other.x;
	y = other.y;
}

//Default destructor
Vector2D::~Vector2D()
{}

//+ operator override
Vector2D Vector2D::operator+(const Vector2D& b)
{
	Vector2D result;

	result.x = this->x + b.x;
	result.y = this->y + b.y;

	return result;
}

//+= operator override
Vector2D Vector2D::operator+=(const Vector2D& b)
{
	this->x += b.x;
	this->y += b.y;

	return *this;
}

//- operator override
Vector2D Vector2D::operator-(const Vector2D& b)
{
	Vector2D result;

	result.x = this->x - b.x;
	result.y = this->y - b.y;

	return result;
}

//-= operator override
Vector2D Vector2D::operator-=(const Vector2D& b)
{
	this->x -= b.x;
	this->y -= b.y;

	return *this;
}

//= operator override
Vector2D Vector2D::operator=(const Vector2D& b)
{
	this->x = b.x;
	this->y = b.y;

	return *this;
}

//Get X unit vector
Vector2D Vector2D::UnitX()
{
	Vector2D result;

	result.x = 1.0f;
	result.y = 0.0f;

	return result;
}

//Get Y unit vector
Vector2D Vector2D::UnitY()
{
	Vector2D result;

	result.x = 0.0f;
	result.y = 1.0f;

	return result;
}

//Calculate dot product
float Vector2D::Dot(Vector2D* a, Vector2D* b)
{
	float result = 0;

	result += a->x * b->x;
	result += a->y * b->y;

	return result;
}

//Calculate vector length
float Vector2D::Length()
{
	float result = 0;

	result += powf(x, 2) + powf(y, 2);
	result = sqrtf(result);

	return result;
}

//Normalize vector
void Vector2D::Normalize()
{
	float mag = Length();

	x /= mag;
	y /= mag;
}

//Scale vector
void Vector2D::Scale(float val)
{
	x *= val;
	y *= val;
}