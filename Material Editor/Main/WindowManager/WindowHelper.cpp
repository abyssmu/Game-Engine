#include "WindowManager.h"

auto directionSize = 120;
auto ambientSize = 120;
auto diffuseSize = 120;
auto specularSize = 170;

auto lightMenuSize = directionSize + ambientSize + diffuseSize + specularSize;
auto materialMenuSize = 300;

HWND CreateContainer(
	HBRUSH brush,
	WNDPROC proc,
	LPCSTR name,
	HWND parent);

HWND CreateStatic(
	LPCSTR text,
	HWND parent);

HWND CreateTrackbar(
	int min,
	int max,
	int start,
	HWND parent);

void HideLightMenu(
	HWND lightMenu)
{
	ShowWindow(lightMenu, SW_HIDE);
}

void HideMaterialMenu(
	HWND materialMenu)
{
	ShowWindow(materialMenu, SW_HIDE);
}

void ShowLightMenu(
	HWND lightMenu)
{
	ShowWindow(lightMenu, SW_SHOW);
}

void ShowMaterialMenu(
	HWND materialMenu)
{
	ShowWindow(materialMenu, SW_SHOW);
}

void SizeAmbient(
	HWND ambient,
	HWND ambientText,
	HWND ambientTextR,
	HWND ambientTextG,
	HWND ambientTextB,
	HWND ambientInputR,
	HWND ambientInputG,
	HWND ambientInputB,
	HWND lightMenu)
{
	auto rc = RECT();
	GetClientRect(lightMenu, &rc);

	auto w = int(rc.right);

	MoveWindow(ambient, 0, directionSize, w, ambientSize, false);

	MoveWindow(ambientText, 0, 0, w, 30, false);

	auto c = int(w * .1);

	MoveWindow(ambientTextR, 0, 30, c, 30, false);
	MoveWindow(ambientInputR, c, 30, w - c, 30, false);

	MoveWindow(ambientTextG, 0, 60, c, 30, false);
	MoveWindow(ambientInputG, c, 60, w - c, 30, false);

	MoveWindow(ambientTextB, 0, 90, c, 30, false);
	MoveWindow(ambientInputB, c, 90, w - c, 30, false);
}

void SizeContainer(
	HWND controlsContainer,
	HWND lightMenu,
	HWND materialMenu,
	double controlsPerc)
{
	auto rc = RECT();
	GetClientRect(ApplicationHandle->GetMain(), &rc);

	auto controlsHeight = int(rc.bottom);
	auto controlsWidth = int(rc.right * controlsPerc);

	MoveWindow(controlsContainer, rc.right - controlsWidth, rc.top, controlsWidth, controlsHeight, true);

	GetClientRect(controlsContainer, &rc);

	auto w = int(rc.right);

	MoveWindow(lightMenu, 0, 0, w, lightMenuSize, true);

	MoveWindow(materialMenu, 0, 0, w, materialMenuSize, true);
}

void SizeDiffuse(
	HWND diffuse,
	HWND diffuseText,
	HWND diffuseTextR,
	HWND diffuseTextG,
	HWND diffuseTextB,
	HWND diffuseInputR,
	HWND diffuseInputG,
	HWND diffuseInputB,
	HWND lightMenu)
{
	auto rc = RECT();
	GetClientRect(lightMenu, &rc);

	auto w = int(rc.right);

	MoveWindow(diffuse, 0, directionSize + ambientSize, w, diffuseSize, false);

	MoveWindow(diffuseText, 0, 0, w, 30, false);

	auto c = int(w * .1);

	MoveWindow(diffuseTextR, 0, 30, c, 30, false);
	MoveWindow(diffuseInputR, c, 30, w - c, 30, false);

	MoveWindow(diffuseTextG, 0, 60, c, 30, false);
	MoveWindow(diffuseInputG, c, 60, w - c, 30, false);

	MoveWindow(diffuseTextB, 0, 90, c, 30, false);
	MoveWindow(diffuseInputB, c, 90, w - c, 30, false);
}

void SizeDirection(
	HWND direction,
	HWND directionInputX,
	HWND directionInputY,
	HWND directionInputZ,
	HWND directionText,
	HWND directionTextX,
	HWND directionTextY,
	HWND directionTextZ,
	HWND lightMenu)
{
	auto rc = RECT();
	GetClientRect(lightMenu, &rc);

	auto w = int(rc.right);

	MoveWindow(direction, 0, 0, w, directionSize, false);

	MoveWindow(directionText, 0, 0, w, 30, false);

	auto c = int(w * .1);

	MoveWindow(directionTextX, 0, 30, c, 30, false);
	MoveWindow(directionInputX, c, 30, w - c, 30, false);

	MoveWindow(directionTextY, 0, 60, c, 30, false);
	MoveWindow(directionInputY, c, 60, w - c, 30, false);

	MoveWindow(directionTextZ, 0, 90, c, 30, false);
	MoveWindow(directionInputZ, c, 90, w - c, 30, false);
}

