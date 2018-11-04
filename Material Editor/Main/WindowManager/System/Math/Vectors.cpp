#include "MathLib.h"

MathLib::Vectors::Vector2D::Vector2D(
	const Vector2D& other)
{
	dimension = other.dimension;
	x = other.x;
	y = other.y;
}

MathLib::Vectors::Vector2D::Vector2D(
	double x,
	double y)
{
	dimension = 2;
	this->x = x;
	this->y = y;
}

void MathLib::Vectors::Vector2D::GetUnits(
	double* units)
{
	units[0] = x;
	units[1] = y;
}

void MathLib::Vectors::Vector2D::SetUnits(
	double* units)
{
	x = units[0];
	y = units[1];
}

MathLib::Vectors::Vector3D::Vector3D(
	const Vector2D& other)
{
	dimension = 3;
	x = other.x;
	y = other.y;
	z = 0.0;
}

MathLib::Vectors::Vector3D::Vector3D(
	const Vector3D& other)
{
	dimension = other.dimension;
	x = other.x;
	y = other.y;
	z = other.z;
}

MathLib::Vectors::Vector3D::Vector3D(
	double x,
	double y,
	double z)
{
	dimension = 3;
	this->x = x;
	this->y = y;
	this->z = z;
}

MathLib::Vectors::VectorParent* MathLib::Vectors::Vector3D::Cross(
	VectorParent* B)
{
	static auto result = Vector3D(Zero_3D());

	result.x = (this->y * B->z) - (this->z * B->y);
	result.y = (this->z * B->x) - (this->x * B->z);
	result.z = (this->x * B->y) - (this->y * B->x);

	return &result;
}

void MathLib::Vectors::Vector3D::GetUnits(
	double* units)
{
	units[0] = x;
	units[1] = y;
	units[2] = z;
}

void MathLib::Vectors::Vector3D::SetUnits(
	double* units)
{
	x = units[0];
	y = units[1];
	z = units[2];
}

MathLib::Vectors::Vector4D::Vector4D(
	const Vector2D& other)
{
	dimension = 4;
	x = other.x;
	y = other.y;
	z = w = 0.0;
}

MathLib::Vectors::Vector4D::Vector4D(
	const Vector3D& other)
{
	dimension = 4;
	x = other.x;
	y = other.y;
	z = other.z;
	w = 0.0;
}

MathLib::Vectors::Vector4D::Vector4D(
	const Vector4D& other)
{
	dimension = other.dimension;
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
}

