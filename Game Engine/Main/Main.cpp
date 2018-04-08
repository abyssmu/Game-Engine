/*
Custom built game engine by Sean (Alex) Robinson.

Most everything in here is custom built. The excpetions are the Assimp library and the DirectX library.
Their corresponding classes are custom and used as an interface.

See UpdateLog.txt for completed and future updates along with routine list.
*/



//Windows main function
//Creates system root object that is basis for entire program

//Class Includes
#include "System\System.h"

//Entry point of program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR pScmdline, int iCmdshow)
{
	System* system = NULL;

	//Create system object
	system = new System;
	if (!system)
	{
		return 0;
	}

	//Initialize and run system object
	if (system->Initialize(600, 800))
	{
		system->Run();
	}

	//Shutdown and release system object
	system->Shutdown();
	delete system;
	system = 0;

	return 0;
}