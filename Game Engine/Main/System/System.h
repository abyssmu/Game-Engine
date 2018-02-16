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
	SystemClass(const SystemClass&);
	~SystemClass();

	//Main Functions
	bool Initialize();
	void Shutdown();
	void Run();

	//Utility Functions
	LRESULT CALLBACK MessageHandler(HWND, UINT,
		WPARAM, LPARAM);

private:
	//Main Functions
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();
	
	//Main Variables
	LPCWSTR m_applicationName;
	HINSTANCE m_hInstance;
	HWND m_hWnd;

	//Class Variabes
	Camera* m_camera;
	Entity* m_entities;
	Graphics* m_graphics;
	Input* m_input;
	
	//Utility Variables
	int screenWidth, screenHeight;
};

//Function Prototype
static LRESULT CALLBACK WndProc(HWND, UINT,
	WPARAM, LPARAM);

//Globals
static SystemClass* ApplicationHandle = 0;

#endif