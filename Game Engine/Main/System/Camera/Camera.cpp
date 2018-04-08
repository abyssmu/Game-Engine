//Camera class
//Sets up viewport

#include "Camera.h"

//Default constructor
Camera::Camera()
{}

//Default copy constructor
Camera::Camera(const Camera& other)
{}

//Default destructor
Camera::~Camera()
{}

//Initialize camera settings
bool Camera::Initialize(MathLib::Vectors::Vector3D position,
						MathLib::Vectors::Vector3D rotation)
{
	SetPosition(position);
	SetRotation(rotation);

	return true;
}

//Render camera
//Calculate view matrix
void Camera::Render()
{
	DirectX::XMVECTOR up, position, lookAt;
	DirectX::XMMATRIX rotationMatrix;
	
	double yaw, pitch, roll;

	//Set up vector
	up = DirectX::XMVectorSet(0.0, 1.0, 0.0, 1.0);

	//Set look at default
	lookAt = DirectX::XMVectorSet(0.0, 0.0, 1.0, 1.0);

	//Set position
	position = DirectX::XMVectorSet((float)GetPosition().x, (float)GetPosition().y,
		(float)GetPosition().z, 1.0f);

	//Set rotation
	pitch = GetRotation().x * 0.0174532925;
	yaw = GetRotation().y * 0.0174532925;
	roll = GetRotation().z * 0.0174532925;

	//Create rotation matrix
	rotationMatrix = DirectX::XMMatrixRotationRollPitchYaw((float)pitch,
		(float)yaw, (float)roll);

	//Transform look at and up by rotation
	lookAt = DirectX::XMVector3TransformCoord(lookAt, rotationMatrix);
	up = DirectX::XMVector3TransformCoord(up, rotationMatrix);

	//Translate camera
	lookAt = DirectX::XMVectorAdd(position, lookAt);

	position = DirectX::XMVectorAdd(position,
		DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f));

	//Create view matrix
	m_viewMatrix = DirectX::XMMatrixLookAtLH(position, lookAt, up);
}

//Get view matrix
DirectX::XMMATRIX Camera::GetViewMatrix()
{
	return m_viewMatrix;
}