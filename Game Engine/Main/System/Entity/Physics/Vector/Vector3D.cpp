//Vector3D class
//Container for 3D behavior

#include "Vector.h"

//Constructor
Vector3D::Vector3D()
{
	//Initialize variables
	x = y = z = 0;
}

//Constructor with input
Vector3D::Vector3D(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

//Copy constructor
Vector3D::Vector3D(const Vector3D& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
}

//Default destructor
Vector3D::~Vector3D()
{}

//+ operator override
Vector3D Vector3D::operator+(const Vector3D& b)
{
	Vector3D result;

	result.x = this->x + b.x;
	result.y = this->y + b.y;
	result.z = this->z + b.z;

	return result;
}

//+= operator override
Vector3D Vector3D::operator+=(const Vector3D& b)
{
	this->x += b.x;
	this->y += b.y;
	this->z += b.z;

	return *this;
}

//- operator override
Vector3D Vector3D::operator-(const Vector3D& b)
{
	Vector3D result;

	result.x = this->x - b.x;
	result.y = this->y - b.y;
	result.z = this->z - b.z;

	return result;
}

//-= operator override
Vector3D Vector3D::operator-=(const Vector3D& b)
{
	this->x -= b.x;
	this->y -= b.y;
	this->z -= b.z;

	return *this;
}

//= operator override
Vector3D Vector3D::operator=(const Vector3D& b)
{
	this->x = b.x;
	this->y = b.y;
	this->z = b.z;

	return *this;
}

//Get X unit vector
Vector3D Vector3D::UnitX()
{
	Vector3D result;

	result.x = 1.0f;
	result.y = 0.0f;
	result.z = 0.0f;

	return result;
}

//Get Y unit vector
Vector3D Vector3D::UnitY()
{
	Vector3D result;

	result.x = 0.0f;
	result.y = 1.0f;
	result.z = 0.0f;

	return result;
}

//Get Z unit vector
Vector3D Vector3D::UnitZ()
{
	Vector3D result;

	result.x = 0.0f;
	result.y = 0.0f;
	result.z = 1.0f;

	return result;
}

//Calculate cross product (a x b)
Vector3D Vector3D::Cross(Vector3D a, Vector3D b)
{
	Vector3D result;

	result.x = (a.y * b.z) - (a.z * b.y);
	result.y = (a.z * b.x) - (a.x * b.z);
	result.z = (a.x * b.y) - (a.y * b.x);

	return result;
}

//Calculate dot product
float Vector3D::Dot(Vector3D a, Vector3D b)
{
	float result = 0;

	result += a.x * b.x;
	result += a.y * b.y;
	result += a.z * b.z;

	return result;
}

//Calculate vector length
float Vector3D::Length()
{
	float result = 0;

	result += powf(x, 2) + powf(y, 2) + powf(z, 2);
	result = sqrtf(result);

	return result;
}

//Normalize vector
void Vector3D::Normalize()
{
	float mag = Length();

	x /= mag;
	y /= mag;
	z /= mag;
}

//Scale vector
void Vector3D::Scale(float val)
{
	x *= val;
	y *= val;
	z *= val;
}