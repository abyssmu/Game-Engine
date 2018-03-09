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
bool Camera::Initialize(float* pos, float* rot)
{
	SetPosition(pos);
	SetRotation(rot);

	return true;
}

//Render camera
//Calculate view matrix
void Camera::Render()
{
	DirectX::XMVECTOR up, position, lookAt;
	DirectX::XMMATRIX rotationMatrix;
	
	float yaw, pitch, roll;

	//Set up vector
	up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);

	//Set look at default
	lookAt = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f);

	//Set position
	position = DirectX::XMVectorSet(GetPosition()[0], GetPosition()[1],
		GetPosition()[2], 1.0f);

	//Set rotation
	pitch = GetRotation()[0] * 0.0174532925f;
	yaw = GetRotation()[1] * 0.0174532925f;
	roll = GetRotation()[2] * 0.0174532925f;

	//Create rotation matrix
	rotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(pitch,
		yaw, roll);

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