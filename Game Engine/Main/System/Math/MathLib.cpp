#include "MathLib.h"

/////////////////////////////////////////////////////////
//Matrices
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
//Matrix NxM
/////////////////////////////////////////////////////////

//Constructor
MathLib::Matrices::MatrixMxN::MatrixMxN()
{
	m = n = 0;
	container = NULL;
}

//Copy constructor
MathLib::Matrices::MatrixMxN::MatrixMxN(const MatrixMxN& other)
{
	m = other.m;
	n = other.n;
	container = other.container;
}

//M x N dimension constructor
MathLib::Matrices::MatrixMxN::MatrixMxN(int m, int n)
{
	this->m = m;
	this->n = n;
	
	//Create matrix arrays
	container = new float*[m];
	for (int i = 0; i < m; ++i)
	{
		container[i] = new float[n];
	}

	//Set all values to 0
	for (int i = 0; i < m; ++i)
	{
		for (int k = 0; k < n; ++k)
		{
			container[i][k] = 0;
		}
	}
}

//Default destructor
MathLib::Matrices::MatrixMxN::~MatrixMxN()
{}

//Get value at x, y
float MathLib::Matrices::MatrixMxN::GetVal(int x, int y)
{
	return container[y][x];
}

//Set value at x, y to val
void MathLib::Matrices::MatrixMxN::SetVal(int x, int y, float val)
{
	container[y][x] = val;
}

/////////////////////////////////////////////////////////
//Matrix Square
/////////////////////////////////////////////////////////

//Constructor
MathLib::Matrices::MatrixSquare::MatrixSquare()
{
	m = n = 0;
	container = NULL;
}

//Copy constructor
MathLib::Matrices::MatrixSquare::MatrixSquare(const MatrixSquare& other)
{
	m = other.m;
	n = other.n;
	container = other.container;
}

//P dimension constructor
MathLib::Matrices::MatrixSquare::MatrixSquare(int p)
{
	m = n = p;

	//Create matrix arrays
	container = new float*[p];
	for (int i = 0; i < p; ++i)
	{
		container[i] = new float[p];
	}

	//Set all values to 0
	for (int i = 0; i < p; ++i)
	{
		for (int k = 0; k < p; ++k)
		{
			container[i][k] = 0;
		}
	}
}

//Default destructor
MathLib::Matrices::MatrixSquare::~MatrixSquare()
{}

//Get value at x, y
float MathLib::Matrices::MatrixSquare::GetVal(int x, int y)
{
	return container[y][x];
}

//Set value at x, y to val
void MathLib::Matrices::MatrixSquare::SetVal(int x, int y, float val)
{
	container[y][x] = val;
}

/////////////////////////////////////////////////////////
//Matrix Operations
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
//Matrix Math
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
//Matrix Constants
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
//Numerical Matrix Constants
/////////////////////////////////////////////////////////

//Return 1D zero matrix
MathLib::Matrices::MatrixSquare MathLib::Matrices::Zero_1D()
{
	//{ 0 }

	MatrixSquare id = MatrixSquare(1);

	id.SetVal(0, 0, 0.0);

	return id;
}

//Return 2D zero matrix
MathLib::Matrices::MatrixSquare MathLib::Matrices::Zero_2D()
{
	//{ 0, 0 }
	//{ 0, 0 }

	MatrixSquare id = MatrixSquare(2);

	for (int i = 0; i < 2; ++i)
	{
		for (int k = 0; k < 2; ++k)
		{
			id.SetVal(k, i, 0.0f);
		}
	}

	return id;
}

//Return 3D zero matrix
MathLib::Matrices::MatrixSquare MathLib::Matrices::Zero_3D()
{
	//{ 0, 0, 0 }
	//{ 0, 0, 0 }
	//{ 0, 0, 0 }

	MatrixSquare id = MatrixSquare(3);

	for (int i = 0; i < 3; ++i)
	{
		for (int k = 0; k < 3; ++k)
		{
			id.SetVal(k, i, 0.0f);
		}
	}

	return id;
}

