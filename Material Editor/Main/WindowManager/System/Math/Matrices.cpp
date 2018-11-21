#include "MathLib.h"

MathLib::Matrices::MatrixMxN::MatrixMxN(
	const MatrixMxN& other)
{
	m = other.m;
	n = other.n;
	container = other.container;
}

MathLib::Matrices::MatrixMxN::MatrixMxN(
	int m,
	int n)
{
	this->m = m;
	this->n = n;

	container = new double*[m];
	for (auto x = 0; x < m; ++x)
	{
		container[x] = new double[n];
	}

	for (auto y = 0; y < m; ++y)
	{
		for (auto x = 0; x < n; ++x)
		{
			container[y][x] = 0;
		}
	}
}

void MathLib::Matrices::MatrixMxN::Delete()
{
	m = n = 0;

	for (auto i = 0; i < m; ++i)
	{
		delete[] container[i];
	}

	delete[] container;

	container = 0;
}

int* MathLib::Matrices::MatrixMxN::GetDim()
{
	static int dim[2] = { m, n };

	return dim;
}

double MathLib::Matrices::MatrixMxN::GetVal(
	int x,
	int y)
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

void MathLib::Matrices::MatrixMxN::SetVal(
	int x,
	int y,
	double val)
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

MathLib::Matrices::MatrixSquare::MatrixSquare(
	const MatrixSquare& other)
{
	m = other.m;
	n = other.n;
	container = other.container;
}

MathLib::Matrices::MatrixSquare::MatrixSquare(
	int p)
{
	m = n = p;

	container = new double*[p];
	for (auto x = 0; x < p; ++x)
	{
		container[x] = new double[p];
	}

	for (auto y = 0; y < p; ++y)
	{
		for (auto x = 0; x < p; ++x)
		{
			container[y][x] = 0;
		}
	}
}

void MathLib::Matrices::MatrixSquare::Delete()
{
	m = n = 0;

	for (auto i = 0; i < m; ++i)
	{
		delete[] container[i];
	}

	delete[] container;

	container = 0;
}

int* MathLib::Matrices::MatrixSquare::GetDim()
{
	static int dim[2] = { m, n };

	return dim;
}

double MathLib::Matrices::MatrixSquare::GetVal(
	int x,
	int y)
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

void MathLib::Matrices::MatrixSquare::SetVal(
	int x,
	int y,
	double val)
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

MathLib::Matrices::MatrixParent* MathLib::Matrices::Dot(
	Matrices::MatrixParent* A,
	Matrices::MatrixParent* B)
{
	MatrixParent* newMatrix = 0;
	auto ax = A->GetDim()[1];
	auto ay = A->GetDim()[0];
	auto bx = B->GetDim()[1];
	auto by = B->GetDim()[0];

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
		return 0;
	}

	for (auto y = 0; y < ay; ++y)
	{
		for (auto x = 0; x < bx; ++x)
		{
			auto val = 0.0;

			for (auto same = 0; same < ay; ++same)
			{
				val += A->GetVal(same, y) * B->GetVal(x, same);
			}

			newMatrix->SetVal(x, y, val);
		}
	}

	return newMatrix;
}

void MathLib::Matrices::Scale(
	Matrices::MatrixParent* M,
	double& amt)
{
	for (auto y = 0; y < M->GetDim()[0]; ++y)
	{
		for (auto x = 0; x < M->GetDim()[1]; ++x)
		{
			M->SetVal(x, y, M->GetVal(x, y) * amt);
		}
	}
}

void MathLib::Matrices::Add(
	Matrices::MatrixParent* A,
	Matrices::MatrixParent* B)
{
	auto ax = A->GetDim()[1];
	auto ay = A->GetDim()[0];
	auto bx = B->GetDim()[1];
	auto by = B->GetDim()[0];

	if ((ax == bx) && (ay == by))
	{
		for (auto y = 0; y < ay; ++y)
		{
			for (auto x = 0; x < ax; ++x)
			{
				auto val = A->GetVal(x, y) + B->GetVal(x, y);
				A->SetVal(x, y, val);
			}
		}
	}
}

