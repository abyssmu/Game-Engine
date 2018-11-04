/*
Entity class is a manager for an individual object. It is a child of physics and contains the model of the object.
It is used to initialize the model and physics, update the physics, and obtain the model information for rendering.
*/

#pragma once

#include "Model\Model.h"
#include "Physics\Physics.h"

class Entity : public Physics
{
public:
	bool Initialize(
		ID3D11Device* device,
		MathLib::Vectors::Vector3D position,
		MathLib::Vectors::Vector3D rotation,
		char* filename);
	void Shutdown();

	int GetNumMeshes();
	AllModelInfo* GetModelInfo(
		int i);

private:
	Model* m_model = 0;
};