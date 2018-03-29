#pragma once

//Includes
#include <math.h>

//Math namespace
//Current data held:
	//Numeric Constants
	//Matrices
	//Matrix Constants
	//Quaternions
	//Quaternion Constants
	//Vectors
	//Vector Constants
	//Math Operations

namespace MathLib
{
	////////Numeric Constants
	const float PI = 3.141592653589793;
	const float RADIAN = PI / 180;

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
			//Get value at x, y
			virtual float GetVal(int x, int y) = 0;

			//Set value at x, y to val
			virtual void SetVal(int x, int y, float val) = 0;

		private:
			////////Utility Variables
			int m = 0;
			int n = 0;
			float** container = NULL;
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
			//Get value at x, y
			float GetVal(int x, int y);

			//Set value at x, y to val
			void SetVal(int x, int y, float val);

		private:
			////////Utility Variables
			int m, n;
			float** container;
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
			//Get value at x, y
			float GetVal(int x, int y);

			//Set value at x, y to val
			void SetVal(int x, int y, float val);

		private:
			////////Utility Variables
			int m, n;
			float** container;
		};

		////////Matrix Operations

		////////Matrix Math

		////////Numerical Matrix Constants
		//Return 1D zero matrix
		MatrixSquare Zero_1D();

		//Return 2D zero matrix
		MatrixSquare Zero_2D();

		//Return 3D zero matrix
		MatrixSquare Zero_3D();

		//Return 4D zero matrix
		MatrixSquare Zero_4D();

		//Return 2D matrix of ones
		MatrixSquare One_2D();

		//Return 3D matrix of ones
		MatrixSquare One_3D();

		//Return 4D matrix of ones
		MatrixSquare One_4D();

		////////Identity Matrix Constants
		//Return 1D identity matrix
		MatrixSquare Identity_1D();

		//Return 2D identity matrix
		MatrixSquare Identity_2D();

		//Return 3D identity matrix
		MatrixSquare Identity_3D();

		//Return 4D identity matrix
		MatrixSquare Identity_4D();

		////////Rotation Matrix Constants
		//Calculate and return rotation matrix about x axis by r radians
		MatrixSquare EulerX(float r);

		//Calculate and return rotation matrix about y axis by r radians
		MatrixSquare EulerY(float r);

		//Calculate and return rotation matrix about z axis by r radians
		MatrixSquare EulerZ(float r);
	}

	////////Quaternions
	namespace Quaternions
	{
		////////Quaternion Constants
	}

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
			virtual void GetUnits(float* units) = 0;
			
			//Set vector units
			virtual void SetUnits(float* units) = 0;

			////////Utility Variables
			int dimension = 0;
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
			Vector2D(float x, float y);
			
			//Default destructor
			~Vector2D();

			////////Constant Functions
			//Return unit x vector
			Vector2D UnitX();

			//Return unit y vector
			Vector2D UnitY();

			//Return vector of ones
			Vector2D One();

			//Return zero vector
			Vector2D Zero();

			////////Utility Functions
			//Get vector units
			void GetUnits(float* units);
			
			//Set vector units
			void SetUnits(float* units);

			////////Utility Variables
			float x, y;
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
			Vector3D(float x, float y, float z);
			
			//Default destructor
			~Vector3D();

			////////Constant Functions
			//Return unit x vector
			Vector3D UnitX();

			//Return unit y vector
			Vector3D UnitY();

			//Return unit z vector
			Vector3D UnitZ();

			//Return vector of ones
			Vector3D One();

			//Return zero vector
			Vector3D Zero();

			////////Math Functions
			//Calculate cross product
			//A(this) cross B
			Vector3D Cross(Vector3D B);

			////////Utility Functions
			//Get vector units
			void GetUnits(float* units);

			//Set vector units
			void SetUnits(float* units);

			////////Utility Variables
			float x, y, z;
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
			Vector4D(float x, float y, float z, float w);
			
			//Default destructor
			~Vector4D();

			////////Constant Functions
			//Return unit x vector
			Vector4D UnitX();
			
			//Return unit y vector
			Vector4D UnitY();

			//Return unit z vector
			Vector4D UnitZ();

			//Return unit w vector
			Vector4D UnitW();

			//Return vector of ones
			Vector4D One();

			//Return zero vector
			Vector4D Zero();

			////////Utility Functions
			//Get vector units
			void GetUnits(float* units);

			//Set vector units
			void SetUnits(float* units);

			//Utility Variables
			float x, y, z, w;
		};

		////////Vector Operation Functions
		//Calculate dot product
		//A dot B
		float Dot(VectorParent* A, VectorParent* B);

		//Calculate length of V
		float Length(VectorParent* V);

		//Normalize V
		void Normalize(VectorParent* V);

		//Scale V by amt
		void Scale(VectorParent* V, float amt);

		////////Vector Math Functions
		//Vector addition
		//A + B
		void Add(VectorParent& A, VectorParent& B);

		//Vector comparison
		//A == B
		bool Compare(VectorParent& A, VectorParent& B);

		//Vector equalization
		//A = B
		void Equal(VectorParent& A, VectorParent& B);

		//Vector subtraction
		//A - B
		void Subtract(VectorParent& A, VectorParent& B);
	}

	////////Math Operations
	////////Conversions
	//Convert 4D vector to 3D
	Vectors::Vector3D Convert4Dto3D(Vectors::Vector4D V);

	////////Math
	//Calculate dot product of 3D matrix M and 3D vector V
	//M dot V
	Vectors::Vector3D Vector3D_Dot_Matrix3x3(Vectors::Vector3D V,
									Matrices::MatrixSquare M);

	////////Rotations
	//Rotate vector V about x axis by r radians
	Vectors::Vector3D RotateEulerX(Vectors::Vector3D V, float r);

	//Rotate vector V about y axis by r radians
	Vectors::Vector3D RotateEulerY(Vectors::Vector3D V, float r);

	//Rotate vector V about z axis by r radians
	Vectors::Vector3D RotateEulerZ(Vectors::Vector3D V, float r);
}