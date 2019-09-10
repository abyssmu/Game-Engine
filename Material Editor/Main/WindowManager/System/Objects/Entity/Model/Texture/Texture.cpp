#include "Texture.h"

bool Texture::Initialize(
	ID3D11Device* device,
	const wchar_t* filename)
{
	if (!InitializeTexture(device, filename))
	{
		return false;
	}
	
	return true;
}

void Texture::Shutdown()
{
	if (m_resource)
	{
		m_resource->Release();
		m_resource = 0;
	}
}

ID3D11ShaderResourceView* Texture::GetTexture()
{
	return m_resource;
}

bool Texture::InitializeTexture(
	ID3D11Device* device,
	const wchar_t* filename)
{
	DirectX::ScratchImage image;

	auto result = DirectX::LoadFromTGAFile(filename, 0, image);

	if (FAILED(result))
	{
		return false;
	}

	result = DirectX::CreateShaderResourceView(device, image.GetImages(),
		image.GetImageCount(), image.GetMetadata(), &m_resource);

	if (FAILED(result))
	{
		return false;
	}

	return true;
}