//Return 4D zero matrix
MathLib::Matrices::MatrixSquare MathLib::Matrices::Zero_4D()
{
	//{ 0, 0, 0, 0 }
	//{ 0, 0, 0, 0 }
	//{ 0, 0, 0, 0 }
	//{ 0, 0, 0, 0 }

	MatrixSquare id = MatrixSquare(4);

	for (int i = 0; i < 4; ++i)
	{
		for (int k = 0; k < 4; ++k)
		{
			id.SetVal(k, i, 0.0f);
		}
	}

	return id;
}

//Return 2D matrix of ones
MathLib::Matrices::MatrixSquare MathLib::Matrices::One_2D()
{
	//{ 1, 1 }
	//{ 1, 1 }

	MatrixSquare id = MatrixSquare(2);

	for (int i = 0; i < 2; ++i)
	{
		for (int k = 0; k < 2; ++k)
		{
			id.SetVal(k, i, 1.0f);
		}
	}

	return id;
}

//Return 3D matrix of ones
MathLib::Matrices::MatrixSquare MathLib::Matrices::One_3D()
{
	//{ 1, 1, 1 }
	//{ 1, 1, 1 }
	//{ 1, 1, 1 }

	MatrixSquare id = MatrixSquare(3);

	for (int i = 0; i < 3; ++i)
	{
		for (int k = 0; k < 3; ++k)
		{
			id.SetVal(k, i, 1.0f);
		}
	}

	return id;
}

//Return 4D matrix of ones
MathLib::Matrices::MatrixSquare MathLib::Matrices::One_4D()
{
	//{ 1, 1, 1, 1 }
	//{ 1, 1, 1, 1 }
	//{ 1, 1, 1, 1 }
	//{ 1, 1, 1, 1 }

	MatrixSquare id = MatrixSquare(4);

	for (int i = 0; i < 4; ++i)
	{
		for (int k = 0; k < 4; ++k)
		{
			id.SetVal(k, i, 1.0f);
		}
	}

	return id;
}

/////////////////////////////////////////////////////////
//Identity Matrix Constants
/////////////////////////////////////////////////////////

//Return 1D identity matrix
MathLib::Matrices::MatrixSquare MathLib::Matrices::Identity_1D()
{
	//{ 1 }

	MatrixSquare id = MatrixSquare(1);
	
	id.SetVal(0, 0, 1.0);

	return id;
}

//Return 2D identity matrix
MathLib::Matrices::MatrixSquare MathLib::Matrices::Identity_2D()
{
	//{ 1, 0 }
	//{ 0, 1 }

	MatrixSquare id = MatrixSquare(2);

	for (int i = 0; i < 2; ++i)
	{
		id.SetVal(i, i, 1.0f);
	}

	return id;
}

//Return 3D identity matrix
MathLib::Matrices::MatrixSquare MathLib::Matrices::Identity_3D()
{
	//{ 1, 0, 0 }
	//{ 0, 1, 0 }
	//{ 0, 0, 1 }

	MatrixSquare id = MatrixSquare(3);

	for (int i = 0; i < 3; ++i)
	{
		id.SetVal(i, i, 1.0f);
	}

	return id;
}

//Return 4D identity matrix
MathLib::Matrices::MatrixSquare MathLib::Matrices::Identity_4D()
{
	//{ 1, 0, 0, 0 }
	//{ 0, 1, 0, 0 }
	//{ 0, 0, 1, 0 }
	//{ 0, 0, 0, 1 }

	MatrixSquare id = MatrixSquare(4);

	for (int i = 0; i < 4; ++i)
	{
		id.SetVal(i, i, 1.0f);
	}

	return id;
}

/////////////////////////////////////////////////////////
//Rotation Matrix Constants
/////////////////////////////////////////////////////////

//Calculate and return rotation matrix about x axis by r radians
MathLib::Matrices::MatrixSquare MathLib::Matrices::EulerX(float r)
{
	//Rotation matrix for roll
	// 1    0    0
	// 0   cos -sin
	// 0   sin  cos

	MatrixSquare id = Zero_3D();

	//Row 1
	id.SetVal(0, 0, 1.0);

	//Row 2
	id.SetVal(1, 1, cosf(r));
	id.SetVal(1, 2, -sinf(r));

	//Row 3
	id.SetVal(2, 1, sinf(r));
	id.SetVal(2, 2, cosf(r));

	return id;
}