void SizeSpecular(
	HWND specular,
	HWND specularText,
	HWND specularPowerText,
	HWND specularPowerInput,
	HWND specularColorText,
	HWND specularColorTextR,
	HWND specularColorTextG,
	HWND specularColorTextB,
	HWND specularColorInputR,
	HWND specularColorInputG,
	HWND specularColorInputB,
	HWND lightMenu)
{
	auto rc = RECT();
	GetClientRect(lightMenu, &rc);

	auto w = int(rc.right);
	auto height = 20;
	auto c = int(w * .1);

	MoveWindow(specular, 0, directionSize + ambientSize + diffuseSize, w, specularSize, false);

	MoveWindow(specularText, 0, 0, w, 20, false);
	
	MoveWindow(specularPowerText, 0, 20, c, 30, false);
	MoveWindow(specularPowerInput, c, 20, w - c, 30, false);

	MoveWindow(specularColorText, 0, 50, w, 30, false);

	MoveWindow(specularColorTextR, 0, 80, c, 30, false);
	MoveWindow(specularColorInputR, c, 80, w - c, 30, false);

	MoveWindow(specularColorTextG, 0, 110, c, 30, false);
	MoveWindow(specularColorInputG, c, 110, w - c, 30, false);

	MoveWindow(specularColorTextB, 0, 140, c, 30, false);
	MoveWindow(specularColorInputB, c, 140, w - c, 30, false);
}

bool InitializeControlsContainer(
	HWND& controlsContainer,
	HWND& lightMenu,
	HWND& materialMenu,
	double controlsPerc)
{
	controlsContainer = CreateContainer(CreateSolidBrush(RGB(0, 128, 128)), WNDPROC(ControlsMessageHandler),
		"ControlsContainer", ApplicationHandle->GetMain());

	if (!controlsContainer)
	{
		return false;
	}

	lightMenu = CreateContainer(CreateSolidBrush(RGB(128, 128, 0)), WNDPROC(ControlsMessageHandler),
		"LightMenuContainer", controlsContainer);

	if (!lightMenu)
	{
		return false;
	}

	materialMenu = CreateContainer(CreateSolidBrush(RGB(128, 128, 128)), WNDPROC(ControlsMessageHandler),
		"MaterialMenuContainer", controlsContainer);

	if (!materialMenu)
	{
		return false;
	}

	SizeContainer(controlsContainer, lightMenu, materialMenu, controlsPerc);

	HideLightMenu(lightMenu);
	HideMaterialMenu(materialMenu);

	return true;
}

bool InitializeAmbient(
	HWND& ambient,
	HWND& ambientText,
	HWND& ambientTextR,
	HWND& ambientTextG,
	HWND& ambientTextB,
	HWND& ambientInputR,
	HWND& ambientInputG,
	HWND& ambientInputB,
	HWND& lightMenu)
{
	ambient = CreateContainer(CreateSolidBrush(RGB(0, 128, 0)), WNDPROC(ControlsMessageHandler),
		"LightContainer", lightMenu);

	if (!ambient)
	{
		return false;
	}

	ambientText = CreateStatic("Ambient", ambient);

	ambientTextR = CreateStatic("R", ambient);
	ambientTextG = CreateStatic("G", ambient);
	ambientTextB = CreateStatic("B", ambient);

	ambientInputR = CreateTrackbar(0, 255, 128, ambient);
	ambientInputG = CreateTrackbar(0, 255, 128, ambient);
	ambientInputB = CreateTrackbar(0, 255, 128, ambient);

	return true;
}

bool InitializeDirection(
	HWND& direction,
	HWND& directionInputX,
	HWND& directionInputY,
	HWND& directionInputZ,
	HWND& directionText,
	HWND& directionTextX,
	HWND& directionTextY,
	HWND& directionTextZ,
	HWND& lightMenu)
{
	direction = CreateContainer(CreateSolidBrush(RGB(128, 0, 0)), WNDPROC(ControlsMessageHandler),
		"DirectionContainer", lightMenu);

	if (!direction)
	{
		return false;
	}

	directionText = CreateStatic("Direction", direction);
	
	directionInputX = CreateTrackbar(0, 100, 50, direction);
	directionTextX = CreateStatic("X", direction);

	directionInputY = CreateTrackbar(0, 100, 50, direction);
	directionTextY = CreateStatic("Y", direction);

	directionInputZ = CreateTrackbar(0, 100, 100, direction);
	directionTextZ = CreateStatic("Z", direction);

	return true;
}

