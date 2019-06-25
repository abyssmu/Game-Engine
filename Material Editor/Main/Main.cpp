/*
Custom built game engine by Sean (Alex) Robinson.

Most everything in here is custom built. The excpetions are the Assimp library and the DirectX library.
Their corresponding classes are custom and used as an interface.

See UpdateLog.txt for completed and future updates along with routine list.
*/

#include "WindowManager\WindowManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR pScmdline, int iCmdshow)
{
	WindowManager* manager = new WindowManager;
	if (!manager)
	{
		return false;
	}

	if (manager->Initialize(720, 1080))
	{
		manager->Run();
	}

	manager->Shutdown();
	delete manager;
	manager = 0;

	return 0;
}