//Calculate and return rotation matrix about y axis by r radians
MathLib::Matrices::MatrixSquare MathLib::Matrices::EulerY(float r)
{
	//Rotation matrix for pitch
	//cos   0   sin
	//0     1    0
	//-sin  0   cos

	MatrixSquare id = Zero_3D();

	//Row 1
	id.SetVal(0, 0, cosf(r));
	id.SetVal(0, 2, sinf(r));

	//Row 2
	id.SetVal(1, 1, 1.0);

	//Row 3
	id.SetVal(2, 0, -sinf(r));
	id.SetVal(2, 2, cosf(r));

	return id;
}

//Calculate and return rotation matrix about z axis by r radians
MathLib::Matrices::MatrixSquare MathLib::Matrices::EulerZ(float r)
{
	//Rotation matrix for yaw
	//cos -sin   0
	//sin  cos   0
	// 0    0    1

	MatrixSquare id = Zero_3D();

	//Row 1
	id.SetVal(0, 0, cosf(r));
	id.SetVal(0, 1, -sinf(r));

	//Row 2
	id.SetVal(1, 0, sinf(r));
	id.SetVal(1, 1, cosf(r));

	//Row 3
	id.SetVal(2, 2, 1.0);

	return id;
}

/////////////////////////////////////////////////////////
//Quaternions
/////////////////////////////////////////////////////////

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
	x = 0;
	y = 0;
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

//Return unit x vector
MathLib::Vectors::Vector2D MathLib::Vectors::Vector2D::UnitX()
{
	return Vector2D(1.0, 0.0);
}

//Return unit y vector
MathLib::Vectors::Vector2D MathLib::Vectors::Vector2D::UnitY()
{
	return Vector2D(0.0, 1.0);
}

//Return vector of ones
MathLib::Vectors::Vector2D MathLib::Vectors::Vector2D::One()
{
	return Vector2D(1.0, 1.0);
}

//Return zero vector
MathLib::Vectors::Vector2D MathLib::Vectors::Vector2D::Zero()
{
	return Vector2D(0.0, 0.0);
}

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
	x = 0;
	y = 0;
	z = 0;
}

