/*
System class is used as a manager for the whole program.
It contains the game loop and manages communication between cores.
*/

#pragma once

//Pre processor
#define WIN32_LEAN_AND_MEAN

//Includes
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

//Class Includes
#include "Camera\Camera.h"
#include "Color\Color.h"
#include "Entity\Entity.h"
#include "Graphics\Graphics.h"
#include "Input\Input.h"

class System
{
public:
	//Constructor
	System();

	//Default copy constructor
	System(const System& other);

	//Default destructor
	~System();

	////////Main Functions
	//Initialize program
	bool Initialize(int screenHeight, int screenWidth, HWND hwnd);

	//Shutdown program
	void Shutdown();

	//Main program loop
	void Run(bool& minimized);

	////////Utility Functions
	//Set input key down
	void KeyDown(unsigned int key);

	//Set input key up
	void KeyUp(unsigned int key);

private:
	////////Main Functions
	//Check for window resolution changes
	bool CheckResizeWindow();

	//Process all per frame changes
	bool Frame();

	//Initialize camera
	bool InitializeCamera();

	//Initialize entities
	bool InitializeEntity();

	//Initialize graphics
	bool InitializeGraphics();

	//Initialize input
	bool InitializeInput();

	//Process graphics
	bool ProcessGraphics();

	//Process input
	bool ProcessInput(MathLib::Vectors::Vector3D& force, 
					MathLib::Vectors::Vector3D& forceC,
					MathLib::Vectors::Vector3D& torque);

	//Update camera
	void UpdateCamera(MathLib::Vectors::Vector3D force,
					MathLib::Vectors::Vector3D torque);

	////////Main Variables
	HWND m_hWnd;

	////////Class Variabes
	Camera* m_camera;
	Entity* m_entities;
	Graphics* m_graphics;
	Input* m_input;
	
	////////Utility Variables
	int m_screenWidth, m_screenHeight;
};