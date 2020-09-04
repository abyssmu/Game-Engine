#include "WindowHelper.h"
#include "WindowManager.h"

auto lightDirX = 0.0;
auto lightDirY = 0.0;
auto lightDirZ = 1.0;

auto specularR = 1.0;
auto specularG = 1.0;
auto specularB = 1.0;
auto specularP = 32.0;

auto ambientR = 0.5;
auto ambientG = 0.5;
auto ambientB = 0.5;

auto diffuseR = 1.0;
auto diffuseG = 1.0;
auto diffuseB = 1.0;

void HandleAmbient(LPARAM lparam);
void HandleDiffuse(LPARAM lparam);
void HandleDirection(LPARAM lparam);
void HandleSpecular(LPARAM lparam);

LRESULT CALLBACK ControlsMessageHandler(
	HWND hwnd,
	UINT umsg,
	WPARAM wparam,
	LPARAM lparam)
{
	LPWORD val;
	double pos;

	HBRUSH bkgrd = 0;

	switch (umsg)
	{
	case WM_ACTIVATE:
	{
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
	}

	case WM_COMMAND:

		return 0;

	case WM_HSCROLL:
		HandleAmbient(lparam);
		HandleDiffuse(lparam);
		HandleDirection(lparam);
		HandleSpecular(lparam);

		return 0;

	default:
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
}

LRESULT CALLBACK MainMessageHandler(
	HWND hwnd,
	UINT umsg,
	WPARAM wparam,
	LPARAM lparam)
{
	switch (umsg)
	{
	case WM_ACTIVATE:
		switch LOWORD(wparam)
		{
		case WA_ACTIVE:
			if (!controlsContainer && ApplicationHandle->GetMain())
			{
				InitializeControlsContainer(controlsContainer, lightMenu, materialMenu, controlsPerc);
			}

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
		case IDMOD_BEDROOM:
			ApplicationHandle->UpdateModel("Bedroom");
			
			return 0;

		case IDMOD_BIRD:
			ApplicationHandle->UpdateModel("Bird");

			return 0;

		case IDMOD_CUBE:
			ApplicationHandle->UpdateModel("Cube");

			return 0;

		case IDMOD_DRAGON:
			ApplicationHandle->UpdateModel("Dragon");

			return 0;

		case IDMOD_HUMANMALE:
			ApplicationHandle->UpdateModel("HumanMale");

			return 0;

		case IDMOD_MONKEY:
			ApplicationHandle->UpdateModel("Monkey");

			return 0;

		case IDMOD_SKULL:
			ApplicationHandle->UpdateModel("Skull");

			return 0;

		case IDMOD_SOFA:
			ApplicationHandle->UpdateModel("Sofa");

			return 0;

		case IDMOD_SPHERE:
			ApplicationHandle->UpdateModel("Sphere");

			return 0;

		case IDMOD_TREE:
			ApplicationHandle->UpdateModel("Tree");

			return 0;

		case IDCON_LIGHT:
			if (!direction && controlsContainer)
			{
				InitializeAmbient(ambient, ambientText,
					ambientTextR, ambientTextG, ambientTextB,
					ambientInputR, ambientInputG, ambientInputB,
					lightMenu);
				SizeAmbient(ambient, ambientText,
					ambientTextR, ambientTextG, ambientTextB,
					ambientInputR, ambientInputG, ambientInputB,
					lightMenu);

				InitializeDiffuse(diffuse, diffuseText,
					diffuseTextR, diffuseTextG, diffuseTextB,
					diffuseInputR, diffuseInputG, diffuseInputB,
					lightMenu);
				SizeDiffuse(diffuse, diffuseText,
					diffuseTextR, diffuseTextG, diffuseTextB,
					diffuseInputR, diffuseInputG, diffuseInputB,
					lightMenu);
				
				InitializeDirection(direction,
					directionInputX, directionInputY, directionInputZ,
					directionText,
					directionTextX, directionTextY, directionTextZ,
					lightMenu);
				SizeDirection(direction,
					directionInputX, directionInputY, directionInputZ,
					directionText,
					directionTextX, directionTextY, directionTextZ,
					lightMenu);

				InitializeSpecular(specular, specularText, specularPowerText, specularPowerInput,
					specularColorText,
					specularColorTextR, specularColorTextG, specularColorTextB,
					specularColorInputR, specularColorInputG, specularColorInputB,
					lightMenu);
				SizeSpecular(specular, specularText, specularPowerText, specularPowerInput,
					specularColorText,
					specularColorTextR, specularColorTextG, specularColorTextB,
					specularColorInputR, specularColorInputG, specularColorInputB,
					lightMenu);

				ShowLightMenu(lightMenu);
			}
			else
			{
				if (lightMenu)
				{
					HideMaterialMenu(materialMenu);

					ShowLightMenu(lightMenu);
				}
			}

			return 0;

		case IDCON_MATERIAL:
			if (materialMenu)
			{
				HideLightMenu(lightMenu);
				
				ShowMaterialMenu(materialMenu);
			}

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
			ApplicationHandle->Resize();

			if (controlsContainer)
			{
				SizeContainer(controlsContainer, lightMenu, materialMenu, controlsPerc);
				
				SizeAmbient(ambient, ambientText,
					ambientTextR, ambientTextG, ambientTextB,
					ambientInputR, ambientInputG, ambientInputB,
					lightMenu);

				SizeDiffuse(diffuse, diffuseText,
					diffuseTextR, diffuseTextG, diffuseTextB,
					diffuseInputR, diffuseInputG, diffuseInputB,
					lightMenu);

				SizeDirection(direction,
					directionInputX, directionInputY, directionInputZ,
					directionText,
					directionTextX, directionTextY, directionTextZ,
					lightMenu);

				SizeSpecular(specular, specularText, specularPowerText, specularPowerInput,
					specularColorText,
					specularColorTextR, specularColorTextG, specularColorTextB,
					specularColorInputR, specularColorInputG, specularColorInputB,
					lightMenu);
			}
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
	switch (umsg)
	{
	case WM_ACTIVATE:
	{
		switch LOWORD(wparam)
		{
		case WA_ACTIVE:
			return 0;

		case WA_CLICKACTIVE:
			ApplicationHandle->SetWorldActive(1);
			ApplicationHandle->RegisterInput();

			SendMessage(hwnd, WM_NCACTIVATE, TRUE, 0);

			return 0;

		case WA_INACTIVE:
			if (ApplicationHandle->GetWorldActive())
			{
				ApplicationHandle->ResetKeys();
			}

			ApplicationHandle->SetWorldActive(0);
			ApplicationHandle->UnregisterInput();

			if ((HWND)lparam != hwnd)
			{
				SendMessage(hwnd, WM_NCACTIVATE, TRUE, 0);

				return 0;
			};
		}
	}

	case WM_INPUT:
	{
		if (ApplicationHandle->GetWorldActive())
		{
			char buffer[sizeof(RAWINPUT)] = {};
			UINT size = sizeof(RAWINPUT);

			GetRawInputData(reinterpret_cast<HRAWINPUT>(lparam), RID_INPUT, buffer,
				&size, sizeof(RAWINPUTHEADER));

			RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(buffer);

			if (raw->header.dwType == RIM_TYPEKEYBOARD)
			{
				RAWKEYBOARD& rawKb = raw->data.keyboard;

				ApplicationHandle->Keyboard(rawKb);
			}
		}
	}

	default:
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
}

void HandleAmbient(LPARAM lparam)
{
	LRESULT pos;

	if ((HWND)lparam == ambientInputR)
	{
		pos = SendMessage(ambientInputR, TBM_GETPOS, 0, 0);

		ambientR = pos / 255.0;

		ApplicationHandle->SetLightAmbient(ambientR, ambientG, ambientB);
	}
	else if ((HWND)lparam == ambientInputG)
	{
		pos = SendMessage(ambientInputG, TBM_GETPOS, 0, 0);

		ambientG = pos / 255.0;

		ApplicationHandle->SetLightAmbient(ambientR, ambientG, ambientB);
	}
	else if ((HWND)lparam == ambientInputB)
	{
		pos = SendMessage(ambientInputB, TBM_GETPOS, 0, 0);

		ambientB = pos / 255.0;

		ApplicationHandle->SetLightAmbient(ambientR, ambientG, ambientB);
	}
}

void HandleDiffuse(LPARAM lparam)
{
	LRESULT pos;

	if ((HWND)lparam == diffuseInputR)
	{
		pos = SendMessage(diffuseInputR, TBM_GETPOS, 0, 0);

		diffuseR = pos / 255.0;

		ApplicationHandle->SetLightDiffuse(diffuseR, diffuseG, diffuseB);
	}
	else if ((HWND)lparam == diffuseInputG)
	{
		pos = SendMessage(diffuseInputG, TBM_GETPOS, 0, 0);

		diffuseG = pos / 255.0;

		ApplicationHandle->SetLightDiffuse(diffuseR, diffuseG, diffuseB);
	}
	else if ((HWND)lparam == diffuseInputB)
	{
		pos = SendMessage(diffuseInputB, TBM_GETPOS, 0, 0);

		diffuseB = pos / 255.0;

		ApplicationHandle->SetLightDiffuse(diffuseR, diffuseG, diffuseB);
	}
}

void HandleDirection(LPARAM lparam)
{
	LRESULT pos;

	if ((HWND)lparam == directionInputX)
	{
		pos = SendMessage(directionInputX, TBM_GETPOS, 0, 0);

		lightDirX = pos / 10.0 - 5.0;

		ApplicationHandle->SetLightDirection(lightDirX, lightDirY, lightDirZ);
	}
	else if ((HWND)lparam == directionInputY)
	{
		pos = SendMessage(directionInputY, TBM_GETPOS, 0, 0);

		lightDirY = pos / 10.0 - 5.0;

		ApplicationHandle->SetLightDirection(lightDirX, lightDirY, lightDirZ);
	}
	else if ((HWND)lparam == directionInputZ)
	{
		pos = SendMessage(directionInputZ, TBM_GETPOS, 0, 0);

		lightDirZ = pos / 100.0;

		ApplicationHandle->SetLightDirection(lightDirX, lightDirY, lightDirZ);
	}
}

void HandleSpecular(LPARAM lparam)
{
	LRESULT pos;
	
	if ((HWND)lparam == specularPowerInput)
	{
		pos = SendMessage(specularPowerInput, TBM_GETPOS, 0, 0);

		specularP = pow(2.0, pos);

		ApplicationHandle->SetSpecular(specularR, specularG, specularB, specularP);
	}
	else if ((HWND)lparam == specularColorInputR)
	{
		pos = SendMessage(specularColorInputR, TBM_GETPOS, 0, 0);

		specularR = pos / 255.0;

		ApplicationHandle->SetSpecular(specularR, specularG, specularB, specularP);
	}
	else if ((HWND)lparam == specularColorInputG)
	{
		pos = SendMessage(specularColorInputG, TBM_GETPOS, 0, 0);

		specularG = pos / 255.0;

		ApplicationHandle->SetSpecular(specularR, specularG, specularB, specularP);
	}
	else if ((HWND)lparam == specularColorInputB)
	{
		pos = SendMessage(specularColorInputB, TBM_GETPOS, 0, 0);

		specularB = pos / 255.0;

		ApplicationHandle->SetSpecular(specularR, specularG, specularB, specularP);
	}
}