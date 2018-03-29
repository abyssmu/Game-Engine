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
	//Default constructor
	Camera();

	//Default copy constructor
	Camera(const Camera& other);

	//Default destructor
	~Camera();

	////////Main Functions
	//Initialize camera settings
	bool Initialize(float* pos, float* rot);

	//Render camera
	//Calculate view matrix
	void Render();

	////////Class Functions
	//Get view matrix
	DirectX::XMMATRIX GetViewMatrix();

private:
	////////Main Variables
	DirectX::XMMATRIX m_viewMatrix;
};

#endif