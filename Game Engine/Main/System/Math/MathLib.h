/*
Math library contains classes for matrices (both mxn and square), quaternions, and vectors (2D, 3D, and 4D).
All have corresponding abstract parent classes along with common constants, operations, and math functions.
Numeric constants and conversion constants are also included.
*/

#pragma once

//Includes
#include <math.h>

//Math namespace
/*
Current data held:
	Numeric Constants
	Matrices
	Matrix Constants
	Matrix Operations
	Matrix Math
	Quaternions
	Quaternion Constants
	Quaternion Operations
	Quaternion Math
	Vectors
	Vector Constants
	Vector Operations
	Vector Math
	Math Operations
*/

namespace MathLib
{
	////////Numeric Constants
	const double PI		= 3.141592653589793;
	const double RADIAN	= PI / 180;

	////////Matrices
	namespace Matrices
	{
		//Matrix container
		class MatrixParent
		{
		public:
			//Default constructor
			MatrixParent() {}

			//Default copy constructor
			MatrixParent(const MatrixParent& other) {}

			//Default destructor
			~MatrixParent() {}

			////////Utility Functions
			//Delete matrix and set to default
			virtual void Delete() = 0;

			//Get dimensions m, n
			virtual int* GetDim() = 0;

			//Get value at x, y
			virtual double GetVal(int x, int y) = 0;

			//Set value at x, y to val
			virtual void SetVal(int x, int y, double val) = 0;
		};

		//Matrix of M by N dimensions
		class MatrixMxN : public MatrixParent
		{
		public:
			//Constructor
			MatrixMxN();
			
			//Copy constructor
			MatrixMxN(const MatrixMxN& other);
			
			//M x N dimension constructor
			MatrixMxN(int m, int n);

			//Default destructor
			~MatrixMxN();

			////////Utility Functions
			//Delete matrix and set to default
			void Delete();

			//Get dimensions m, n
			int* GetDim();

			//Get value at x, y
			double GetVal(int x, int y);

			//Set value at x, y to val
			void SetVal(int x, int y, double val);

		private:
			////////Main Variables
			int m, n;
			double** container;
		};

		//Matrix of M by M dimensions
		class MatrixSquare : public MatrixParent
		{
		public:
			//Constructor
			MatrixSquare();

			//Copy constructor
			MatrixSquare(const MatrixSquare& other);

			//P dimension constructor
			MatrixSquare(int p);

			//Default destructor
			~MatrixSquare();

			////////Utility Functions
			//Delete matrix and set to default
			void Delete();

			//Get dimensions m, n
			int* GetDim();

			//Get value at x, y
			double GetVal(int x, int y);

			//Set value at x, y to val
			void SetVal(int x, int y, double val);

		private:
			////////Utility Variables
			int m, n;
			double** container;
		};

		////////Matrix Constants
		////////Numerical Matrix Constants
		//Return square zero matrix
		MatrixSquare Zero_1D();
		MatrixSquare Zero_2D();
		MatrixSquare Zero_3D();
		MatrixSquare Zero_4D();

		//Return square matrix of ones
		MatrixSquare One_2D();
		MatrixSquare One_3D();
		MatrixSquare One_4D();

		////////Identity Matrix Constants
		//Return identity matrix
		MatrixSquare Identity_1D();
		MatrixSquare Identity_2D();
		MatrixSquare Identity_3D();
		MatrixSquare Identity_4D();

		////////Rotation Matrix Constants
		//Calculate and return 4x4 rotation matrix about axis by r radians
		MatrixSquare EulerX(double r);
		MatrixSquare EulerY(double r);
		MatrixSquare EulerZ(double r);

		////////Matrix Operation Functions
		//Calculate matrix dot product
		//Can return 0
		//A dot B
		MatrixParent* Dot(MatrixParent* A, MatrixParent* B);

		//Scale matrix M by amt
		void Scale(MatrixParent* M, double amt);

		////////Matrix Math
		//Matrix addition
		//A + B
		void Add(MatrixParent* A, MatrixParent* B);

		//Matrix comparison
		//A == B
		bool Compare(MatrixParent* A, MatrixParent* B);

		//Matrix equalization
		//A = B
		void Equal(MatrixParent* A, MatrixParent* B);

		//Matrix subtraction
		//A - B
		void Subtract(MatrixParent* A, MatrixParent* B);
	}

	////////Quaternions
	namespace Quaternions
	{
		
	}

	////////Quaternion Constants

	////////Quaternion Operation Functions

	////////Quaternion Math

	////////Vectors
	namespace Vectors
	{
		//Vector container
		class VectorParent
		{
		public:
			//Default constructor
			VectorParent() {}
			
			//Default copy constructor
			VectorParent(const VectorParent& other) {}

