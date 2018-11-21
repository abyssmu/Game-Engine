/*
Math library contains classes for matrices (both mxn and square), quaternions, and vectors (2D, 3D, and 4D).
All have corresponding abstract parent classes along with common constants, operations, and math functions.
Numeric constants and conversion constants are also included.
*/

#pragma once

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
	const double PI		= 3.141592653589793;
	const double RADIAN	= PI / 180;

	namespace Matrices
	{
		class MatrixParent
		{
		public:
			MatrixParent() {}
			MatrixParent(
				const MatrixParent& other) {}
			~MatrixParent() {}

			virtual void Delete() = 0;
			virtual int* GetDim() = 0;
			virtual double GetVal(
				int x,
				int y) = 0;
			virtual void SetVal(
				int x,
				int y,
				double val) = 0;
		};

		class MatrixMxN : public MatrixParent
		{
		public:			
			MatrixMxN(
				const MatrixMxN& other);
			MatrixMxN(
				int m,
				int n);

			void Delete();
			int* GetDim();
			double GetVal(
				int x,
				int y);
			void SetVal(
				int x,
				int y,
				double val);

		private:
			int m = 0, n = 0;
			double** container = 0;
		};

		class MatrixSquare : public MatrixParent
		{
		public:
			MatrixSquare(
				const MatrixSquare& other);
			MatrixSquare(
				int p);

			void Delete();
			int* GetDim();
			double GetVal(
				int x,
				int y);
			void SetVal(
				int x,
				int y,
				double val);

		private:
			int m = 0, n = 0;
			double** container = 0;
		};

		MatrixSquare Zero_1D();
		MatrixSquare Zero_2D();
		MatrixSquare Zero_3D();
		MatrixSquare Zero_4D();

		MatrixSquare One_2D();
		MatrixSquare One_3D();
		MatrixSquare One_4D();

		MatrixSquare Identity_1D();
		MatrixSquare Identity_2D();
		MatrixSquare Identity_3D();
		MatrixSquare Identity_4D();

		MatrixSquare EulerX(
			double& r);
		MatrixSquare EulerY(
			double& r);
		MatrixSquare EulerZ(
			double& r);

		MatrixParent* Dot(
			MatrixParent* A,
			MatrixParent* B);
		void Scale(
			MatrixParent* M,
			double& amt);
		void Add(
			MatrixParent* A,
			MatrixParent* B);
		bool Compare(
			MatrixParent* A,
			MatrixParent* B);
		void Equal(
			MatrixParent* A,
			MatrixParent* B);
		void Subtract(
			MatrixParent* A,
			MatrixParent* B);
	}

	namespace Quaternions
	{
		
	}

	namespace Vectors
	{
		class VectorParent
		{
		public:
			VectorParent() {}
			VectorParent(
				const VectorParent& other) {}
			~VectorParent() {}

			virtual void GetUnits(
				double* units) = 0;
			virtual void SetUnits(
				double* units) = 0;

			int dimension = 0;
			double x = 0.0, y = 0.0, z = 0.0, w = 0.0;
		};

		class Vector2D : public VectorParent
		{
		public:
			Vector2D(
				const Vector2D& other);
			Vector2D(
				double x,
				double y);

		private:
			void GetUnits(
				double* units);
			void SetUnits(
				double* units);
		};

		class Vector3D : public VectorParent
		{
		public:
			Vector3D(
				const Vector2D& other);
			Vector3D(
				const Vector3D& other);
			Vector3D(
				double x,
				double y,
				double z);
			
			VectorParent* Cross(
				VectorParent* B);

		private:
			void GetUnits(
				double* units);
			void SetUnits(
				double* units);
		};

		class Vector4D : public VectorParent
		{
		public:
			Vector4D(
				const Vector2D& other);
			Vector4D(
				const Vector3D& other);
			Vector4D(
				const Vector4D& other);
			Vector4D(
				double x,
				double y,
				double z,
				double w);

		private:
			void GetUnits(
				double* units);
			void SetUnits(
				double* units);
		};

		Vector2D UnitX_2D();
		Vector3D UnitX_3D();
		Vector4D UnitX_4D();

		Vector2D UnitY_2D();
		Vector3D UnitY_3D();
		Vector4D UnitY_4D();

		Vector3D UnitZ_3D();
		Vector4D UnitZ_4D();

		Vector4D UnitW_4D();
		
		Vector2D One_2D();
		Vector3D One_3D();
		Vector4D One_4D();

		Vector2D Zero_2D();
		Vector3D Zero_3D();
		Vector4D Zero_4D();

		double Dot(
			VectorParent* A,
			VectorParent* B);
		double Length(
			VectorParent* V);
		void Normalize(
			VectorParent* V);
		void Scale(
			VectorParent* V,
			double amt);
		void Add(
			VectorParent* A,
			VectorParent* B);
		bool Compare(
			VectorParent* A,
			VectorParent* B);
		void Equal(
			VectorParent* A,
			VectorParent* B);
		void Subtract(
			VectorParent* A,
			VectorParent* B);
	}

	Vectors::VectorParent* Convert3Dto4D(
		Vectors::VectorParent* V);
	Vectors::VectorParent* Convert4Dto3D(
		Vectors::VectorParent* V);
	Matrices::MatrixParent* ToScale(
		Vectors::VectorParent* S);
	Matrices::MatrixParent* ToTranslate(
		Vectors::VectorParent* T);
	Vectors::Vector3D Vector3D_Dot_Matrix3x3(
		Matrices::MatrixSquare M,
		Vectors::VectorParent* V);
	Vectors::Vector3D RotateEulerX(
		Vectors::VectorParent* V,
		double r);
	Vectors::Vector3D RotateEulerY(
		Vectors::VectorParent* V,
		double r);
	Vectors::Vector3D RotateEulerZ(
		Vectors::VectorParent* V,
		double r);
}