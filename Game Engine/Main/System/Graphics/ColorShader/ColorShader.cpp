#include "ColorShader.h"

ColorShader::ColorShader()
{
	//Initialize pointers
	m_layout = 0;
	m_matrixBuffer = 0;
	m_pixelShader = 0;
	m_vertexShader = 0;

	vertexShaderBuffer = 0;
	pixelShaderBuffer = 0;
}

ColorShader::ColorShader(const ColorShader& other)
{}

ColorShader::~ColorShader()
{}

bool ColorShader::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result = false;

	LPCWSTR vs = L"Main/System/Graphics/ColorShader/ColorShader_vs.hlsl";
	LPCWSTR ps = L"Main/System/Graphics/ColorShader/ColorShader_ps.hlsl";

	//Initialize vertex and pixel shaders
	result = InitializeShader(device, hwnd, vs, ps);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

bool ColorShader::Render(ID3D11DeviceContext* deviceContext,
	int indexCount, DirectX::XMMATRIX worldMatrix,
	DirectX::XMMATRIX viewMatrix, DirectX::XMMATRIX projectionMatrix)
{
	bool result = false;

	//Set shader parameters
	result = SetShaderParameters(deviceContext, worldMatrix, viewMatrix,
		projectionMatrix);
	if (!result)
	{
		return false;
	}

	//Render prepared buffers
	RenderShader(deviceContext, indexCount);

	return true;
}

void ColorShader::Shutdown()
{
	//Shutdown shaders
	ShutdownShader();
}

/////////////////////////////////////////////////////////
//Private
/////////////////////////////////////////////////////////

bool ColorShader::CompilerShaders(ID3D11Device* device, HWND hwnd, 
	LPCWSTR vsFilename, LPCWSTR psFilename)
{
	HRESULT result;

	ID3D10Blob* errorMessage = 0;

	//Compile vertex shader
	result = D3DCompileFromFile(vsFilename, NULL, NULL, "main",
		"vs_5_0", D3DCOMPILE_SKIP_OPTIMIZATION | D3DCOMPILE_DEBUG,
		NULL, &vertexShaderBuffer, &errorMessage);
	if (FAILED(result))
	{
		//If shader failed to compile
		if (errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, hwnd, vsFilename);
		}
		//If nothing is in error message, file could not compile
		else
		{
			MessageBox(hwnd, (LPCSTR)vsFilename,
				"Missing shader file", NULL);
		}

		return false;
	}

	//Compile pixel shader
	result = D3DCompileFromFile(psFilename, NULL, NULL, "main",
		"ps_5_0", D3DCOMPILE_SKIP_OPTIMIZATION | D3DCOMPILE_DEBUG,
		NULL, &pixelShaderBuffer, &errorMessage);
	if (FAILED(result))
	{
		//If shader failed to compile
		if (errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, hwnd, psFilename);
		}
		//If nothing is in error message, file could not compile
		else
		{
			MessageBox(hwnd, (LPCSTR)psFilename,
				"Missing shader file", NULL);
		}

		return false;
	}

	//Create shaders
	result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
	if (FAILED(result))
	{
		return false;
	}

	result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(),
		pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

bool ColorShader::CreateLayout(ID3D11Device* device)
{
	HRESULT result;

	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];

	unsigned int numElements;

	//Layout description
	//Matches VertexType struct
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "COLOR";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	//Get count of elements in layout
	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	//Create vertex input layout
	result = device->CreateInputLayout(polygonLayout, numElements,
		vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(), &m_layout);
	if (FAILED(result))
	{
		return false;
	}

	//Release shader buffers
	vertexShaderBuffer->Release();
	vertexShaderBuffer = 0;

	pixelShaderBuffer->Release();
	pixelShaderBuffer = 0;

	return true;
}

bool ColorShader::CreateMatrixCB(ID3D11Device* device)
{
	HRESULT result;

	D3D11_BUFFER_DESC matrixBufferDesc;

	//Matrix buffer description
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	//Create constant buffer
	result = device->CreateBuffer(&matrixBufferDesc, NULL,
		&m_matrixBuffer);
	if (FAILED(result))
	{
		return false;
	}
}

bool ColorShader::InitializeShader(ID3D11Device* device, HWND hwnd,
	LPCWSTR vsFilename, LPCWSTR psFilename)
{
	//Compile shaders
	if (!CompilerShaders(device, hwnd, vsFilename, psFilename))
	{
		return false;
	}

	//Setup layout
	if (!CreateLayout(device))
	{
		return false;
	}

	//Setup matrix constant buffer
	if (!CreateMatrixCB(device))
	{
		return false;
	}

	return true;
}

void ColorShader::OutputShaderErrorMessage(ID3D10Blob* errorMessage,
	HWND hwnd, LPCWSTR shaderFile)
{
	char* compilerErrors = 0;
	unsigned long bufferSize = 0;
	std::ofstream fout;

	//Get pointer to error message text buffer
	compilerErrors = (char*)errorMessage->GetBufferPointer();

	//Get length of message
	bufferSize = errorMessage->GetBufferSize();

	//Open file to write message
	fout.open("shader-error.txt");

	//Write out error message
	for (int i = 0; i < bufferSize; ++i)
	{
		fout << compilerErrors[i];
	}

	//Close file
	fout.close();

	//Release message
	errorMessage->Release();
	errorMessage = 0;

	//Show message to notify of error
	MessageBox(hwnd, "Error compiling shader. Check shader-error.txt.",
		(LPCSTR)shaderFile, MB_OK);
}

void ColorShader::RenderShader(ID3D11DeviceContext* deviceContext,
	int indexCount)
{
	//Set vertex input layout
	deviceContext->IASetInputLayout(m_layout);

	//Set shaders
	deviceContext->VSSetShader(m_vertexShader, NULL, 0);
	deviceContext->PSSetShader(m_pixelShader, NULL, 0);

	//Render
	deviceContext->DrawIndexed(indexCount, 0, 0);
}

bool ColorShader::SetShaderParameters(ID3D11DeviceContext* deviceContext,
	DirectX::XMMATRIX worldMatrix, DirectX::XMMATRIX viewMatrix,
	DirectX::XMMATRIX projectionMatrix)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;
	unsigned int bufferNumber = 0;

	//Transpose matrices
	worldMatrix = DirectX::XMMatrixTranspose(worldMatrix);
	viewMatrix = DirectX::XMMatrixTranspose(viewMatrix);
	projectionMatrix = DirectX::XMMatrixTranspose(projectionMatrix);

	//Lock constant buffer
	result = deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD,
		0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	//Get pointer to data in constant buffer
	dataPtr = (MatrixBufferType*)mappedResource.pData;

	//Copy matrices into buffer
	dataPtr->world = worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projectionMatrix;

	//Unlock buffer
	deviceContext->Unmap(m_matrixBuffer, 0);

	//Set position of buffer
	bufferNumber = 0;

	//Set buffer in vertex shader
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, 
		&m_matrixBuffer);
	
	return true;
}

void ColorShader::ShutdownShader()
{
	//Shutdown matrix constant buffer
	if (m_matrixBuffer)
	{
		m_matrixBuffer->Release();
		m_matrixBuffer = 0;
	}

	//Shutdown layout
	if (m_layout)
	{
		m_layout->Release();
		m_layout = 0;
	}

	//Release pixel shader
	if (m_pixelShader)
	{
		m_pixelShader->Release();
		m_pixelShader = 0;
	}

	//Release vertex shader
	if (m_vertexShader)
	{
		m_vertexShader->Release();
		m_vertexShader = 0;
	}
}