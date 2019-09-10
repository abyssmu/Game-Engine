/*
Texture class imports .tga files and stores information for model use.
*/

#pragma

#include <DirectXTex-master/DirectXTex/DirectXTex.h>

#include <stdio.h>

class Texture
{
public:
	bool Initialize(
		ID3D11Device* device,
		const wchar_t* filename);
	void Shutdown();
	ID3D11ShaderResourceView* GetTexture();

private:
	bool InitializeTexture(
		ID3D11Device* device,
		const wchar_t* filename);

	ID3D11ShaderResourceView* m_resource = 0;
};