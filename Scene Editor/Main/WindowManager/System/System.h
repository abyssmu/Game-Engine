/*
System class is used as a manager for the whole program.
It contains the game loop and manages communication between cores.
*/

#pragma once

#define WIN32_LEAN_AND_MEAN

#include "Camera\Camera.h"
#include "Color\Color.h"
#include "Objects\Entity\Entity.h"
#include "Graphics\Graphics.h"
#include "Input\Input.h"

#include <Windows.h>
#include <stdio.h>
#include <string>
#include <tchar.h>

class System
{
public:
	bool Initialize(
		int screenHeight,
		int screenWidth,
		HWND hwnd);
	void Shutdown();
	void Run(
		bool& minimized);

	void KeyDown(
		unsigned int key);
	void KeyUp(
		unsigned int key);
	void MouseActive(
		bool active);
	void ResetKeys();
	void UpdateModel(
		std::string modelName);

private:
	void CreateFilenameString
	(std::string& filename);
	void CheckPosition();
	bool CheckResizeWindow();
	bool Frame();
	bool InitializeCamera();
	bool InitializeEntity();
	bool InitializeGraphics();
	bool InitializeInput();
	bool ProcessGraphics();
	bool ProcessInput(
		MathLib::Vectors::Vector3D& force, 
		MathLib::Vectors::Vector3D& forceC,
		MathLib::Vectors::Vector3D& torque);
	void UpdateCamera(
		MathLib::Vectors::Vector3D force,
		MathLib::Vectors::Vector3D torque);
	void UpdateEntity();

	HWND m_hWnd = HWND(0);

	Camera* m_camera = 0;
	Entity* m_entities = 0;
	Graphics* m_graphics = 0;
	Input* m_input = 0;
	
	int m_screenWidth = 0, m_screenHeight = 0;
	bool m_mouseActive = false, m_mouseGo = false;
	std::string m_modelName = "Sphere";
};