/*
WindowManager class is used as a manager for the window display.
It holds the program manager and transfers information from there to the display.
*/

#pragma once

//Pre processor
#define WIN32_LEAN_AND_MEAN

//Includes
#include <ShObjIdl.h>
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

//Class Includes
#include "MenuResource.h"
#include "System\System.h"

class WindowManager
{
public:
	//Constructor
	WindowManager();

	//Default copy constructor
	WindowManager(const WindowManager& other);

	//Default destructor
	~WindowManager();

	////////Main Functions
	//Initialize window
	bool Initialize(int screenHeight, int screenWidth);

	//Shutdown window
	void Shutdown();

	//Run program
	void Run();

	////////Utility Functions
	//Check window resolution changes
	bool CheckResizeWindow();

	//Return world window
	HWND GetWorld();

	//Main window message handler
	LRESULT CALLBACK MainMessageHandler(HWND hwnd, UINT umsg,
										WPARAM wparam, LPARAM lparam);

	//World window message handler
	LRESULT CALLBACK WorldMessageHandler(HWND hwnd, UINT umsg,
										WPARAM wparam, LPARAM lparam);

	//Check if first pass
	bool PassGo();

	//Size game window
	void SizeWorld();

	//Update model
	void UpdateModel(std::string modelName);

private:
	////////Main Functions
	//Initialize inner windows
	bool InitializeInner();

	//Initialize main window
	bool InitializeMain();
	
	//Initialize game window
	bool InitializeWorld();

	//Shutdown window
	void ShutdownWindow();

	////////Main Variables
	LPCSTR m_applicationName;
	HINSTANCE m_hInstance;
	HWND m_mainWindow, m_worldWindow;

	////////Class Variables
	System* m_system;

	////////Utility Variables
	bool go;
	int m_screenHeight, m_screenWidth,
		m_worldHeight, m_worldWidth;
};

//Function Prototype
//Check window exit
static LRESULT CALLBACK WndProc(HWND hwnd, UINT umsg,
								WPARAM wparam, LPARAM lparam);

//Globals
static WindowManager* ApplicationHandle = 0;