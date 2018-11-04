#include "MathLib.h"

MathLib::Vectors::VectorParent* MathLib::Convert3Dto4D(
	Vectors::VectorParent* V)
{
	static auto hold = Vectors::Vector4D(MathLib::Vectors::Zero_4D());

	hold.x = V->x;
	hold.y = V->y;
	hold.z = V->z;
	hold.w = 1.0;

	return &hold;
}

MathLib::Vectors::VectorParent* MathLib::Convert4Dto3D(
	Vectors::VectorParent* V)
{
	static auto hold = Vectors::Vector4D(MathLib::Vectors::Zero_3D());

	hold.x = V->x;
	hold.y = V->y;
	hold.z = V->z;

	return &hold;
}

MathLib::Matrices::MatrixParent* MathLib::ToScale(
	Vectors::VectorParent* S)
{
	static auto scale = Matrices::MatrixSquare(Matrices::Identity_4D());

	scale.SetVal(0, 0, S->x);
	scale.SetVal(1, 1, S->y);
	scale.SetVal(2, 2, S->z);

	return &scale;
}

MathLib::Matrices::MatrixParent* MathLib::ToTranslate(
	Vectors::VectorParent* T)
{
	static auto translation = Matrices::MatrixSquare(Matrices::Identity_4D());

	translation.SetVal(3, 0, T->x);
	translation.SetVal(3, 1, T->y);
	translation.SetVal(3, 2, T->z);

	return &translation;
}

MathLib::Vectors::Vector3D MathLib::Vector3D_Dot_Matrix3x3(
	Matrices::MatrixSquare M,
	Vectors::VectorParent* V)
{
	//{ , , , , }	{ , }	{ , }
	//{ , , , , } * { , } = { , }
	//{ , , , , }	{ , }	{ , }
	//{ , , , , }	{ , }	{ , }

	auto hold = Vectors::Vector3D(Vectors::Zero_3D());
	auto vecMatrix = Matrices::MatrixMxN(4, 1);

	vecMatrix.SetVal(0, 0, V->x);
	vecMatrix.SetVal(0, 1, V->y);
	vecMatrix.SetVal(0, 2, V->z);
	vecMatrix.SetVal(0, 3, 1.0);

	auto temp = Matrices::Dot(&M, &vecMatrix);
	if (temp == 0)
	{
		return Vectors::Zero_3D();
	}

	hold.x = temp->GetVal(0, 0);
	hold.y = temp->GetVal(0, 1);
	hold.z = temp->GetVal(0, 2);

	return hold;
}

MathLib::Vectors::Vector3D MathLib::RotateEulerX(
	Vectors::VectorParent* V,
	double r)
{
	auto EulerX = Matrices::MatrixSquare(Matrices::EulerX(r));

	return Vector3D_Dot_Matrix3x3(EulerX, V);
}

MathLib::Vectors::Vector3D MathLib::RotateEulerY(
	Vectors::VectorParent* V,
	double r)
{
	auto EulerY = Matrices::MatrixSquare(Matrices::EulerY(r));

	return Vector3D_Dot_Matrix3x3(EulerY, V);
}

MathLib::Vectors::Vector3D MathLib::RotateEulerZ(
	Vectors::VectorParent* V,
	double r)
{
	auto EulerZ = Matrices::MatrixSquare(Matrices::EulerZ(r));

	return Vector3D_Dot_Matrix3x3(EulerZ, V);
}