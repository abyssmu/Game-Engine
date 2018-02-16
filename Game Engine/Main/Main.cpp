//Includes

//Class Includes
#include "System\System.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR pScmdline, int iCmdshow)
{
	ShowCursor(true);

	SystemClass* System;
	bool result;

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

	ShowCursor(true);

	return 0;
}