MathLib::Vectors::Vector4D::Vector4D(
	double x,
	double y,
	double z,
	double w)
{
	dimension = 4;
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

void MathLib::Vectors::Vector4D::GetUnits(
	double* units)
{
	units[0] = x;
	units[1] = y;
	units[2] = z;
	units[3] = w;
}

void MathLib::Vectors::Vector4D::SetUnits(
	double* units)
{
	x = units[0];
	y = units[1];
	z = units[2];
	w = units[3];
}

MathLib::Vectors::Vector2D MathLib::Vectors::UnitX_2D()
{
	return Vector2D(1.0, 0.0);
}

MathLib::Vectors::Vector3D MathLib::Vectors::UnitX_3D()
{
	return Vector3D(1.0, 0.0, 0.0);
}

MathLib::Vectors::Vector4D MathLib::Vectors::UnitX_4D()
{
	return Vector4D(1.0, 0.0, 0.0, 0.0);
}

MathLib::Vectors::Vector2D MathLib::Vectors::UnitY_2D()
{
	return Vector2D(0.0, 1.0);
}

MathLib::Vectors::Vector3D MathLib::Vectors::UnitY_3D()
{
	return Vector3D(0.0, 1.0, 0.0);
}

MathLib::Vectors::Vector4D MathLib::Vectors::UnitY_4D()
{
	return Vector4D(0.0, 1.0, 0.0, 0.0);
}

MathLib::Vectors::Vector3D MathLib::Vectors::UnitZ_3D()
{
	return Vector3D(0.0, 0.0, 1.0);
}

MathLib::Vectors::Vector4D MathLib::Vectors::UnitZ_4D()
{
	return Vector4D(0.0, 0.0, 1.0, 0.0);
}

MathLib::Vectors::Vector4D MathLib::Vectors::UnitW_4D()
{
	return Vector4D(0.0, 0.0, 0.0, 1.0);
}

MathLib::Vectors::Vector2D MathLib::Vectors::One_2D()
{
	return Vector2D(1.0, 1.0);
}

MathLib::Vectors::Vector3D MathLib::Vectors::One_3D()
{
	return Vector3D(1.0, 1.0, 1.0);
}

MathLib::Vectors::Vector4D MathLib::Vectors::One_4D()
{
	return Vector4D(1.0, 1.0, 1.0, 1.0);
}

MathLib::Vectors::Vector2D MathLib::Vectors::Zero_2D()
{
	return Vector2D(0.0, 0.0);
}

MathLib::Vectors::Vector3D MathLib::Vectors::Zero_3D()
{
	return Vector3D(0.0, 0.0, 0.0);
}

MathLib::Vectors::Vector4D MathLib::Vectors::Zero_4D()
{
	return Vector4D(0.0, 0.0, 0.0, 0.0);
}

double MathLib::Vectors::Dot(
	VectorParent* A,
	VectorParent* B)
{
	if (A->dimension != B->dimension)
	{
		return _CRT_INT_MAX;
	}

	auto uA = new double[A->dimension];
	auto uB = new double[B->dimension];
	A->GetUnits(uA);
	B->GetUnits(uB);

	auto result = 0.0;
	
	for (auto i = 0; i < A->dimension; ++i)
	{
		result += uA[i] * uB[i];
	}

	delete[] uA;
	delete[] uB;

	return result;
}

double MathLib::Vectors::Length(
	VectorParent* A)
{
	auto u = new double[A->dimension];
	A->GetUnits(u);

	auto result = 0.0;
	
	for (auto i = 0; i < A->dimension; ++i)
	{
		result += pow(u[i], 2);
	}

	result = sqrt(result);

	delete[] u;

	return result;
}

void MathLib::Vectors::Normalize(
	VectorParent* A)
{
	auto u = new double[A->dimension];
	A->GetUnits(u);

	auto length = Length(A);
	
	for (auto i = 0; i < A->dimension; ++i)
	{
		u[i] /= length;
	}

	A->SetUnits(u);

	delete[] u;
}

void MathLib::Vectors::Scale(
	VectorParent* A,
	double amt)
{
	auto u = new double[A->dimension];
	A->GetUnits(u);

	for (auto i = 0; i < A->dimension; ++i)
	{
		u[i] *= amt;
	}

	A->SetUnits(u);

	delete[] u;
}

void MathLib::Vectors::Add(
	VectorParent* A,
	VectorParent* B)
{
	auto uA = new double[A->dimension];
	auto uB = new double[B->dimension];
	A->GetUnits(uA);
	B->GetUnits(uB);

	for (auto i = 0; i < A->dimension; ++i)
	{
		uA[i] += uB[i];
	}

	A->SetUnits(uA);

	delete[] uA;
	delete[] uB;
}

bool MathLib::Vectors::Compare(
	VectorParent* A,
	VectorParent* B)
{
	if (A->dimension != B->dimension)
	{
		return false;
	}

	auto uA = new double[A->dimension];
	auto uB = new double[B->dimension];
	A->GetUnits(uA);
	B->GetUnits(uB);

	auto equals = true;
	
	for (auto i = 0; i < A->dimension; ++i)
	{
		if (uA[i] != uB[i])
		{
			equals = false;
			break;
		}
	}

	delete[] uA;
	delete[] uB;

	return equals;
}

void MathLib::Vectors::Equal(
	VectorParent* A,
	VectorParent* B)
{
	if (A->dimension != B->dimension)
	{
		return;
	}

	auto uA = new double[A->dimension];
	auto uB = new double[B->dimension];
	A->GetUnits(uA);
	B->GetUnits(uB);

	for (auto i = 0; i < A->dimension; ++i)
	{
		uA[i] = uB[i];
	}

	A->SetUnits(uA);

	delete[] uA;
	delete[] uB;
}

void MathLib::Vectors::Subtract(
	VectorParent* A,
	VectorParent* B)
{
	auto uA = new double[A->dimension];
	auto uB = new double[B->dimension];
	A->GetUnits(uA);
	B->GetUnits(uB);

	for (auto i = 0; i < A->dimension; ++i)
	{
		uA[i] -= uB[i];
	}

	A->SetUnits(uA);

	delete[] uA;
	delete[] uB;
}