#pragma once

#ifndef _ENTITYCLASS_H_
#define _ENTITYCLASS_H_

//Includes

//Class Includes
#include "Model\Model.h"

class Entity
{
public:
	Entity();
	Entity(const Entity&);
	~Entity();

	//Main Functions
	bool Initialize(ID3D11Device*);
	void Shutdown();

	//Utility Functions
	ModelInfo* GetModelInfo();

private:
	Model* m_model;
};

#endif