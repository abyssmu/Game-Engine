#include "Light.h"

Colors::Color Light::GetAmbientColor()
{
	return m_ambientColor;
}

Colors::Color Light::GetDiffuseColor()
{
	return m_diffuseColor;
}

Colors::Color Light::GetSpecularColor()
{
	return m_specularColor;
}

double Light::GetSpecularPower()
{
	return m_specularPower;
}

void Light::SetAmbientColor(
	Colors::Color c)
{
	m_ambientColor = c;
}

void Light::SetDiffuseColor(
	Colors::Color c)
{
	m_diffuseColor = c;
}

void Light::SetSpecularColor(
	Colors::Color c)
{
	m_specularColor = c;
}

void Light::SetSpecularPower(
	double p)
{
	m_specularPower = p;
}