/*
WindowHelper class is meant to encapsulate the functions for creating and editing WinAPI windows.
*/

#pragma once

#include <Windows.h>

HWND controlsContainer = 0;

HWND lightMenu = 0;

HWND direction = 0;
HWND directionText = 0;
HWND directionTextX = 0, directionTextY = 0, directionTextZ = 0;
HWND directionInputX = 0, directionInputY = 0, directionInputZ = 0;

HWND ambient = 0;
HWND ambientText = 0;
HWND ambientTextR = 0, ambientTextG = 0, ambientTextB = 0;
HWND ambientInputR = 0, ambientInputG = 0, ambientInputB = 0;

HWND diffuse = 0;
HWND diffuseText = 0;
HWND diffuseTextR = 0, diffuseTextG = 0, diffuseTextB = 0;
HWND diffuseInputR = 0, diffuseInputG = 0, diffuseInputB = 0;

HWND specular = 0;
HWND specularText = 0;
HWND specularPowerText = 0;
HWND specularPowerInput = 0;
HWND specularColorText = 0;
HWND specularColorTextR = 0, specularColorTextG = 0, specularColorTextB = 0;
HWND specularColorInputR = 0, specularColorInputG = 0, specularColorInputB = 0;

HWND materialMenu = 0;

int controlsHeight = 0, controlsWidth = 0;

double controlsPerc = 0.2;

void HideLightMenu(
	HWND lightMenu);
void HideMaterialMenu(
	HWND materialMenu);

void ShowLightMenu(
	HWND lightMenu);
void ShowMaterialMenu(
	HWND materialMenu);

void SizeAmbient(
	HWND ambient,
	HWND ambientText,
	HWND ambientTextR,
	HWND ambientTextG,
	HWND ambientTextB,
	HWND ambientInputR,
	HWND ambientInputG,
	HWND ambientInputB,
	HWND lightMenu);
void SizeContainer(
	HWND controlsContainer,
	HWND lightMenu,
	HWND materialMenu,
	double controlsPerc);
void SizeDiffuse(
	HWND diffuse,
	HWND diffuseText,
	HWND diffuseTextR,
	HWND diffuseTextG,
	HWND diffuseTextB,
	HWND diffuseInputR,
	HWND diffuseInputG,
	HWND diffuseInputB,
	HWND lightMenu);
void SizeDirection(
	HWND direction,
	HWND directionInputX,
	HWND directionInputY,
	HWND directionInputZ,
	HWND directionText,
	HWND directionTextX,
	HWND directionTextY,
	HWND directionTextZ,
	HWND lightMenu);
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
	HWND lightMenu);

bool InitializeAmbient(
	HWND& ambient,
	HWND& ambientText,
	HWND& ambientTextR,
	HWND& ambientTextG,
	HWND& ambientTextB,
	HWND& ambientInputR,
	HWND& ambientInputG,
	HWND& ambientInputB,
	HWND& lightMenu);
bool InitializeControlsContainer(
	HWND& controlsContainer,
	HWND& lightMenu,
	HWND& materialMenu,
	double controlsPerc);
bool InitializeDiffuse(
	HWND& diffuse,
	HWND& diffuseText,
	HWND& diffuseTextR,
	HWND& diffuseTextG,
	HWND& diffuseTextB,
	HWND& diffuseInputR,
	HWND& diffuseInputG,
	HWND& diffuseInputB,
	HWND& lightMenu);
bool InitializeDirection(
	HWND& direction,
	HWND& directionInputX,
	HWND& directionInputY,
	HWND& directionInputZ,
	HWND& directionText,
	HWND& directionTextX,
	HWND& directionTextY,
	HWND& directionTextZ,
	HWND& lightMenu);
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
	HWND& lightMenu);