bool InitializeDiffuse(
	HWND& diffuse,
	HWND& diffuseText,
	HWND& diffuseTextR,
	HWND& diffuseTextG,
	HWND& diffuseTextB,
	HWND& diffuseInputR,
	HWND& diffuseInputG,
	HWND& diffuseInputB,
	HWND& lightMenu)
{
	diffuse = CreateContainer(CreateSolidBrush(RGB(128, 0, 128)), WNDPROC(ControlsMessageHandler),
		"LightContainer", lightMenu);

	if (!diffuse)
	{
		return false;
	}

	diffuseText = CreateStatic("Diffuse", diffuse);

	diffuseTextR = CreateStatic("R", diffuse);
	diffuseTextG = CreateStatic("G", diffuse);
	diffuseTextB = CreateStatic("B", diffuse);

	diffuseInputR = CreateTrackbar(0, 255, 255, diffuse);
	diffuseInputG = CreateTrackbar(0, 255, 255, diffuse);
	diffuseInputB = CreateTrackbar(0, 255, 255, diffuse);

	return true;
}

bool InitializeSpecular(
	HWND& specular,
	HWND& specularText,
	HWND& specularPowerText,
	HWND& specularPowerInput,
	HWND& specularColorText,
	HWND& specularColorTextR,
	HWND& specularColorTextG,
	HWND& specularColorTextB,
	HWND& specularColorInputR,
	HWND& specularColorInputG,
	HWND& specularColorInputB,
	HWND& lightMenu)
{
	specular = CreateContainer(CreateSolidBrush(RGB(0, 0, 128)), WNDPROC(ControlsMessageHandler),
		"SpecularContainer", lightMenu);

	if (!specular)
	{
		return false;
	}
	
	specularText = CreateStatic("Specular", specular);

	specularPowerText = CreateStatic("P", specular);
	specularPowerInput = CreateTrackbar(1, 10, 5, specular);

	specularColorText = CreateStatic("Color", specular);

	specularColorTextR = CreateStatic("R", specular);
	specularColorTextG = CreateStatic("G", specular);
	specularColorTextB = CreateStatic("B", specular);

	specularColorInputR = CreateTrackbar(0, 255, 255, specular);
	specularColorInputG = CreateTrackbar(0, 255, 255, specular);
	specularColorInputB = CreateTrackbar(0, 255, 255, specular);

	return true;
}

HWND CreateContainer(
	HBRUSH brush,
	WNDPROC proc,
	LPCSTR name,
	HWND parent)
{
	auto wc = WNDCLASSEX();

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WNDPROC(ControlsMessageHandler);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = ApplicationHandle->GetHInstance();
	wc.hIcon = 0;
	wc.hIconSm = 0;
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = brush;
	wc.lpszMenuName = 0;
	wc.lpszClassName = name;
	wc.cbSize = sizeof(WNDCLASSEX);

	RegisterClassEx(&wc);

	HWND win = CreateWindowEx(WS_EX_APPWINDOW, name, 0,
		WS_POPUP | WS_CHILD | WS_VISIBLE,
		0, 0, 0, 0, 0, 0, ApplicationHandle->GetHInstance(), 0);

	if (!win)
	{
		return 0;
	}

	SetParent(win, parent);
	SetMenu(win, 0);

	return win;
}

HWND CreateStatic(
	LPCSTR text,
	HWND parent)
{
	auto style = WS_CHILD | WS_VISIBLE | SS_CENTER;

	auto stat = CreateWindow("STATIC", text, style, 0, 0, 0, 0, parent, 0, ApplicationHandle->GetHInstance(), 0);

	return stat;
}

HWND CreateTrackbar(
	int min,
	int max,
	int start,
	HWND parent)
{
	auto trackbar = CreateWindowEx(0, TRACKBAR_CLASS, "",
		WS_CHILD | WS_VISIBLE | TBS_NOTICKS,
		0, 0, 0, 0, parent, 0, ApplicationHandle->GetHInstance(), 0);

	SendMessage(trackbar, TBM_SETRANGE, WPARAM(TRUE), LPARAM(MAKELONG(min, max)));
	SendMessage(trackbar, TBM_SETSEL, WPARAM(FALSE), LPARAM(MAKELONG(0, 1)));
	SendMessage(trackbar, TBM_SETPOS, WPARAM(TRUE), LPARAM(start));

	return trackbar;
}