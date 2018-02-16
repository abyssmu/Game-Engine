#include "Camera.h"

Camera::Camera()
{
	m_position = m_rotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
}

Camera::Camera(const Camera& other)
{}

Camera::~Camera()
{}

void Camera::Render()
{
	DirectX::XMVECTOR up, position, lookAt;
	DirectX::XMMATRIX rotationMatrix;
	
	float yaw, pitch, roll;

	//Set up vector
	up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);

	//Set look at
	lookAt = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f);

	//Set position
	position = DirectX::XMVectorSet(m_position.x, m_position.y,
		m_position.z, 1.0f);

	//Set rotation
	pitch = m_rotation.x * 0.0174532925f;
	yaw = m_rotation.y * 0.0174532925f;
	roll = m_rotation.z * 0.0174532925f;

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

void Camera::SetPosition(float* position)
{
	m_position.x = position[0];
	m_position.y = position[1];
	m_position.z = position[2];
}

void Camera::SetRotation(float* rotation)
{
	m_rotation.x = rotation[0];
	m_rotation.y = rotation[1];
	m_rotation.z = rotation[2];
}

void Camera::UpdatePosition(float* position)
{
	m_position.x += position[0];
	m_position.y += position[1];
	m_position.z += position[2];
}

void Camera::UpdateRotation(float* rotation)
{
	m_rotation.x += rotation[0];
	m_rotation.y += rotation[1];
	m_rotation.z += rotation[2];
}

DirectX::XMFLOAT3 Camera::GetPosition()
{
	return m_position;
}

DirectX::XMFLOAT3 Camera::GetRotation()
{
	return m_position;
}

DirectX::XMMATRIX Camera::GetViewMatrix()
{
	return m_viewMatrix;
}