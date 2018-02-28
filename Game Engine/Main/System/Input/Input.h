#pragma once

#ifndef _INPUTCLASS_H_
#define _INPUTCLASS_H_

//Includes
#include <Windows.h>

class Input
{
public:
	Input();
	Input(const Input&);
	~Input();

	//Main Functions
	void Initialize();

	//Utility Functions
	bool IsKeyDown(int);
	void KeyDown(int);
	void KeyUp(int);
	void ProcessMouse(float*);
	void ProcessMovement(float&, float&, float&);
	bool ProcessQuit();

private:
	//Main Functions

	//Main Variables
	bool m_keys[256];
	POINT mouseP, prevMouseP;

	//Keys
	enum
	{
		ESC = 0x1B,
		W = 0x57,
		A = 0x41,
		S = 0x53,
		D = 0x44,
		R = 0x52,
		F = 0x46
	};
};

#endif