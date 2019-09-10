/*
Defines the parent light class used to hold basics for all lights.
*/

#pragma once

//Class Includes
#include "../../Color/Color.h"
#include "../Entity/Entity.h"

class Light : public Entity
{
public:
	Colors::Color GetAmbientColor();
	Colors::Color GetDiffuseColor();
	Colors::Color GetSpecularColor();
	double GetSpecularPower();

	void SetAmbientColor(
		Colors::Color c);
	void SetDiffuseColor(
		Colors::Color c);
	void SetSpecularColor(
		Colors::Color c);
	void SetSpecularPower(
		double p);

private:
	Colors::Color m_ambientColor = Colors::White();
	Colors::Color m_diffuseColor = Colors::White();
	Colors::Color m_specularColor = Colors::White();
	double m_specularPower = 0;
};