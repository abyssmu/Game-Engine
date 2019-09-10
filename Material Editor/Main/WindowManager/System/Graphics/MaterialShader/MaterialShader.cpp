#include "MaterialShader.h"

bool MaterialShader::Initialize(
	ID3D11Device* device,
	HWND& hwnd)
{
	auto vs = LPCWSTR(L"Main/WindowManager/System/Graphics/MaterialShader/MaterialShader_vs.hlsl");
	auto ps = LPCWSTR(L"Main/WindowManager/System/Graphics/MaterialShader/MaterialShader_ps.hlsl");

	if (!InitializeShader(device, hwnd, vs, ps))
	{
		return false;
	}

	return true;
}

bool MaterialShader::Render(
	ID3D11DeviceContext* deviceContext,
	int& indexCount,
	DirectX::XMMATRIX& worldMatrix, 
	DirectX::XMMATRIX& viewMatrix,
	DirectX::XMMATRIX projectionMatrix,
	DirectX::XMFLOAT3 lightDirection,
	DirectX::XMFLOAT4 ambientColor,
	DirectX::XMFLOAT4 diffuseColor,
	DirectX::XMFLOAT3 cameraPosition,
	DirectX::XMFLOAT4 specularColor,
	double specularPower)
{
	if (!SetShaderParameters(deviceContext, worldMatrix, viewMatrix,
		projectionMatrix, lightDirection, ambientColor, diffuseColor,
		cameraPosition, specularColor, specularPower))
	{
		return false;
	}

	RenderShader(deviceContext, indexCount);

	return true;
}

void MaterialShader::Shutdown()
{
	ShutdownShader();
}

bool MaterialShader::CompilerShaders(
	ID3D11Device* device,
	HWND& hwnd, 
	LPCWSTR& vsFilename,
	LPCWSTR& psFilename)
{
	ID3D10Blob* errorMessage = 0;

	auto result = D3DCompileFromFile(vsFilename, 0, 0, "main",
		"vs_5_0", D3DCOMPILE_SKIP_OPTIMIZATION | D3DCOMPILE_DEBUG,
		0, &vertexShaderBuffer, &errorMessage);
	if (FAILED(result))
	{
		if (errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, hwnd, vsFilename);
		}
		else
		{
			MessageBox(hwnd, (LPCSTR)vsFilename,
				"Missing shader file", 0);
		}

		return false;
	}

	result = D3DCompileFromFile(psFilename, 0, 0, "main",
		"ps_5_0", D3DCOMPILE_SKIP_OPTIMIZATION | D3DCOMPILE_DEBUG,
		0, &pixelShaderBuffer, &errorMessage);
	if (FAILED(result))
	{
		if (errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, hwnd, psFilename);
		}
		else
		{
			MessageBox(hwnd, (LPCSTR)psFilename,
				"Missing shader file", 0);
		}

		return false;
	}

	result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(), 0, &m_vertexShader);
	if (FAILED(result))
	{
		return false;
	}

	result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(),
		pixelShaderBuffer->GetBufferSize(), 0, &m_pixelShader);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

