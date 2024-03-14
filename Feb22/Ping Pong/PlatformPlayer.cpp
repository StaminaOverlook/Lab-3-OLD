#include "PlatformPlayer.h"
#include "PingPongGame.h"
#include "../Keys.h"

PlatformPlayer::PlatformPlayer()
{
}

void PlatformPlayer::Initialize() {
	inputDevice = game->GetInputDevice();

	auto res = D3DCompileFromFile(L"./Shaders/MyVeryFirstShader.hlsl",
		nullptr, // macros
		nullptr, //
		"VSMain",
		"vs_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		&vertexShaderByteCode,
		&errorVertexCode);

	if (FAILED(res)) {
		// If the shader failed to compile it should have written something to the error message.
		if (errorVertexCode) {
			char* compileErrors = (char*)(errorVertexCode->GetBufferPointer());

			std::cout << compileErrors << std::endl;
		}
		// If there was  nothing in the error message then it simply could not find the shader file itself.
		else
		{
			MessageBox(game->GetDisplay().GethWnd(), L"MyVeryFirstShader.hlsl", L"Missing Shader File", MB_OK);
		}
	}

	D3D_SHADER_MACRO Shader_Macros[] = { "TEST", "1", "TCOLOR", "float4(1.0f, 1.0f, 1.0f, 1.0f)", nullptr, nullptr };

	res = D3DCompileFromFile(L"./Shaders/MyVeryFirstShader.hlsl", Shader_Macros /*macros*/, nullptr /*include*/, "PSMain", "ps_5_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &pixelShaderByteCode, &errorPixelCode);

	game->GetDevice()->CreateVertexShader(
		vertexShaderByteCode->GetBufferPointer(),
		vertexShaderByteCode->GetBufferSize(),
		nullptr, &vertexShader);

	game->GetDevice()->CreatePixelShader(
		pixelShaderByteCode->GetBufferPointer(),
		pixelShaderByteCode->GetBufferSize(),
		nullptr, &pixelShader);

	D3D11_INPUT_ELEMENT_DESC inputElements[] = {
		D3D11_INPUT_ELEMENT_DESC {
			"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		D3D11_INPUT_ELEMENT_DESC{
			"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	game->GetDevice()->CreateInputLayout(inputElements, 2, vertexShaderByteCode->GetBufferPointer(), vertexShaderByteCode->GetBufferSize(), &layout);

	vertexBufDesc = {};
	vertexBufDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufDesc.CPUAccessFlags = 0;
	vertexBufDesc.MiscFlags = 0;
	vertexBufDesc.StructureByteStride = 0;
	vertexBufDesc.ByteWidth = sizeof(DirectX::XMFLOAT4) * std::size(points);

	vertexData = {};
	vertexData.pSysMem = points;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	game->GetDevice()->CreateBuffer(&vertexBufDesc, &vertexData, &vb);

	indexBufDesc = {};
	indexBufDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufDesc.CPUAccessFlags = 0;
	indexBufDesc.MiscFlags = 0;
	indexBufDesc.StructureByteStride = 0;
	indexBufDesc.ByteWidth = sizeof(int) * std::size(indeces);

	indexData = {};
	indexData.pSysMem = indeces;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	game->GetDevice()->CreateBuffer(&indexBufDesc, &indexData, &ib);

	rastDesc = {};
	rastDesc.CullMode = D3D11_CULL_NONE;
	rastDesc.FillMode = D3D11_FILL_SOLID;

	res = game->GetDevice()->CreateRasterizerState(&rastDesc, &rastState);
}

void PlatformPlayer::Update() {
	if (inputDevice->IsKeyDown(Keys::W)) {
		direction = 1.0f;
		std::cout << "Moving!";
		position[1] += direction * speed * game->GetDeltaTime();

		Move(position[0], position[1]);
	}
		
	if (inputDevice->IsKeyDown(Keys::S)) {
		direction = -1.0f;
		std::cout << "Moving!";
		position[1] += direction * speed * game->GetDeltaTime();

		Move(position[0], position[1]);
	}

//	vertexBufDesc.ByteWidth = sizeof(DirectX::XMFLOAT4) * std::size(points);
	vertexData.pSysMem = points;
	game->GetDevice()->CreateBuffer(&vertexBufDesc, &vertexData, &vb);

//	indexBufDesc.ByteWidth = sizeof(int) * std::size(indeces);
	indexData.pSysMem = indeces;

	game->GetDevice()->CreateBuffer(&indexBufDesc, &indexData, &ib);

	auto res = game->GetDevice()->CreateRasterizerState(&rastDesc, &rastState);
	Draw();
}