//Create 3D vector from 2D
//Initialize z = 0
MathLib::Vectors::Vector3D::Vector3D(const Vector2D& other)
{
	dimension = 3;
	x = other.x;
	y = other.y;
	z = 0;
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

//Return unit x vector
MathLib::Vectors::Vector3D MathLib::Vectors::Vector3D::UnitX()
{
	return Vector3D(1.0, 0.0, 0.0);
}

//Return unit y vector
MathLib::Vectors::Vector3D MathLib::Vectors::Vector3D::UnitY()
{
	return Vector3D(0.0, 1.0, 0.0);
}

//Return unit z vector
MathLib::Vectors::Vector3D MathLib::Vectors::Vector3D::UnitZ()
{
	return Vector3D(0.0, 0.0, 1.0);
}

//Return vector of ones
MathLib::Vectors::Vector3D MathLib::Vectors::Vector3D::One()
{
	return Vector3D(1.0, 1.0, 1.0);
}

//Return zero vector
MathLib::Vectors::Vector3D MathLib::Vectors::Vector3D::Zero()
{
	return Vector3D(0.0, 0.0, 0.0);
}

//Vector cross product
//A(this) cross B
MathLib::Vectors::Vector3D MathLib::Vectors::Vector3D::Cross(Vector3D B)
{
	Vector3D result = result.Zero();

	result.x = (this->y * B.z) - (this->z * B.y);
	result.y = (this->z * B.x) - (this->x * B.z);
	result.z = (this->x * B.y) - (this->y * B.x);

	return result;
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
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

//Create 4D vector from 2D
//Initialize z = 0, w = 0
MathLib::Vectors::Vector4D::Vector4D(const Vector2D& other)
{
	dimension = 4;
	x = other.x;
	y = other.y;
	z = 0;
	w = 0;
}

//Create 4D vector from 3D
//Initialize w = 0
MathLib::Vectors::Vector4D::Vector4D(const Vector3D& other)
{
	dimension = 4;
	x = other.x;
	y = other.y;
	z = other.z;
	w = 0;
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
MathLib::Vectors::Vector4D::Vector4D(float x, float y, float z,
									float w)
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

//Return unit x vector
MathLib::Vectors::Vector4D MathLib::Vectors::Vector4D::UnitX()
{
	return Vector4D(1.0, 0.0, 0.0, 0.0);
}

//Return unit y vector
MathLib::Vectors::Vector4D MathLib::Vectors::Vector4D::UnitY()
{
	return Vector4D(0.0, 1.0, 0.0, 0.0);
}

//Return unit z vector
MathLib::Vectors::Vector4D MathLib::Vectors::Vector4D::UnitZ()
{
	return Vector4D(0.0, 0.0, 1.0, 0.0);
}

//Return unit w vector
MathLib::Vectors::Vector4D MathLib::Vectors::Vector4D::UnitW()
{
	return Vector4D(0.0, 0.0, 0.0, 1.0);
}

//Return vector of ones
MathLib::Vectors::Vector4D MathLib::Vectors::Vector4D::One()
{
	return Vector4D(1.0, 1.0, 1.0, 1.0);
}

//Return zero vector
MathLib::Vectors::Vector4D MathLib::Vectors::Vector4D::Zero()
{
	return Vector4D(0.0, 0.0, 0.0, 0.0);
}

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
	w = units[4];
}

/////////////////////////////////////////////////////////
//Vector Operations
/////////////////////////////////////////////////////////

//Vector dot product
//A dot B
float MathLib::Vectors::Dot(VectorParent* A, VectorParent* B)
{
	float result = 0.0f;

	//Obtain unit information from incoming vectors
	float* unitsA = new float[A->dimension];
	float* unitsB = new float[B->dimension];

	A->GetUnits(unitsA);
	B->GetUnits(unitsB);

	//Calculate dot product
	for (int i = 0; i < A->dimension; ++i)
	{
		result += unitsA[i] * unitsB[i];
	}

	delete[] unitsA;
	delete[] unitsB;

	return result;
}

//Vector length/magnitude
float MathLib::Vectors::Length(VectorParent* A)
{
	float result = 0.0f;

	//Obtain unit information from incoming vector
	float* units = new float[A->dimension];
	A->GetUnits(units);

	//Calculate length of vector
	for (int i = 0; i < A->dimension; ++i)
	{
		result += powf(units[i], 2);
	}

	result = sqrtf(result);

	delete[] units;

	return result;
}

//Vector normalization
void MathLib::Vectors::Normalize(VectorParent* A)
{
	//Obtain vector length
	float length = Length(A);

	//Obtain unit information from incoming vector
	float* units = new float[A->dimension];
	A->GetUnits(units);

	//Normalize vector
	for (int i = 0; i < A->dimension; ++i)
	{
		units[i] /= length;
	}

	//Set unit information of incoming vector
	A->SetUnits(units);

	delete[] units;
}

//Vector scaling
void MathLib::Vectors::Scale(VectorParent* A, float amt)
{
	//Obtain unit information from incoming vector
	float* units = new float[A->dimension];
	A->GetUnits(units);

	//Scale vector
	for (int i = 0; i < A->dimension; ++i)
	{
		units[i] *= amt;
	}

	//Set unit information of incoming vector
	A->SetUnits(units);

	delete[] units;
}

/////////////////////////////////////////////////////////
//Vector Math
/////////////////////////////////////////////////////////

//Vector addition
void MathLib::Vectors::Add(VectorParent& lhs, VectorParent& rhs)
{
	//Obtain unit information from incoming vectors
	float* unitsL = new float[lhs.dimension];
	float* unitsR = new float[rhs.dimension];

	lhs.GetUnits(unitsL);
	rhs.GetUnits(unitsR);

	//Add rhs to lhs
	for (int i = 0; i < lhs.dimension; ++i)
	{
		unitsL[i] += unitsR[i];
	}

	//Set unit information of incoming vector
	lhs.SetUnits(unitsL);

	delete[] unitsL;
	delete[] unitsR;
}

//Vector comparison
bool MathLib::Vectors::Compare(VectorParent& A, VectorParent& B)
{
	bool equals = true;

	//Obtain unit information from incoming vectors
	float* unitsA = new float[A.dimension];
	float* unitsB = new float[B.dimension];

	A.GetUnits(unitsA);
	B.GetUnits(unitsB);

	//Compare vector units
	for (int i = 0; i < A.dimension; ++i)
	{
		//If any unit isn't equal, set false and break
		if (unitsA[i] != unitsB[i])
		{
			equals = false;
			break;
		}
	}

	delete[] unitsA;
	delete[] unitsB;

	return equals;
}

//Vector equalization
void MathLib::Vectors::Equal(VectorParent& lhs, VectorParent& rhs)
{
	//Obtain unit information from incoming vectors
	float* unitsL = new float[lhs.dimension];
	float* unitsR = new float[rhs.dimension];

	lhs.GetUnits(unitsL);
	rhs.GetUnits(unitsR);

	//Set lhs equal to rhs
	for (int i = 0; i < lhs.dimension; ++i)
	{
		unitsL[i] = unitsR[i];
	}

	//Set unit information of incoming vector
	lhs.SetUnits(unitsL);

	delete[] unitsL;
	delete[] unitsR;
}

//Vector subtraction
void MathLib::Vectors::Subtract(VectorParent& lhs, VectorParent& rhs)
{
	//Obtain unit information from incoming vectors
	float* unitsL = new float[lhs.dimension];
	float* unitsR = new float[rhs.dimension];

	lhs.GetUnits(unitsL);
	rhs.GetUnits(unitsR);

	//Subtract rhs from lhs
	for (int i = 0; i < lhs.dimension; ++i)
	{
		unitsL[i] -= unitsR[i];
	}

	//Set unit information of incoming vector
	lhs.SetUnits(unitsL);

	delete[] unitsL;
	delete[] unitsR;
}

/////////////////////////////////////////////////////////
//Math Operations
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
//Conversions
/////////////////////////////////////////////////////////

//Create 3D vector from 4D
MathLib::Vectors::Vector3D MathLib::Convert4Dto3D(Vectors::Vector4D V)
{
	Vectors::Vector3D hold = hold.Zero();

	hold.x = V.x;
	hold.y = V.y;
	hold.z = V.z;

	return hold;
}

/////////////////////////////////////////////////////////
//Math
/////////////////////////////////////////////////////////

//Calculate dot product of 3D matrix M and 3D vector V
MathLib::Vectors::Vector3D MathLib::Vector3D_Dot_Matrix3x3(
												Vectors::Vector3D V,
												Matrices::MatrixSquare M)
{
	//{ , , , }	  { , }	  { , }
	//{ , , , } * { , } = { , }
	//{ , , , }	  { , }	  { , }

	Vectors::Vector3D hold = hold.Zero();

	hold.x = M.GetVal(0, 0) * V.x +
		M.GetVal(1, 0) * V.y +
		M.GetVal(2, 0) * V.z;

	hold.y = M.GetVal(0, 1) * V.x +
		M.GetVal(1, 1) * V.y +
		M.GetVal(2, 1) * V.z;

	hold.z = M.GetVal(0, 2) * V.x +
		M.GetVal(1, 2) * V.y +
		M.GetVal(2, 2) * V.z;

	return hold;
}

/////////////////////////////////////////////////////////
//Rotations
/////////////////////////////////////////////////////////

//Rotate vector V about x axis by r radians
MathLib::Vectors::Vector3D MathLib::RotateEulerX(Vectors::Vector3D V,
												float r)
{
	Matrices::MatrixSquare EulerX = Matrices::EulerX(r);

	return Vector3D_Dot_Matrix3x3(V, EulerX);
}

//Rotate vector V about y axis by r radians
MathLib::Vectors::Vector3D MathLib::RotateEulerY(Vectors::Vector3D V,
												float r)
{
	Matrices::MatrixSquare EulerY = Matrices::EulerY(r);

	return Vector3D_Dot_Matrix3x3(V, EulerY);
}

//Rotate vector V about z axis by r radians
MathLib::Vectors::Vector3D MathLib::RotateEulerZ(Vectors::Vector3D V,
												float r)
{
	Matrices::MatrixSquare EulerZ = Matrices::EulerZ(r);

	return Vector3D_Dot_Matrix3x3(V, EulerZ);
}