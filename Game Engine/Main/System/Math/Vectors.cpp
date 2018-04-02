//Class Includes
#include "MathLib.h"

/////////////////////////////////////////////////////////
//Vectors
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
//2D Vectors
/////////////////////////////////////////////////////////

//Constructor
MathLib::Vectors::Vector2D::Vector2D()
{
	dimension = 2;
	x = y = 0.0;
}

//Copy constructor
MathLib::Vectors::Vector2D::Vector2D(const Vector2D& other)
{
	dimension = other.dimension;
	x = other.x;
	y = other.y;
}

//Unit constructor
MathLib::Vectors::Vector2D::Vector2D(float x, float y)
{
	dimension = 2;
	this->x = x;
	this->y = y;
}

//Default destructor
MathLib::Vectors::Vector2D::~Vector2D()
{}

//Get vector units
void MathLib::Vectors::Vector2D::GetUnits(float* units)
{
	units[0] = x;
	units[1] = y;
}

//Set vector units
void MathLib::Vectors::Vector2D::SetUnits(float* units)
{
	x = units[0];
	y = units[1];
}

/////////////////////////////////////////////////////////
//3D Vectors
/////////////////////////////////////////////////////////

//Constructor
MathLib::Vectors::Vector3D::Vector3D()
{
	dimension = 3;
	x = y = z = 0.0;
}

//Create 3D vector from 2D
//Initialize z = 0;
MathLib::Vectors::Vector3D::Vector3D(const Vector2D& other)
{
	dimension = 3;
	x = other.x;
	y = other.y;
	z = 0.0;
}

//Copy constructor
MathLib::Vectors::Vector3D::Vector3D(const Vector3D& other)
{
	dimension = other.dimension;
	x = other.x;
	y = other.y;
	z = other.z;
}

//Unit constructor
MathLib::Vectors::Vector3D::Vector3D(float x, float y, float z)
{
	dimension = 3;
	this->x = x;
	this->y = y;
	this->z = z;
}

//Default destructor
MathLib::Vectors::Vector3D::~Vector3D()
{}

//Vector cross product
MathLib::Vectors::VectorParent* MathLib::Vectors::Vector3D::Cross(VectorParent* B)
{
	Vector3D result(Zero_3D());

	result.x = (this->y * B->z) - (this->z * B->y);
	result.y = (this->z * B->x) - (this->x * B->z);
	result.z = (this->x * B->y) - (this->y * B->x);

	return &result;
}

//Get vector units
void MathLib::Vectors::Vector3D::GetUnits(float* units)
{
	units[0] = x;
	units[1] = y;
	units[2] = z;
}

//Set vector units
void MathLib::Vectors::Vector3D::SetUnits(float* units)
{
	x = units[0];
	y = units[1];
	z = units[2];
}

/////////////////////////////////////////////////////////
//4D Vectors
/////////////////////////////////////////////////////////

//Constructor
MathLib::Vectors::Vector4D::Vector4D()
{
	dimension = 4;
	x = y = z = w = 0.0;
}

//Create 4D vector from 2D
//Initialize z = 0, w = 0
MathLib::Vectors::Vector4D::Vector4D(const Vector2D& other)
{
	dimension = 4;
	x = other.x;
	y = other.y;
	z = w = 0.0;
}

//Create 4D vector from 3D
//Initialize w = 0
MathLib::Vectors::Vector4D::Vector4D(const Vector3D& other)
{
	dimension = 4;
	x = other.x;
	y = other.y;
	z = other.z;
	w = 0.0;
}

//Copy constructor
MathLib::Vectors::Vector4D::Vector4D(const Vector4D& other)
{
	dimension = other.dimension;
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
}

