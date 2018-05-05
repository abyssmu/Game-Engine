/*
Custom built game engine by Sean (Alex) Robinson.

Most everything in here is custom built. The excpetions are the Assimp library and the DirectX library.
Their corresponding classes are custom and used as an interface.

See UpdateLog.txt for completed and future updates along with routine list.
*/

//Windows main function
//Creates system root object that is base for entire program

//Class Includes
#include "WindowManager\WindowManager.h"

//Entry point of program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR pScmdline, int iCmdshow)
{
	WindowManager* manager = new WindowManager;
	if (!manager)
	{
		return false;
	}

	//Initialize and run
	//Height, width
	if (manager->Initialize(720, 1280))
	{
		manager->Run();
	}

	//Shutdown and release window
	manager->Shutdown();
	delete manager;
	manager = 0;

	return 0;
}