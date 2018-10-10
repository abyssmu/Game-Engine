/*
Input class is captures peripheral input (currently mouse and keyboard).
It captures the state of a key/the mouse by receiving messages as to which keys are down from the message handler.
It then stores these states in a boolean array from which they can be queried.
An enumeration is used to store the keys as known alphabet characters.
*/

#pragma once

//Includes
#include <Windows.h>

//Class Includes
#include "..\Math\MathLib.h"

class Input
{
public:
	//Default constructor
	Input();
	
	//Default copy constructor
	Input(const Input& other);

	//Default destructor
	~Input();

	////////Main Functions
	//Initialize all key states
	void Initialize();

	////////Utility Functions
	//Query current key state
	bool IsKeyDown(int key);

	//Capture down state of key
	void KeyDown(int key);
	
	//Capture up state of key
	void KeyUp(int key);

	//Capture character keys
	void ProcessCharacter(MathLib::Vectors::Vector3D& force);

	//Capture movement keys
	void ProcessMovement(MathLib::Vectors::Vector3D& force);

	//Capture mouse input
	void ProcessMouse(MathLib::Vectors::Vector3D& torque, bool& go);
	
	//Capture quit key
	bool ProcessQuit();

	//Reset key states
	void ResetKeys();

private:
	////////Main Functions

	////////Main Variables
	bool m_keys[256];
	POINT mouseP, prevMouseP;
};