bool MaterialShader::CreateCameraCB(
	ID3D11Device* device)
{
	auto cameraBufferDesc = D3D11_BUFFER_DESC();

	cameraBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	cameraBufferDesc.ByteWidth = sizeof(CameraBufferType);
	cameraBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cameraBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cameraBufferDesc.MiscFlags = 0;
	cameraBufferDesc.StructureByteStride = 0;

	auto result = device->CreateBuffer(&cameraBufferDesc, 0, &m_cameraBuffer);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

bool MaterialShader::CreateCameraDP(
	ID3D11DeviceContext* deviceContext,
	DirectX::XMFLOAT3& cameraPosition)
{
	auto mappedResource = D3D11_MAPPED_SUBRESOURCE();

	auto result = deviceContext->Map(m_cameraBuffer, 0, D3D11_MAP_WRITE_DISCARD,
		0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	auto dataPtr = (CameraBufferType*)mappedResource.pData;

	dataPtr->cameraPosition = cameraPosition;
	dataPtr->pad = 0.0;

	deviceContext->Unmap(m_cameraBuffer, 0);

	auto bufferNumber = 1;

	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_cameraBuffer);

	return true;
}

bool MaterialShader::CreateLayout(
	ID3D11Device* device)
{
	D3D11_INPUT_ELEMENT_DESC polygonLayout[4];

	polygonLayout[0].SemanticName = "COLOR";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "NORMAL";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	polygonLayout[2].SemanticName = "POSITION";
	polygonLayout[2].SemanticIndex = 0;
	polygonLayout[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[2].InputSlot = 0;
	polygonLayout[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[2].InstanceDataStepRate = 0;

	polygonLayout[3].SemanticName = "TEXCOORD";
	polygonLayout[3].SemanticIndex = 0;
	polygonLayout[3].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[3].InputSlot = 0;
	polygonLayout[3].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[3].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[3].InstanceDataStepRate = 0;

	auto numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	auto result = device->CreateInputLayout(polygonLayout, UINT(numElements),
		vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(), &m_layout);
	if (FAILED(result))
	{
		return false;
	}

	vertexShaderBuffer->Release();
	vertexShaderBuffer = 0;

	pixelShaderBuffer->Release();
	pixelShaderBuffer = 0;

	return true;
}

bool MaterialShader::CreateLightCB(
	ID3D11Device* device)
{
	auto lightBufferDesc = D3D11_BUFFER_DESC();

	lightBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	lightBufferDesc.ByteWidth = sizeof(LightBufferType);
	lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	lightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	lightBufferDesc.MiscFlags = 0;
	lightBufferDesc.StructureByteStride = 0;

	auto result = device->CreateBuffer(&lightBufferDesc, 0, &m_lightBuffer);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

bool MaterialShader::CreateLightDP(
	ID3D11DeviceContext* deviceContext,
	DirectX::XMFLOAT4& ambientColor,
	DirectX::XMFLOAT4& diffuseColor,
	DirectX::XMFLOAT3& lightDirection,
	DirectX::XMFLOAT4& specularColor,
	double& specularPower)
{
	auto mappedResource = D3D11_MAPPED_SUBRESOURCE();

	auto result = deviceContext->Map(m_lightBuffer, 0, D3D11_MAP_WRITE_DISCARD,
		0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	auto dataPtr = (LightBufferType*)mappedResource.pData;

	dataPtr->ambientColor = ambientColor;
	dataPtr->diffuseColor = diffuseColor;
	dataPtr->lightDirection = lightDirection;
	dataPtr->specularColor = specularColor;
	dataPtr->specularPower = (float)specularPower;

	deviceContext->Unmap(m_lightBuffer, 0);

	auto bufferNumber = 0;

	deviceContext->PSSetConstantBuffers(bufferNumber, 1, &m_lightBuffer);

	return true;
}

bool MaterialShader::CreateMatrixCB(
	ID3D11Device* device)
{
	auto matrixBufferDesc = D3D11_BUFFER_DESC();

	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	auto result = device->CreateBuffer(&matrixBufferDesc, 0, &m_matrixBuffer);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

bool MaterialShader::CreateMatrixDP(
	ID3D11DeviceContext* deviceContext,
	DirectX::XMMATRIX& worldMatrix,
	DirectX::XMMATRIX& viewMatrix,
	DirectX::XMMATRIX& projectionMatrix)
{
	auto mappedResource = D3D11_MAPPED_SUBRESOURCE();

	auto result = deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD,
		0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	auto dataPtr = (MatrixBufferType*)mappedResource.pData;

	dataPtr->world = worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projectionMatrix;

	deviceContext->Unmap(m_matrixBuffer, 0);

	auto bufferNumber = 0;

	deviceContext->VSSetConstantBuffers(bufferNumber, 1,
		&m_matrixBuffer);

	return true;
}

bool MaterialShader::InitializeShader(
	ID3D11Device* device,
	HWND& hwnd,
	LPCWSTR& vsFilename,
	LPCWSTR& psFilename)
{
	if (!CompilerShaders(device, hwnd, vsFilename, psFilename))
	{
		return false;
	}

	if (!CreateLayout(device))
	{
		return false;
	}

	if (!CreateMatrixCB(device))
	{
		return false;
	}

	if (!CreateCameraCB(device))
	{
		return false;
	}

	if (!CreateLightCB(device))
	{
		return false;
	}

	return true;
}

void MaterialShader::OutputShaderErrorMessage(
	ID3D10Blob* errorMessage,
	HWND& hwnd,
	LPCWSTR& shaderFile)
{
	auto fout = std::ofstream("shader-error.txt");
	auto compilerErrors = (char*)errorMessage->GetBufferPointer();
	auto bufferSize = (unsigned long)errorMessage->GetBufferSize();

	for (auto i = 0u; i < bufferSize; ++i)
	{
		fout << compilerErrors[i];
	}

	fout.close();

	errorMessage->Release();
	errorMessage = 0;

	MessageBox(hwnd, "Error compiling shader. Check shader-error.txt.",
		(LPCSTR)shaderFile, MB_OK);
}

void MaterialShader::RenderShader(
	ID3D11DeviceContext* deviceContext,
	int& indexCount)
{
	deviceContext->IASetInputLayout(m_layout);

	deviceContext->VSSetShader(m_vertexShader, 0, 0);
	deviceContext->PSSetShader(m_pixelShader, 0, 0);

	deviceContext->DrawIndexed(indexCount, 0, 0);
}

bool MaterialShader::SetShaderParameters(
	ID3D11DeviceContext* deviceContext,
	DirectX::XMMATRIX& worldMatrix,
	DirectX::XMMATRIX& viewMatrix,
	DirectX::XMMATRIX& projectionMatrix,
	DirectX::XMFLOAT3& lightDirection,
	DirectX::XMFLOAT4& ambientColor,
	DirectX::XMFLOAT4& diffuseColor,
	DirectX::XMFLOAT3& cameraPosition,
	DirectX::XMFLOAT4& specularColor,
	double& specularPower)
{
	worldMatrix = DirectX::XMMatrixTranspose(worldMatrix);
	viewMatrix = DirectX::XMMatrixTranspose(viewMatrix);
	projectionMatrix = DirectX::XMMatrixTranspose(projectionMatrix);

	if (!CreateMatrixDP(deviceContext, worldMatrix, viewMatrix, projectionMatrix))
	{
		return false;
	}

	if (!CreateCameraDP(deviceContext, cameraPosition))
	{
		return false;
	}
	
	if (!CreateLightDP(deviceContext, ambientColor, diffuseColor, lightDirection,
		specularColor, specularPower))
	{
		return false;
	}
	
	return true;
}

void MaterialShader::ShutdownShader()
{
	if (m_matrixBuffer)
	{
		m_matrixBuffer->Release();
		m_matrixBuffer = 0;
	}

	if (m_layout)
	{
		m_layout->Release();
		m_layout = 0;
	}

	if (m_pixelShader)
	{
		m_pixelShader->Release();
		m_pixelShader = 0;
	}

	if (m_vertexShader)
	{
		m_vertexShader->Release();
		m_vertexShader = 0;
	}
}