#include "Vector.h"

Vector4D::Vector4D()
{
	//Initialize variables
	x = y = z = w = 0;
}

Vector4D::Vector4D(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector4D::Vector4D(const Vector4D& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
}

Vector4D::~Vector4D()
{}

Vector3D Vector4D::rotateEulerX(Vector3D v, float r)
{
	//Rotation matrix for roll
	// 1    0    0
	// 0   cos -sin
	// 0   sin  cos

	Vector3D result;

	result.x = v.x;
	result.y = (v.y * cosf(r)) + (v.z * -sinf(r));
	result.z = (v.y * sinf(r)) + (v.z * cosf(r));

	return result;
}

Vector3D Vector4D::rotateEulerY(Vector3D v, float r)
{
	//Rotation matrix for pitch
	//cos   0   sin
	//0     1    0
	//-sin  0   cos

	Vector3D result;

	result.x = (v.x * cosf(r)) + (v.z * sinf(r));
	result.y = v.y;
	result.z = (v.x * -sinf(r)) + (v.z * cosf(r));

	return result;
}

Vector3D Vector4D::rotateEulerZ(Vector3D v, float r)
{
	//Rotation matrix for yaw
	//cos -sin   0
	//sin  cos   0
	// 0    0    1

	Vector3D result;

	result.x = (v.x * cosf(r)) + (v.y * -sinf(r));
	result.y = (v.x * sinf(r)) + (v.y * cosf(r));
	result.z = v.z;

	return result;
}

Vector3D Vector4D::rotateVbyQ(Vector4D q, Vector3D v)
{
	//Rotate vector by quaternion
	//v' = qvq*
	Vector3D result;
	Vector4D vPrime;
	Vector4D qConj(-q.x, -q.y, -q.z, q.w);
	Vector4D vQuat(v.x, v.y, v.z, 1.0f);

	vPrime = q * vQuat;
	vPrime = vPrime * qConj;

	result.x = vPrime.x;
	result.y = vPrime.y;
	result.z = vPrime.z;

	return result;
}

Vector4D Vector4D::operator*(const Vector4D& qR)
{
	//Quaternion multiplication
	Vector4D result;
	float qx, qy, qz, qw;
	float rx, ry, rz, rw;

	qx = this->x;
	qy = this->y;
	qz = this->z;
	qw = this->w;

	rx = qR.x;
	ry = qR.y;
	rz = qR.z;
	rw = qR.w;

	result.w = (qw * rw) - (qx * rx)
		- (qy * ry) - (qz * rz);
	result.x = (qx * rw) + (qw * rx)
		- (qz * ry) + (qy * rz);
	result.y = (qy * rw) + (qz * rx)
		+ (qw * ry) - (qx * rz);
	result.z = (qz * rw) - (qy * rx)
		+ (qx * ry) + (qw * rz);

	return result;
}

float Vector4D::Length()
{
	float result = 0;

	result += powf(x, 2) + powf(y, 2)
		+ powf(z, 2) + powf(w, 2);
	result = sqrtf(result);

	return result;
}

void Vector4D::Normalize()
{
	float mag = Length();

	x /= mag;
	y /= mag;
	z /= mag;
	w /= mag;
}