#pragma once

#ifndef _ENTITYCLASS_H_
#define _ENTITYCLASS_H_

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
	bool Initialize(ID3D11Device* device, float* position,
					float* rotation, char* filename);

	//Shutdown components
	void Shutdown();

	////////Utility Functions
	//Get number of meshes
	int GetNumMeshes();

	////////Class Functions
	//Get model information
	ModelInfo* GetModelInfo(int i);

private:
	////////Main Variables
	Model* m_model;
};

#endif