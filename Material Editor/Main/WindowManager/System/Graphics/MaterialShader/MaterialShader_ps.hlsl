/*
ColorShader pixel shader
Simple shader that returns the color of the pixel
*/

cbuffer LightBuffer
{
	float4 ambientColor;
	float4 diffuseColor;
	float3 lightDirection;
	float specularPower;
	float4 specularColor;
};

struct PixelInputType
{
	float4 color : COLOR;
	float3 normal : NORMAL;
	float4 position : SV_POSITION;
	float3 viewDirection : TEXCOORD0;
};

float4 main(PixelInputType input) : SV_TARGET
{
	float4 endColor = ambientColor;
	float3 lightDir = -lightDirection;
	float lightIntensity = saturate(dot(input.normal, lightDir));
	float4 specular = float4(0.0, 0.0, 0.0, 0.0);

	if (lightIntensity > 0.0)
	{
		endColor += diffuseColor * lightIntensity;
		endColor = saturate(endColor);

		float3 reflection = normalize(((2 * lightIntensity) * input.normal) - lightDir);

		specular = pow(saturate(dot(reflection, input.viewDirection)), specularPower) * specularColor;
	}

	endColor = endColor * input.color;
	endColor = saturate(endColor + specular);

	return endColor;
}