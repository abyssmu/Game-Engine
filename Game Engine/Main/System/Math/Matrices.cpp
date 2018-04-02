//Class Includes
#include "MathLib.h"

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
	//Create y arrays
	container = new float*[m];
	for (int x = 0; x < m; ++x)
	{
		//Create x arrays
		container[x] = new float[n];
	}

	//Set all values to 0
	for (int y = 0; y < m; ++y)
	{
		for (int x = 0; x < n; ++x)
		{
			container[y][x] = 0;
		}
	}
}


//Default destructor
MathLib::Matrices::MatrixMxN::~MatrixMxN()
{}

//Delete matrix and set to default
void MathLib::Matrices::MatrixMxN::Delete()
{
	m = n = 0;

	for (int i = 0; i < m; ++i)
	{
		delete[] container[i];
	}

	delete[] container;

	container = NULL;
}

//Get dimensions m, n
float* MathLib::Matrices::MatrixMxN::GetDim()
{
	float dim[2] = { m, n };

	return dim;
}

//Get value at x, y
float MathLib::Matrices::MatrixMxN::GetVal(int x, int y)
{
	if ((x > n) || (x < 0))
	{
		return _CRT_INT_MAX;
	}
	if ((y > m) || (y < 0))
	{
		return _CRT_INT_MAX;
	}

	return container[y][x];
}

//Set value at x, y to val
void MathLib::Matrices::MatrixMxN::SetVal(int x, int y, float val)
{
	if ((x > n) || (x < 0))
	{
		return;
	}
	if ((y > m) || (y < 0))
	{
		return;
	}
	
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
	//Create y arrays
	container = new float*[p];
	for (int x = 0; x < p; ++x)
	{
		//Create x arrays
		container[x] = new float[p];
	}

	//Set all values to 0
	for (int y = 0; y < p; ++y)
	{
		for (int x = 0; x < p; ++x)
		{
			container[y][x] = 0;
		}
	}
}

//Default destructor
MathLib::Matrices::MatrixSquare::~MatrixSquare()
{}

//Delete matrix and set to default
void MathLib::Matrices::MatrixSquare::Delete()
{
	m = n = 0;

	for (int i = 0; i < m; ++i)
	{
		delete[] container[i];
	}

	delete[] container;

	container = NULL;
}

//Get dimensions m, n
float* MathLib::Matrices::MatrixSquare::GetDim()
{
	float dim[2] = { m, n };

	return dim;
}

//Get value at x, y
float MathLib::Matrices::MatrixSquare::GetVal(int x, int y)
{
	if ((x > n) || (x < 0))
	{
		return _CRT_INT_MAX;
	}
	if ((y > m) || (y < 0))
	{
		return _CRT_INT_MAX;
	}

	return container[y][x];
}

//Set value at x, y to val
void MathLib::Matrices::MatrixSquare::SetVal(int x, int y, float val)
{
	if ((x > n) || (x < 0))
	{
		return;
	}
	if ((y > m) || (y < 0))
	{
		return;
	}

	container[y][x] = val;
}

/////////////////////////////////////////////////////////
//Matrix Operations
/////////////////////////////////////////////////////////

//Calculate matrix dot product
//A dot B
MathLib::Matrices::MatrixParent* MathLib::Matrices::Dot(
												Matrices::MatrixParent* A,
												Matrices::MatrixParent* B)
{
	MatrixParent* newMatrix = NULL;
	int ax, ay, bx, by;
	ax = A->GetDim()[1];
	ay = A->GetDim()[0];
	bx = B->GetDim()[1];
	by = B->GetDim()[0];

	if ((ax == ay) && (bx == by) && (ax == bx))
	{
		newMatrix = new MatrixSquare(ax);
	}
	else if (ax == by)
	{
		newMatrix = new MatrixMxN(ay, bx);
	}
	else
	{
		return NULL;
	}

	for (int y = 0; y < ay; ++y)
	{
		for (int x = 0; x < bx; ++x)
		{
			float val = 0.0;

			for (int same = 0; same < ay; ++same)
			{
				val += A->GetVal(same, y) * B->GetVal(x, same);
			}

			newMatrix->SetVal(x, y, val);
		}
	}

	return newMatrix;
}

//Scale matrix M by amt
void MathLib::Matrices::Scale(Matrices::MatrixParent* M, float amt)
{
	for (int y = 0; y < M->GetDim()[0]; ++y)
	{
		for (int x = 0; x < M->GetDim()[1]; ++x)
		{
			M->SetVal(x, y, M->GetVal(x, y) * amt);
		}
	}
}

/////////////////////////////////////////////////////////
//Matrix Math
/////////////////////////////////////////////////////////

//Matrix addition
//A + B
void MathLib::Matrices::Add(Matrices::MatrixParent* A,
							Matrices::MatrixParent* B)
{
	float ax, ay, bx, by;
	ax = A->GetDim()[1];
	ay = A->GetDim()[0];
	bx = B->GetDim()[1];
	by = B->GetDim()[0];

	if ((ax == bx) && (ay == by))
	{
		for (int y = 0; y < ay; ++y)
		{
			for (int x = 0; x < ax; ++x)
			{
				float val = A->GetVal(x, y) + B->GetVal(x, y);
				A->SetVal(x, y, val);
			}
		}
	}
}

