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
#include "Entity\Entity.h"
#include "Graphics\Graphics.h"
#include "Input\Input.h"

class System
{
public:
	System();
	System(const System& other);
	~System();

	////////Main Functions
	//Initialize class
	bool Initialize(int screenWidth, int screenHeight);

	//Shutdown class
	void Shutdown();

	//Main program loop
	void Run();

	////////Utility Functions
	//Windows message handler
	LRESULT CALLBACK MessageHandler(HWND hwnd, UINT umsg,
		WPARAM wparam, LPARAM lparam);

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

	//Intialize window
	void InitializeWindows();

	//Process graphics
	bool ProcessGraphics();

	//Process input
	bool ProcessInput(MathLib::Vectors::Vector3D& force, 
					MathLib::Vectors::Vector3D& forceC,
					MathLib::Vectors::Vector3D& torque);

	//Shutdown window
	void ShutdownWindows();

	//Update camera
	void UpdateCamera(MathLib::Vectors::Vector3D force,
					MathLib::Vectors::Vector3D torque);
	
	////////Main Variables
	LPCSTR m_applicationName;
	HINSTANCE m_hInstance;
	HWND m_hWnd;

	////////Class Variabes
	Camera* m_camera;
	Entity* m_entities;
	Graphics* m_graphics;
	Input* m_input;
	
	////////Utility Variables
	int m_screenWidth, m_screenHeight;
};

//Function Prototype
//Check window exit
static LRESULT CALLBACK WndProc(HWND hwnd, UINT umsg,
	WPARAM wparam, LPARAM lparam);

//Globals
static System* ApplicationHandle = 0;