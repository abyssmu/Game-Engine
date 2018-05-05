/*
WindowManager class is used as a manager for the window display.
It holds the program manager and transfers information from there to the display.
*/

#pragma once

//Pre processor
#define WIN32_LEAN_AND_MEAN

//Includes
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

//Class Includes
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
	//Windows message handler
	LRESULT CALLBACK MessageHandler(HWND hwnd, UINT umsg,
		WPARAM wparam, LPARAM lparam);

private:
	////////Main Functions
	//Initialize game window
	bool InitializeGame(int screenHeight, int screenWidth);

	//Initialize main window
	bool InitializeMain(int screenHeight, int screenWidth);

	//Shutdown window
	void ShutdownWindow();

	////////Main Variables
	LPCSTR m_applicationName;
	HINSTANCE m_hInstance;
	HWND m_mainWindow;
	HWND m_gameWindow;

	////////Class Variables
	System* m_system;
};

//Function Prototype
//Check window exit
static LRESULT CALLBACK WndProc(HWND hwnd, UINT umsg,
	WPARAM wparam, LPARAM lparam);

//Globals
static WindowManager* ApplicationHandle = 0;