bool MathLib::Matrices::Compare(
	Matrices::MatrixParent* A,
	Matrices::MatrixParent* B)
{
	auto ax = A->GetDim()[1];
	auto ay = A->GetDim()[0];
	auto bx = B->GetDim()[1];
	auto by = B->GetDim()[0];

	if ((ax == bx) && (ay == by))
	{
		for (auto y = 0; y < ay; ++y)
		{
			for (auto x = 0; x < ax; ++x)
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

void MathLib::Matrices::Equal(
	Matrices::MatrixParent* A,
	Matrices::MatrixParent* B)
{
	auto ax = A->GetDim()[1];
	auto ay = A->GetDim()[0];
	auto bx = B->GetDim()[1];
	auto by = B->GetDim()[0];

	if ((ax == bx) && (ay == by))
	{
		for (auto y = 0; y < ay; ++y)
		{
			for (auto x = 0; x < ax; ++x)
			{
				A->SetVal(x, y, B->GetVal(x, y));
			}
		}
	}
}

void MathLib::Matrices::Subtract(
	Matrices::MatrixParent* A,
	Matrices::MatrixParent* B)
{
	auto ax = A->GetDim()[1];
	auto ay = A->GetDim()[0];
	auto bx = B->GetDim()[1];
	auto by = B->GetDim()[0];

	if ((ax == bx) && (ay == by))
	{
		for (auto y = 0; y < ay; ++y)
		{
			for (auto x = 0; x < ax; ++x)
			{
				auto val = A->GetVal(x, y) - B->GetVal(x, y);
				A->SetVal(x, y, val);
			}
		}
	}
}

MathLib::Matrices::MatrixSquare MathLib::Matrices::Zero_1D()
{
	auto id = MatrixSquare(1);

	id.SetVal(0, 0, 0.0);

	return id;
}

MathLib::Matrices::MatrixSquare MathLib::Matrices::Zero_2D()
{
	auto id = MatrixSquare(2);

	for (auto y = 0; y < 2; ++y)
	{
		for (auto x = 0; x < 2; ++x)
		{
			id.SetVal(x, y, 0.0);
		}
	}

	return id;
}

MathLib::Matrices::MatrixSquare MathLib::Matrices::Zero_3D()
{
	auto id = MatrixSquare(3);

	for (auto y = 0; y < 3; ++y)
	{
		for (auto x = 0; x < 3; ++x)
		{
			id.SetVal(x, y, 0.0);
		}
	}

	return id;
}

MathLib::Matrices::MatrixSquare MathLib::Matrices::Zero_4D()
{
	auto id = MatrixSquare(4);

	for (auto y = 0; y < 4; ++y)
	{
		for (auto x = 0; x < 4; ++x)
		{
			id.SetVal(x, y, 0.0);
		}
	}

	return id;
}

MathLib::Matrices::MatrixSquare MathLib::Matrices::One_2D()
{
	auto id = MatrixSquare(2);

	for (auto y = 0; y < 2; ++y)
	{
		for (auto x = 0; x < 2; ++x)
		{
			id.SetVal(x, y, 1.0);
		}
	}

	return id;
}

MathLib::Matrices::MatrixSquare MathLib::Matrices::One_3D()
{
	auto id = MatrixSquare(3);

	for (auto y = 0; y < 3; ++y)
	{
		for (auto x = 0; x < 3; ++x)
		{
			id.SetVal(x, y, 1.0);
		}
	}

	return id;
}

MathLib::Matrices::MatrixSquare MathLib::Matrices::One_4D()
{
	auto id = MatrixSquare(4);

	for (auto y = 0; y < 4; ++y)
	{
		for (auto x = 0; x < 4; ++x)
		{
			id.SetVal(x, y, 1.0);
		}
	}

	return id;
}

MathLib::Matrices::MatrixSquare MathLib::Matrices::Identity_1D()
{
	auto id = MatrixSquare(1);

	id.SetVal(0, 0, 1.0);

	return id;
}

MathLib::Matrices::MatrixSquare MathLib::Matrices::Identity_2D()
{
	auto id = MatrixSquare(2);

	for (auto i = 0; i < 2; ++i)
	{
		id.SetVal(i, i, 1.0);
	}

	return id;
}

MathLib::Matrices::MatrixSquare MathLib::Matrices::Identity_3D()
{
	auto id = MatrixSquare(3);

	for (auto i = 0; i < 3; ++i)
	{
		id.SetVal(i, i, 1.0);
	}

	return id;
}

MathLib::Matrices::MatrixSquare MathLib::Matrices::Identity_4D()
{
	auto id = MatrixSquare(4);

	for (auto i = 0; i < 4; ++i)
	{
		id.SetVal(i, i, 1.0);
	}

	return id;
}

MathLib::Matrices::MatrixSquare MathLib::Matrices::EulerX(
	double& r)
{
	//Rotation matrix for roll
	// 1    0    0    0
	// 0   cos -sin   0
	// 0   sin  cos   0
	// 0    0    0    1

	auto id = MatrixSquare(Identity_4D());

	id.SetVal(0, 0, 1.0);

	id.SetVal(1, 1, cos(r));
	id.SetVal(1, 2, -sin(r));

	id.SetVal(2, 1, sin(r));
	id.SetVal(2, 2, cos(r));

	return id;
}

MathLib::Matrices::MatrixSquare MathLib::Matrices::EulerY(
	double& r)
{
	//Rotation matrix for pitch
	//cos   0   sin   0
	//0     1    0    0
	//-sin  0   cos   0
	// 0    0    0    1

	auto id = MatrixSquare(Identity_4D());

	id.SetVal(0, 0, cos(r));
	id.SetVal(0, 2, sin(r));

	id.SetVal(1, 1, 1.0);

	id.SetVal(2, 0, -sin(r));
	id.SetVal(2, 2, cos(r));

	return id;
}

MathLib::Matrices::MatrixSquare MathLib::Matrices::EulerZ(
	double& r)
{
	//Rotation matrix for yaw
	//cos -sin   0    0
	//sin  cos   0    0
	// 0    0    1    0
	// 0    0    0    1

	auto id = MatrixSquare(Identity_4D());

	id.SetVal(0, 0, cos(r));
	id.SetVal(0, 1, -sin(r));

	id.SetVal(1, 0, sin(r));
	id.SetVal(1, 1, cos(r));

	id.SetVal(2, 2, 1.0);

	return id;
}