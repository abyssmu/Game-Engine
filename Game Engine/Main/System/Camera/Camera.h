/*
Camera class is used to setup the view matrix for DirectX. It takes a position and rotation and
calculates the view matrix with DirectX functions.
*/

#pragma once

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
	bool Initialize(MathLib::Vectors::Vector3D position,
					MathLib::Vectors::Vector3D rotation);

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