//Windows main function
//Creates system root object that is basis for entire program

//Class Includes
#include "System\System.h"

//Entry point of program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR pScmdline, int iCmdshow)
{
	SystemClass* System = NULL;
	bool result = true;

	//Create system object
	System = new SystemClass;
	if (!System)
	{
		return 0;
	}

	//Initialize and run system object
	result = System->Initialize();
	if (result)
	{
		System->Run();
	}

	//Shutdown and release system object
	System->Shutdown();
	delete System;
	System = 0;

	return 0;
}