//Matrix comparison
//A == B
bool MathLib::Matrices::Compare(Matrices::MatrixParent* A,
								Matrices::MatrixParent* B)
{
	float ax, ay, bx, by;
	ax = A->GetDim()[1];
	ay = A->GetDim()[0];
	bx = B->GetDim()[1];
	by = B->GetDim()[0];

	if ((ax == bx) && (ay == by))
	{
		for (int y = 0; y < ay; ++y)
		{
			for (int x = 0; x < ax; ++x)
			{
				if (A->GetVal(x, y) != B->GetVal(x, y))
				{
					return false;
				}
			}
		}
	}

	return true;
}

//Matrix equalization
//A = B
void MathLib::Matrices::Equal(Matrices::MatrixParent* A,
							Matrices::MatrixParent* B)
{
	float ax, ay, bx, by;
	ax = A->GetDim()[1];
	ay = A->GetDim()[0];
	bx = B->GetDim()[1];
	by = B->GetDim()[0];

	if ((ax == bx) && (ay == by))
	{
		for (int y = 0; y < ay; ++y)
		{
			for (int x = 0; x < ax; ++x)
			{
				A->SetVal(x, y, B->GetVal(x, y));
			}
		}
	}
}

//Matrix subtraction
//A - B
void MathLib::Matrices::Subtract(Matrices::MatrixParent* A,
								Matrices::MatrixParent* B)
{
	float ax, ay, bx, by;
	ax = A->GetDim()[1];
	ay = A->GetDim()[0];
	bx = B->GetDim()[1];
	by = B->GetDim()[0];

	if ((ax == bx) && (ay == by))
	{
		for (int y = 0; y < ay; ++y)
		{
			for (int x = 0; x < ax; ++x)
			{
				float val = A->GetVal(x, y) - B->GetVal(x, y);
				A->SetVal(x, y, val);
			}
		}
	}
}

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

	MatrixSquare id(1);

	id.SetVal(0, 0, 0.0);

	return id;
}

//Return 2D zero matrix
MathLib::Matrices::MatrixSquare MathLib::Matrices::Zero_2D()
{
	//{ 0, 0 }
	//{ 0, 0 }

	MatrixSquare id(2);

	for (int y = 0; y < 2; ++y)
	{
		for (int x = 0; x < 2; ++x)
		{
			id.SetVal(x, y, 0.0);
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

	MatrixSquare id(3);

	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 3; ++x)
		{
			id.SetVal(x, y, 0.0);
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

	MatrixSquare id(4);

	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 4; ++x)
		{
			id.SetVal(x, y, 0.0);
		}
	}

	return id;
}

//Return 2D matrix of ones
MathLib::Matrices::MatrixSquare MathLib::Matrices::One_2D()
{
	//{ 1, 1 }
	//{ 1, 1 }

	MatrixSquare id(2);

	for (int y = 0; y < 2; ++y)
	{
		for (int x = 0; x < 2; ++x)
		{
			id.SetVal(x, y, 1.0);
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

	MatrixSquare id(3);

	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 3; ++x)
		{
			id.SetVal(x, y, 1.0);
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

	MatrixSquare id(4);

	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 4; ++x)
		{
			id.SetVal(x, y, 1.0);
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

	MatrixSquare id(1);

	id.SetVal(0, 0, 1.0);

	return id;
}

//Return 2D identity matrix
MathLib::Matrices::MatrixSquare MathLib::Matrices::Identity_2D()
{
	//{ 1, 0 }
	//{ 0, 1 }

	MatrixSquare id(2);

	for (int i = 0; i < 2; ++i)
	{
		id.SetVal(i, i, 1.0);
	}

	return id;
}

//Return 3D identity matrix
MathLib::Matrices::MatrixSquare MathLib::Matrices::Identity_3D()
{
	//{ 1, 0, 0 }
	//{ 0, 1, 0 }
	//{ 0, 0, 1 }

	MatrixSquare id(3);

	for (int i = 0; i < 3; ++i)
	{
		id.SetVal(i, i, 1.0);
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

	MatrixSquare id(4);

	for (int i = 0; i < 4; ++i)
	{
		id.SetVal(i, i, 1.0);
	}

	return id;
}

/////////////////////////////////////////////////////////
//Rotation Matrix Constants
/////////////////////////////////////////////////////////

//Calculate and return 4x4 rotation matrix about x axis by r radians
MathLib::Matrices::MatrixSquare MathLib::Matrices::EulerX(float r)
{
	//Rotation matrix for roll
	// 1    0    0    0
	// 0   cos -sin   0
	// 0   sin  cos   0
	// 0    0    0    1

	MatrixSquare id(Identity_4D());

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

//Calculate and return 4x4 rotation matrix about y axis by r radians
MathLib::Matrices::MatrixSquare MathLib::Matrices::EulerY(float r)
{
	//Rotation matrix for pitch
	//cos   0   sin   0
	//0     1    0    0
	//-sin  0   cos   0
	// 0    0    0    1

	MatrixSquare id(Identity_4D());

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

//Calculate and return 4x4 rotation matrix about z axis by r radians
MathLib::Matrices::MatrixSquare MathLib::Matrices::EulerZ(float r)
{
	//Rotation matrix for yaw
	//cos -sin   0    0
	//sin  cos   0    0
	// 0    0    1    0
	// 0    0    0    1

	MatrixSquare id(Identity_4D());

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