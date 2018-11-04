#include "Camera.h"

bool Camera::Initialize(
	MathLib::Vectors::Vector3D position,
	MathLib::Vectors::Vector3D rotation)
{
	SetPosition(position);
	SetRotation(rotation);

	return true;
}

//Render camera by calculating view matrix
void Camera::Render()
{	
	auto up = DirectX::XMVectorSet(0.0, 1.0, 0.0, 1.0);
	auto lookAt = DirectX::XMVectorSet(0.0, 0.0, 1.0, 1.0);
	auto position = DirectX::XMVectorSet((float)GetPosition().x, (float)GetPosition().y,
		(float)GetPosition().z, 1.0f);

	//Calculate rotation
	auto pitch = GetRotation().x * 0.0174532925;
	auto yaw = GetRotation().y * 0.0174532925;
	auto roll = GetRotation().z * 0.0174532925;

	auto rotationMatrix = DirectX::XMMatrixRotationRollPitchYaw((float)pitch,
		(float)yaw, (float)roll);

	//Transform look at and up by rotation
	lookAt = DirectX::XMVector3TransformCoord(lookAt, rotationMatrix);
	up = DirectX::XMVector3TransformCoord(up, rotationMatrix);

	//Translate camera
	lookAt = DirectX::XMVectorAdd(position, lookAt);

	position = DirectX::XMVectorAdd(position,
		DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f));

	m_viewMatrix = DirectX::XMMatrixLookAtLH(position, lookAt, up);
}

DirectX::XMMATRIX Camera::GetViewMatrix()
{
	return m_viewMatrix;
}