//Unit constructor
MathLib::Vectors::Vector4D::Vector4D(float x, float y, float z, float w)
{
	dimension = 4;
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

//Default destructor
MathLib::Vectors::Vector4D::~Vector4D()
{}

//Get vector units
void MathLib::Vectors::Vector4D::GetUnits(float* units)
{
	units[0] = x;
	units[1] = y;
	units[2] = z;
	units[3] = w;
}

//Set vector units
void MathLib::Vectors::Vector4D::SetUnits(float* units)
{
	x = units[0];
	y = units[1];
	z = units[2];
	w = units[3];
}

/////////////////////////////////////////////////////////
//Vector Constants
/////////////////////////////////////////////////////////

//Return unit x vector
MathLib::Vectors::Vector2D MathLib::Vectors::UnitX_2D()
{
	return Vector2D(1.0, 0.0);
}

//Return unit x vector
MathLib::Vectors::Vector3D MathLib::Vectors::UnitX_3D()
{
	return Vector3D(1.0, 0.0, 0.0);
}

//Return unit x vector
MathLib::Vectors::Vector4D MathLib::Vectors::UnitX_4D()
{
	return Vector4D(1.0, 0.0, 0.0, 0.0);
}

//Return unit y vector
MathLib::Vectors::Vector2D MathLib::Vectors::UnitY_2D()
{
	return Vector2D(0.0, 1.0);
}

//Return unit y vector
MathLib::Vectors::Vector3D MathLib::Vectors::UnitY_3D()
{
	return Vector3D(0.0, 1.0, 0.0);
}

//Return unit y vector
MathLib::Vectors::Vector4D MathLib::Vectors::UnitY_4D()
{
	return Vector4D(0.0, 1.0, 0.0, 0.0);
}

//Return unit z vector
MathLib::Vectors::Vector3D MathLib::Vectors::UnitZ_3D()
{
	return Vector3D(0.0, 0.0, 1.0);
}

//Return unit z vector
MathLib::Vectors::Vector4D MathLib::Vectors::UnitZ_4D()
{
	return Vector4D(0.0, 0.0, 1.0, 0.0);
}

//Return unit w vector
MathLib::Vectors::Vector4D MathLib::Vectors::UnitW_4D()
{
	return Vector4D(0.0, 0.0, 0.0, 1.0);
}

//Return vector of ones
MathLib::Vectors::Vector2D MathLib::Vectors::One_2D()
{
	return Vector2D(1.0, 1.0);
}

//Return vector of ones
MathLib::Vectors::Vector3D MathLib::Vectors::One_3D()
{
	return Vector3D(1.0, 1.0, 1.0);
}

//Return vector of ones
MathLib::Vectors::Vector4D MathLib::Vectors::One_4D()
{
	return Vector4D(1.0, 1.0, 1.0, 1.0);
}

//Return zero vector
MathLib::Vectors::Vector2D MathLib::Vectors::Zero_2D()
{
	return Vector2D(0.0, 0.0);
}

//Return zero vector
MathLib::Vectors::Vector3D MathLib::Vectors::Zero_3D()
{
	return Vector3D(0.0, 0.0, 0.0);
}

//Return zero vector
MathLib::Vectors::Vector4D MathLib::Vectors::Zero_4D()
{
	return Vector4D(0.0, 0.0, 0.0, 0.0);
}

/////////////////////////////////////////////////////////
//Vector Operations
/////////////////////////////////////////////////////////

//Vector dot product
//A dot B
float MathLib::Vectors::Dot(VectorParent* A, VectorParent* B)
{
	if (A->dimension != B->dimension)
	{
		return _CRT_INT_MAX;
	}

	float result = 0.0;

	//Obtain unit information
	float* uA = new float[A->dimension];
	float* uB = new float[B->dimension];

	A->GetUnits(uA);
	B->GetUnits(uB);

	//Calculate dot product
	for (int i = 0; i < A->dimension; ++i)
	{
		result += uA[i] * uB[i];
	}

	delete[] uA;
	delete[] uB;

	return result;
}

//Vector length/magnitude
float MathLib::Vectors::Length(VectorParent* A)
{
	float result = 0.0;

	//Obtain unit information
	float* u = new float[A->dimension];
	
	A->GetUnits(u);

	//Calculate length
	for (int i = 0; i < A->dimension; ++i)
	{
		result += powf(u[i], 2);
	}

	result = sqrtf(result);

	delete[] u;

	return result;
}

//Vector normalization
void MathLib::Vectors::Normalize(VectorParent* A)
{
	//Obtain vector length
	float length = Length(A);

	//Obtain unit information
	float* u = new float[A->dimension];

	A->GetUnits(u);

	//Normalize vector units
	for (int i = 0; i < A->dimension; ++i)
	{
		u[i] /= length;
	}

	//Set unit information
	A->SetUnits(u);

	delete[] u;
}

//Vector scaling
void MathLib::Vectors::Scale(VectorParent* A, float amt)
{
	//Obtain unit information
	float* u = new float[A->dimension];

	A->GetUnits(u);

	//Scale vector units
	for (int i = 0; i < A->dimension; ++i)
	{
		u[i] *= amt;
	}

	//Set unit information
	A->SetUnits(u);

	delete[] u;
}

/////////////////////////////////////////////////////////
//Vector Math
/////////////////////////////////////////////////////////

//Vector addition
void MathLib::Vectors::Add(VectorParent* A, VectorParent* B)
{
	//Obtain unit information
	float* uA = new float[A->dimension];
	float* uB = new float[B->dimension];

	A->GetUnits(uA);
	B->GetUnits(uB);

	//Add vector units
	for (int i = 0; i < A->dimension; ++i)
	{
		uA[i] += uB[i];
	}

	//Set unit information
	A->SetUnits(uA);

	delete[] uA;
	delete[] uB;
}

//Vector comparison
bool MathLib::Vectors::Compare(VectorParent* A, VectorParent* B)
{
	if (A->dimension != B->dimension)
	{
		return false;
	}

	bool equals = true;

	//Obtain unit information
	float* uA = new float[A->dimension];
	float* uB = new float[B->dimension];

	A->GetUnits(uA);
	B->GetUnits(uB);

	//Compare vector units
	for (int i = 0; i < A->dimension; ++i)
	{
		//If any unit isn't equal, set false and break
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

//Vector equalization
void MathLib::Vectors::Equal(VectorParent* A, VectorParent* B)
{
	if (A->dimension != B->dimension)
	{
		return;
	}

	//Obtain unit information
	float* uA = new float[A->dimension];
	float* uB = new float[B->dimension];

	A->GetUnits(uA);
	B->GetUnits(uB);

	//Equalize vector units
	for (int i = 0; i < A->dimension; ++i)
	{
		uA[i] = uB[i];
	}

	//Set unit information
	A->SetUnits(uA);

	delete[] uA;
	delete[] uB;
}

//Vector subtraction
void MathLib::Vectors::Subtract(VectorParent* A, VectorParent* B)
{
	//Obtain unit information
	float* uA = new float[A->dimension];
	float* uB = new float[B->dimension];

	A->GetUnits(uA);
	B->GetUnits(uB);

	//Subtract vector units
	for (int i = 0; i < A->dimension; ++i)
	{
		uA[i] -= uB[i];
	}

	//Set unit information
	A->SetUnits(uA);

	delete[] uA;
	delete[] uB;
}