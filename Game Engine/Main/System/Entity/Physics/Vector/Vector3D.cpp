#include "Vector.h"

Vector3D::Vector3D()
{
	//Initialize variables
	x = y = z = 0;
}

Vector3D::Vector3D(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3D::Vector3D(const Vector3D& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
}

Vector3D::~Vector3D()
{}

Vector3D Vector3D::operator+(const Vector3D& b)
{
	Vector3D result;

	result.x = this->x + b.x;
	result.y = this->y + b.y;
	result.z = this->z + b.z;

	return result;
}

Vector3D Vector3D::operator+=(const Vector3D& b)
{
	this->x += b.x;
	this->y += b.y;
	this->z += b.z;

	return *this;
}

Vector3D Vector3D::operator-(const Vector3D& b)
{
	Vector3D result;

	result.x = this->x - b.x;
	result.y = this->y - b.y;
	result.z = this->z - b.z;

	return result;
}

Vector3D Vector3D::operator-=(const Vector3D& b)
{
	this->x -= b.x;
	this->y -= b.y;
	this->z -= b.z;

	return *this;
}

Vector3D Vector3D::operator=(const Vector3D& b)
{
	this->x = b.x;
	this->y = b.y;
	this->z = b.z;

	return *this;
}

Vector3D Vector3D::UnitX()
{
	Vector3D result;

	result.x = 1.0f;
	result.y = 0.0f;
	result.z = 0.0f;

	return result;
}

Vector3D Vector3D::UnitY()
{
	Vector3D result;

	result.x = 0.0f;
	result.y = 1.0f;
	result.z = 0.0f;

	return result;
}

Vector3D Vector3D::UnitZ()
{
	Vector3D result;

	result.x = 0.0f;
	result.y = 0.0f;
	result.z = 1.0f;

	return result;
}

Vector3D Vector3D::Cross(Vector3D a, Vector3D b)
{
	Vector3D result;

	result.x = (a.y * b.z) - (a.z * b.y);
	result.y = (a.z * b.x) - (a.x * b.z);
	result.z = (a.x * b.y) - (a.y * b.x);

	return result;
}

float Vector3D::Dot(Vector3D a, Vector3D b)
{
	float result = 0;

	result += a.x * b.x;
	result += a.y * b.y;
	result += a.z * b.z;

	return result;
}

float Vector3D::Length()
{
	float result = 0;

	result += powf(x, 2) + powf(y, 2) + powf(z, 2);
	result = sqrtf(result);

	return result;
}

void Vector3D::Normalize()
{
	float mag = Length();

	x /= mag;
	y /= mag;
	z /= mag;
}

void Vector3D::Scale(float val)
{
	x *= val;
	y *= val;
	z *= val;
}