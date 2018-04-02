//Class Includes
#include "MathLib.h"

/////////////////////////////////////////////////////////
//Conversions
/////////////////////////////////////////////////////////

//Create 4D vector from 3D
MathLib::Vectors::VectorParent* MathLib::Convert3Dto4D(Vectors::VectorParent* V)
{
	Vectors::Vector4D hold(MathLib::Vectors::Zero_4D());

	hold.x = V->x;
	hold.y = V->y;
	hold.z = V->z;
	hold.w = 1.0;

	return &hold;
}

//Create 3D vector from 4D
MathLib::Vectors::VectorParent* MathLib::Convert4Dto3D(Vectors::VectorParent* V)
{
	Vectors::Vector3D hold(MathLib::Vectors::Zero_3D());

	hold.x = V->x;
	hold.y = V->y;
	hold.z = V->z;

	return &hold;
}

//Convert 3D vector S to scale matrix
MathLib::Matrices::MatrixParent* MathLib::ToScale(Vectors::VectorParent* S)
{
	Matrices::MatrixSquare scale(Matrices::Identity_4D());

	scale.SetVal(0, 0, S->x);
	scale.SetVal(1, 1, S->y);
	scale.SetVal(2, 2, S->z);

	return &scale;
}

//Convert 3D vector T to translation matrix
MathLib::Matrices::MatrixParent* MathLib::ToTranslate(Vectors::VectorParent* T)
{
	Matrices::MatrixSquare translation(Matrices::Identity_4D());

	translation.SetVal(3, 0, T->x);
	translation.SetVal(3, 1, T->y);
	translation.SetVal(3, 2, T->z);

	return &translation;
}

/////////////////////////////////////////////////////////
//Math
/////////////////////////////////////////////////////////

//Calculate dot product of 3D matrix M and 3D vector V
//Vector dimension must equal N dimension of matrix
//M dot V
MathLib::Vectors::Vector3D MathLib::Vector3D_Dot_Matrix3x3(
	Matrices::MatrixSquare M,
	Vectors::VectorParent* V)
{
	//{ , , , , }	{ , }	{ , }
	//{ , , , , } * { , } = { , }
	//{ , , , , }	{ , }	{ , }
	//{ , , , , }	{ , }	{ , }

	Vectors::Vector3D hold(Vectors::Zero_3D());
	Matrices::MatrixMxN vecMatrix(4, 1);

	vecMatrix.SetVal(0, 0, V->x);
	vecMatrix.SetVal(0, 1, V->y);
	vecMatrix.SetVal(0, 2, V->z);
	vecMatrix.SetVal(0, 3, 1.0);

	Matrices::MatrixParent* temp = Matrices::Dot(&M, &vecMatrix);
	if (temp == NULL)
	{
		return Vectors::Zero_3D();
	}

	hold.x = temp->GetVal(0, 0);
	hold.y = temp->GetVal(0, 1);
	hold.z = temp->GetVal(0, 2);

	return hold;
}

/////////////////////////////////////////////////////////
//Rotations
/////////////////////////////////////////////////////////

//Rotate vector V about x axis by r radians
MathLib::Vectors::Vector3D MathLib::RotateEulerX(Vectors::VectorParent* V,
												float r)
{
	Matrices::MatrixSquare EulerX(Matrices::EulerX(r));

	return Vector3D_Dot_Matrix3x3(EulerX, V);
}

//Rotate vector V about y axis by r radians
MathLib::Vectors::Vector3D MathLib::RotateEulerY(Vectors::VectorParent* V,
												float r)
{
	Matrices::MatrixSquare EulerY(Matrices::EulerY(r));

	return Vector3D_Dot_Matrix3x3(EulerY, V);
}

//Rotate vector V about z axis by r radians
MathLib::Vectors::Vector3D MathLib::RotateEulerZ(Vectors::VectorParent* V,
												float r)
{
	Matrices::MatrixSquare EulerZ(Matrices::EulerZ(r));

	return Vector3D_Dot_Matrix3x3(EulerZ, V);
}