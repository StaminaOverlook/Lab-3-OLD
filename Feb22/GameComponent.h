#pragma once

#include <d3d.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include "SimpleMath.h"
#include "DirectXCollision.h"

class Game;
class GameComponent
{
public:
	Game* game;
protected:
	D3D11_BUFFER_DESC indexBufDesc = {};
	D3D11_SUBRESOURCE_DATA indexData = {};
	int indeces[6] = {};

	CD3D11_RASTERIZER_DESC rastDesc = {};
	D3D11_BUFFER_DESC vertexBufDesc = {};
	D3D11_SUBRESOURCE_DATA vertexData = {};

	ID3D11InputLayout* layout;
	ID3D11PixelShader* pixelShader;
	ID3DBlob* pixelShaderByteCode = nullptr;

	//This is 0, 0 position of the ball.
	DirectX::XMFLOAT4 points[8] = {};
	ID3D11RasterizerState* rastState;
	ID3D11VertexShader* vertexShader;
	ID3DBlob* vertexShaderByteCode = nullptr;
	int vertices;

	ID3DBlob* errorPixelCode = nullptr;
	ID3DBlob* errorVertexCode = nullptr;
	ID3D11Buffer* vb;
	ID3D11Buffer* ib;

	ID3D11Buffer* ConstantBuffer = NULL;

public:
	GameComponent(Game* _game) : game(_game) {

	}

	GameComponent();

	void virtual DestroyResources();

	void virtual Draw();

	void virtual Initialize();

	void virtual Reload();

	void virtual Update();
};

