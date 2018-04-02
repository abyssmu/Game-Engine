#pragma once

//Includes
#include <math.h>

//Math namespace
//Current data held:
	//Numeric Constants
	//Matrices
	//Matrix Constants
	//Matrix Constants
	//Quaternions
	//Quaternion Constants
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
			//Delete matrix and set to default
			virtual void Delete() = 0;

			//Get dimensions m, n
			virtual float* GetDim() = 0;

			//Get value at x, y
			virtual float GetVal(int x, int y) = 0;

			//Set value at x, y to val
			virtual void SetVal(int x, int y, float val) = 0;
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
			float* GetDim();

			//Get value at x, y
			float GetVal(int x, int y);

			//Set value at x, y to val
			void SetVal(int x, int y, float val);

		private:
			////////Main Variables
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
			//Delete matrix and set to default
			void Delete();

			//Get dimensions m, n
			float* GetDim();

			//Get value at x, y
			float GetVal(int x, int y);

			//Set value at x, y to val
			void SetVal(int x, int y, float val);

		private:
			////////Utility Variables
			int m, n;
			float** container;
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
		MatrixSquare EulerX(float r);
		MatrixSquare EulerY(float r);
		MatrixSquare EulerZ(float r);

		////////Matrix Operation Functions
		//Calculate matrix dot product
		//A dot B
		MatrixParent* Dot(MatrixParent* A, MatrixParent* B);

		//Scale matrix M by amt
		void Scale(MatrixParent* M, float amt);

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
			virtual void GetUnits(float* units) = 0;
			
			//Set vector units
			virtual void SetUnits(float* units) = 0;

			////////Utility Variables
			int dimension;
			float x, y, z, w;
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

			////////Utility Functions
			//Get vector units
			void GetUnits(float* units);
			
			//Set vector units
			void SetUnits(float* units);
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

			////////Math Functions
			//Calculate cross product
			//A(this) cross B
			VectorParent* Cross(VectorParent* B);

			////////Utility Functions
			//Get vector units
			void GetUnits(float* units);

			//Set vector units
			void SetUnits(float* units);
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

			////////Utility Functions
			//Get vector units
			void GetUnits(float* units);

			//Set vector units
			void SetUnits(float* units);
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
	Vectors::Vector3D RotateEulerX(Vectors::VectorParent* V, float r);

	//Rotate vector V about y axis by r radians
	Vectors::Vector3D RotateEulerY(Vectors::VectorParent* V, float r);

	//Rotate vector V about z axis by r radians
	Vectors::Vector3D RotateEulerZ(Vectors::VectorParent* V, float r);
}