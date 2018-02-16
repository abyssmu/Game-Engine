#pragma once

#ifndef _INPUTCLASS_H_
#define _INPUTCLASS_H_

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
	bool ProcessQuit();

private:
	bool m_keys[256];

	//Keys
	enum
	{
		ESC = 0x1B,
	};
};

#endif