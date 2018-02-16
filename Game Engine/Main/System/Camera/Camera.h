#pragma once

#ifndef _CAMERACLASS_H_
#define _CAMERACLASS_H_

//Includes
#include <DirectXMath.h>

//Class Includes
#include "..\Entity\Entity.h"

class Camera : public Entity
{
public:
	Camera();
	Camera(const Camera&);
	~Camera();

	//Main Functions
	void Render();

	//Utility Functions
	void SetPosition(float*);
	void SetRotation(float*);
	void UpdatePosition(float*);
	void UpdateRotation(float*);

	//Class Functions
	DirectX::XMFLOAT3 GetPosition();
	DirectX::XMFLOAT3 GetRotation();
	DirectX::XMMATRIX GetViewMatrix();

private:
	//Main Variables
	DirectX::XMFLOAT3 m_position;
	DirectX::XMFLOAT3 m_rotation;
	DirectX::XMMATRIX m_viewMatrix;
};

#endif