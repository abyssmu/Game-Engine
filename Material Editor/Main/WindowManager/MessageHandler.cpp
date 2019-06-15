#include "WindowManager.h"

LRESULT CALLBACK ControlsMessageHandler(
	HWND hwnd,
	UINT umsg,
	WPARAM wparam,
	LPARAM lparam)
{
	switch (umsg)
	{
	case WM_DESTROY:

	default:
		if (!ApplicationHandle->CheckResizeWindow())
		{
			ApplicationHandle->SizeWorld();
		}

		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
}

LRESULT CALLBACK MainMessageHandler(
	HWND hwnd,
	UINT umsg,
	WPARAM wparam,
	LPARAM lparam)
{
	if (ApplicationHandle)
	{
		ApplicationHandle->SetMouseState(false);
	}

	switch (umsg)
	{
	case WM_ACTIVATE:
		switch LOWORD(wparam)
		{
		case WA_ACTIVE:
			return 0;

		case WA_CLICKACTIVE:
			SendMessage(hwnd, WM_NCACTIVATE, TRUE, 0);

			return 0;

		case WA_INACTIVE:
			if ((HWND)lparam != hwnd)
			{
				SendMessage(hwnd, WM_NCACTIVATE, TRUE, 0);

				return 0;
			};
		}

	case WM_CLOSE:
		PostQuitMessage(0);

		return 0;

	case WM_COMMAND:
	{
		int iD = LOWORD(wparam);

		switch (iD)
		{
			//File menu actions
		case IDF_OPEN:
			ApplicationHandle->OpenFile();

			return 0;

		case IDF_EXIT:
			PostQuitMessage(0);

			return 0;

			//Material menu actions

			//Model menu cations
		case IDMOD_CUBE:
			ApplicationHandle->UpdateModel("Cube");

			return 0;

		case IDMOD_HUMANMALE:
			ApplicationHandle->UpdateModel("HumanMale");

			return 0;

		case IDMOD_MONKEY:
			ApplicationHandle->UpdateModel("Monkey");

			return 0;

		case IDMOD_SPHERE:
			ApplicationHandle->UpdateModel("Sphere");

			return 0;

		default:
			return DefWindowProc(hwnd, umsg, wparam, lparam);
		}
	}

	case WM_DESTROY:
		PostQuitMessage(0);

		return 0;

	case WM_SIZE:
	{
		auto sys = ApplicationHandle->CheckSystem();
		auto min = ApplicationHandle->GetMinimized();

		if ((wparam == SIZE_MINIMIZED) && sys && !min)
		{
			min = true;
			ApplicationHandle->SetMinimized(min);

			return 0;
		}
		else if ((wparam == 0) && sys && min)
		{
			min = false;
			ApplicationHandle->SetMinimized(min);

			return 0;
		}

		return 0;
	}

	default:
		if (!ApplicationHandle->CheckResizeWindow())
		{
			ApplicationHandle->SizeWorld();
		}

		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
}

LRESULT CALLBACK WorldMessageHandler(
	HWND hwnd,
	UINT umsg,
	WPARAM wparam,
	LPARAM lparam)
{
	ApplicationHandle->SetMouseState(true);

	switch (umsg)
	{
	case WM_KEYDOWN:
		ApplicationHandle->KeyDown((unsigned int)wparam);

		return 0;

	case WM_KEYUP:
		ApplicationHandle->KeyUp((unsigned int)wparam);

		return 0;

	default:
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
}