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
#include <string>
#include <tchar.h>

//Class Includes
#include "Camera\Camera.h"
#include "Color\Color.h"
#include "Objects\Entity\Entity.h"
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

	//Set mouse active
	void MouseActive(bool active);

	//Reset key states
	void ResetKeys();

	//Update entity model
	void UpdateModel(std::string modelName);

private:
	////////Main Functions
	//Create full model filename string
	void CreateFilenameString(std::string& filename);

	//Check new model position
	void CheckPosition();

	//Check window resolution changes
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

	//Update entity model
	void UpdateEntity();

	////////Main Variables
	HWND m_hWnd;

	////////Class Variabes
	Camera* m_camera;
	Entity* m_entities;
	Graphics* m_graphics;
	Input* m_input;
	
	////////Utility Variables
	int m_screenWidth, m_screenHeight;
	bool m_mouseActive, m_mouseGo;
	std::string m_modelName;
};