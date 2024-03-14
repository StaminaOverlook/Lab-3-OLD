#pragma once

#include <d3d.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include "GameComponent.h"

class TriangleComponent : public GameComponent
{
private:
	ID3D11InputLayout* layout;
	ID3D11PixelShader* pixelShader;
	ID3DBlob* pixelShaderByteCode = nullptr;
	DirectX::XMFLOAT4 points[3] = {
		DirectX::XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),
		DirectX::XMFLOAT4(-0.5f, -0.5f, 0.5f, 1.0f) };	//DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f),
	//	DirectX::XMFLOAT4(0.5f, -0.5f, 0.5f, 1.0f),	DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f),
	//	DirectX::XMFLOAT4(-0.5f, 0.5f, 0.5f, 1.0f),	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
	//};
	ID3D11RasterizerState* rastState;
	ID3D11VertexShader* vertexShader;
	ID3DBlob* vertexShaderByteCode = nullptr;
	int vertices;

	ID3DBlob* errorPixelCode = nullptr;
	ID3DBlob* errorVertexCode = nullptr;
	ID3D11Buffer* vb;
	ID3D11Buffer* ib;

public:
	TriangleComponent(Game* _game) : GameComponent(_game)
	{
		
	};
	TriangleComponent();

	void DestroyResources() override;

	void Draw() override;

	void Initialize() override;

	void Update() override;

	void Reload() override;
};