			//Default destructor
			~VectorParent() {}

			////////Utility Functions
			//Get vector units
			virtual void GetUnits(double* units) = 0;
			
			//Set vector units
			virtual void SetUnits(double* units) = 0;

			////////Utility Variables
			int dimension;
			double x, y, z, w;
		};

		//2D vector
		class Vector2D : public VectorParent
		{
		public:
			//Constructor
			Vector2D();

			//Copy constructor
			Vector2D(const Vector2D& other);

			//Unit constructor
			Vector2D(double x, double y);
			
			//Default destructor
			~Vector2D();

		private:
			////////Utility Functions
			//Get vector units
			void GetUnits(double* units);
			
			//Set vector units
			void SetUnits(double* units);
		};

		//3D vector
		class Vector3D : public VectorParent
		{
		public:
			//Constructor
			Vector3D();

			//Create 3D vector from 2D
			//Initialize z = 0
			Vector3D(const Vector2D& other);

			//Copy constructor
			Vector3D(const Vector3D& other);

			//Unit constructor
			Vector3D(double x, double y, double z);
			
			//Default destructor
			~Vector3D();

			////////Math Functions
			//Calculate cross product
			//A(this) cross B
			VectorParent* Cross(VectorParent* B);

		private:
			////////Utility Functions
			//Get vector units
			void GetUnits(double* units);

			//Set vector units
			void SetUnits(double* units);
		};

		//4D vector
		class Vector4D : public VectorParent
		{
		public:
			//Constructor
			Vector4D();

			//Create 4D vector from 2D
			//Initialize z = 0, w = 0
			Vector4D(const Vector2D& other);

			//Create 4D vector from 3D
			//Initialize w = 0
			Vector4D(const Vector3D& other);
			
			//Copy constructor
			Vector4D(const Vector4D& other);
			
			//Unit constructor
			Vector4D(double x, double y, double z, double w);
			
			//Default destructor
			~Vector4D();

		private:
			////////Utility Functions
			//Get vector units
			void GetUnits(double* units);

			//Set vector units
			void SetUnits(double* units);
		};

		////////Vector Constants
		//Return unit x vector
		Vector2D UnitX_2D();
		Vector3D UnitX_3D();
		Vector4D UnitX_4D();

		//Return unit y vector
		Vector2D UnitY_2D();
		Vector3D UnitY_3D();
		Vector4D UnitY_4D();

		Vector3D UnitZ_3D();
		Vector4D UnitZ_4D();

		Vector4D UnitW_4D();
		
		//Return vector of ones
		Vector2D One_2D();
		Vector3D One_3D();
		Vector4D One_4D();

		//Return zero vector
		Vector2D Zero_2D();
		Vector3D Zero_3D();
		Vector4D Zero_4D();

		////////Vector Operation Functions
		//Calculate dot product
		//A dot B
		double Dot(VectorParent* A, VectorParent* B);

		//Calculate length of V
		double Length(VectorParent* V);

		//Normalize V
		void Normalize(VectorParent* V);

		//Scale V by amt
		void Scale(VectorParent* V, double amt);

		////////Vector Math Functions
		//Vector addition
		//A + B
		void Add(VectorParent* A, VectorParent* B);

		//Vector comparison
		//A == B
		bool Compare(VectorParent* A, VectorParent* B);

		//Vector equalization
		//A = B
		void Equal(VectorParent* A, VectorParent* B);

		//Vector subtraction
		//A - B
		void Subtract(VectorParent* A, VectorParent* B);
	}

	////////Math Operations
	////////Conversions
	//Create 4D vector from 3D
	Vectors::VectorParent* Convert3Dto4D(Vectors::VectorParent* V);

	//Create 3D vector from 4D
	Vectors::VectorParent* Convert4Dto3D(Vectors::VectorParent* V);

	//Convert 3D vector S to scale matrix
	Matrices::MatrixParent* ToScale(Vectors::VectorParent* S);

	//Convert 3D vector T to translation matrix
	Matrices::MatrixParent* ToTranslate(Vectors::VectorParent* T);

	////////Math
	//Calculate dot product of 3D matrix M and 3D vector V
	//M dot V
	Vectors::Vector3D Vector3D_Dot_Matrix3x3(Matrices::MatrixSquare M,
											Vectors::VectorParent* V);

	////////Rotations
	//Rotate vector V about x axis by r radians
	Vectors::Vector3D RotateEulerX(Vectors::VectorParent* V, double r);

	//Rotate vector V about y axis by r radians
	Vectors::Vector3D RotateEulerY(Vectors::VectorParent* V, double r);

	//Rotate vector V about z axis by r radians
	Vectors::Vector3D RotateEulerZ(Vectors::VectorParent* V, double r);
}