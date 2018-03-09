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
	Entity();
	Entity(const Entity&);
	~Entity();

	//Main Functions
	bool Initialize(ID3D11Device*, float*,
		float*, char*);
	void Shutdown();

	//Utility Functions
	int GetNumMeshes();

	//Class Functions
	ModelInfo* GetModelInfo(int);

private:
	//Main Variables
	Model* m_model;
};

#endif