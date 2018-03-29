#pragma once

#ifndef _SYSTEMCLASS_H_
#define _SYSTEMCLASS_H_

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

class SystemClass
{
public:
	SystemClass();
	SystemClass(const SystemClass& other);
	~SystemClass();

	////////Main Functions
	//Initialize class
	bool Initialize();

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
	//Process all per frame changes
	bool Frame();

	//Intialize window
	void InitializeWindows(int& screenHeight, int& screenWidth);

	//Shutdown window
	void ShutdownWindows();
	
	////////Main Variables
	LPCWSTR m_applicationName;
	HINSTANCE m_hInstance;
	HWND m_hWnd;

	////////Class Variabes
	Camera* m_camera;
	Entity* m_entities;
	Graphics* m_graphics;
	Input* m_input;
	
	////////Utility Variables
	int screenWidth, screenHeight;
};

//Function Prototype
//Check window exit
static LRESULT CALLBACK WndProc(HWND hwnd, UINT umsg,
	WPARAM wparam, LPARAM lparam);

//Globals
static SystemClass* ApplicationHandle = 0;

#endif