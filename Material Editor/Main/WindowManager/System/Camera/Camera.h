/*
Camera class is used to setup the view matrix for DirectX. It takes a position and rotation and
calculates the view matrix with DirectX functions.
*/

#pragma once

#include "..\Objects\Entity\Entity.h"

#include <DirectXMath.h>

class Camera : public Entity
{
public:
	bool Initialize(
		MathLib::Vectors::Vector3D& position,
		MathLib::Vectors::Vector3D& rotation);

	//Render camera by calculating view matrix
	void Render();
	DirectX::XMMATRIX GetViewMatrix();

private:
	DirectX::XMMATRIX m_viewMatrix = DirectX::XMMatrixIdentity();
};