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
	bool Initialize(float*, float*);
	void Render();

	//Class Functions
	DirectX::XMMATRIX GetViewMatrix();

private:
	//Main Variables
	DirectX::XMMATRIX m_viewMatrix;
};

#endif