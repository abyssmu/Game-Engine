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
	bool Initialize(ID3D11Device*, float*, float*);
	void Shutdown();

	//Utility Functions
	ModelInfo* GetModelInfo();

private:
	//Main Variables
	Model* m_model;
};

#endif