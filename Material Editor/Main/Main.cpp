/*
Custom built game engine by Sean (Alex) Womack.

Most everything in here is custom built. The excpetions are the Assimp library and the DirectX library.
Their corresponding classes are custom and used as an interface/wrapper.

See UpdateLog.txt for completed and future updates along with routine list.
*/

#include "WindowManager\WindowManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR pScmdline, int iCmdshow)
{
	WindowManager* winManager = new WindowManager;
	if (!winManager)
	{
		return false;
	}

	if (winManager->Initialize(720, 1080))
	{
		winManager->Run();
	}

	winManager->Shutdown();
	delete winManager;
	winManager = 0;

	return 0;
}