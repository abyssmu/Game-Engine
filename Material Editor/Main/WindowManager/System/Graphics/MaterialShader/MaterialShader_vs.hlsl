/*
ColorShader vertex shader
Simple shader that calculates world position of output
and assigns color;
*/

cbuffer MatrixBuffer
{
	matrix projectionMatrix;
	matrix viewMatrix;
	matrix worldMatrix;
};

cbuffer CameraBuffer
{
	float3 cameraPosition;
	float padding;
};

struct VertexInputType
{
	float4 color : COLOR;
	float3 normal : NORMAL;
	float4 position : POSITION;
};

struct PixelInputType
{
	float4 color : COLOR;
	float3 normal : NORMAL;
	float4 position : SV_POSITION;
	float3 viewDirection : TEXCOORD0;
};

PixelInputType main(VertexInputType input)
{
	PixelInputType output;
	float4 worldPosition = float4(0.0, 0.0, 0.0, 0.0);

	input.position.w = 1.0;

	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	output.color = input.color;

	output.normal = mul(input.normal, (float3x3)worldMatrix);
	output.normal = normalize(output.normal);

	worldPosition = mul(input.position, worldMatrix);

	output.viewDirection = cameraPosition.xyz - worldPosition.xyz;
	output.viewDirection = normalize(output.viewDirection);

	return output;
}