//ColorShader pixel shader
//Simple shader that returns the color of the pixel

struct PixelInputType
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

float4 main(PixelInputType input) : SV_TARGET
{
	return input.color;
}