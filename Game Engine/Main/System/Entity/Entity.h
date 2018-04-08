/*
Entity class is a manager for an individual object. It is a child of physics and contains the model of the object.
It is used to initialize the model and physics, update the physics, and obtain the model information for rendering.
*/

#pragma once

//Includes

//Class Includes
#include "Model\Model.h"
#include "Physics\Physics.h"

class Entity : public Physics
{
public:
	//Constructor
	Entity();

	//Default copy constructor
	Entity(const Entity& other);

	//Default destructor
	~Entity();

	////////Main Functions
	//Initialize components
	bool Initialize(ID3D11Device* device, MathLib::Vectors::Vector3D position,
					MathLib::Vectors::Vector3D rotation, char* filename);

	//Shutdown components
	void Shutdown();

	////////Utility Functions
	//Get number of meshes
	int GetNumMeshes();

	////////Class Functions
	//Get model information
	AllModelInfo* GetModelInfo(int i);

private:
	////////Main Variables
	Model* m_model;
};