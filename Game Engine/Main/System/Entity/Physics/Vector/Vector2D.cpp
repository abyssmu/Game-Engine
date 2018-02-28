#include "Vector.h"

Vector2D::Vector2D()
{
	//Initialize variables
	x = y = 0;
}

Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2D::Vector2D(const Vector2D& other)
{
	x = other.x;
	y = other.y;
}

Vector2D::~Vector2D()
{}

Vector2D Vector2D::operator+(const Vector2D& b)
{
	Vector2D result;

	result.x = this->x + b.x;
	result.y = this->y + b.y;

	return result;
}

Vector2D Vector2D::operator+=(const Vector2D& b)
{
	this->x += b.x;
	this->y += b.y;

	return *this;
}

Vector2D Vector2D::operator-(const Vector2D& b)
{
	Vector2D result;

	result.x = this->x - b.x;
	result.y = this->y - b.y;

	return result;
}

Vector2D Vector2D::operator-=(const Vector2D& b)
{
	this->x -= b.x;
	this->y -= b.y;

	return *this;
}

Vector2D Vector2D::operator=(const Vector2D& b)
{
	this->x = b.x;
	this->y = b.y;

	return *this;
}

Vector2D Vector2D::UnitX()
{
	Vector2D result;

	result.x = 1.0f;
	result.y = 0.0f;

	return result;
}

Vector2D Vector2D::UnitY()
{
	Vector2D result;

	result.x = 0.0f;
	result.y = 1.0f;

	return result;
}

float Vector2D::Dot(Vector2D* a, Vector2D* b)
{
	float result = 0;

	result += a->x * b->x;
	result += a->y * b->y;

	return result;
}

float Vector2D::Length()
{
	float result = 0;

	result += powf(x, 2) + powf(y, 2);
	result = sqrtf(result);

	return result;
}

void Vector2D::Normalize()
{
	float mag = Length();

	x /= mag;
	y /= mag;
}

void Vector2D::Scale(float val)
{
	x *= val;
	y *= val;
}