#include "Sphere.h"
#include "PlanetsGame.h"
#include "cmath"

using namespace DirectX;

Sphere::Sphere() {
}

inline PlanetsGame* Sphere::GetGame() const {
	return (PlanetsGame*)(game);
}

void Sphere::CreateSphere(float x, float y, float z){
	float phiStep = PI / stacks;
	float thetaStep = 2.0f * PI / slices;
	
	points.push_back({ 0, radius, 0, 1 });
	points.push_back({ 0, 1, 0, 1 });
	for (int i = 1; i <= stacks - 1; i++) {
		float phi = i * phiStep;
		for (int j = 0; j <= slices; j++) {
			float theta = j * thetaStep;
			Vector3 p = Vector3(
				(radius * sinf(phi) * cosf(theta)),
				(radius * cosf(phi)),
				(radius * sinf(phi) * sinf(theta))
			);
			points.push_back({ p.x,p.y,p.z,1 });
			points.push_back({ p.x,p.y,p.z,1 });
		}
	}
	points.push_back({ 0, -radius, 0, 1 });
	points.push_back({ 0, -radius, 0, 1 });

	for (int i = 1; i <= slices; i++) {
		indeces.push_back(0);
		indeces.push_back(i + 1);
		indeces.push_back(i);
	}
	int baseIndex = 1;
	int ringVertexCount = slices + 1;
	for (int i = 0; i < stacks - 2; i++) {
		for (int j = 0; j < slices; j++) {
			indeces.push_back(baseIndex + i * ringVertexCount + j);
			indeces.push_back(baseIndex + i * ringVertexCount + j + 1);
			indeces.push_back(baseIndex + (i + 1) * ringVertexCount + j);

			indeces.push_back(baseIndex + (i + 1) * ringVertexCount + j);
			indeces.push_back(baseIndex + i * ringVertexCount + j + 1);
			indeces.push_back(baseIndex + (i + 1) * ringVertexCount + j + 1);
		}
	}
	int southPoleIndex = points.size() / 2 - 1;
	baseIndex = southPoleIndex - ringVertexCount;
	for (int i = 0; i < slices; i++) {
		indeces.push_back(southPoleIndex);
		indeces.push_back(baseIndex + i);
		indeces.push_back(baseIndex + i + 1);
	}
}

void Sphere::Initialize() {
	auto res = D3DCompileFromFile(L"./Shaders/MyVeryFirstShader.hlsl", nullptr, nullptr, "VSMain", "vs_5_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &vertexShaderByteCode, &errorVertexCode);

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

	if (FAILED(res))
	{
		 
	}
	game->GetDevice()->CreateVertexShader(vertexShaderByteCode->GetBufferPointer(), vertexShaderByteCode->GetBufferSize(), nullptr, &vertexShader);

	game->GetDevice()->CreatePixelShader(pixelShaderByteCode->GetBufferPointer(), pixelShaderByteCode->GetBufferSize(), nullptr, &pixelShader);

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
	vertexData.pSysMem = &points;
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
	indexData.pSysMem = &indeces;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	game->GetDevice()->CreateBuffer(&indexBufDesc, &indexData, &ib);

	// Fill in a buffer description.
	D3D11_BUFFER_DESC cbDesc;
	cbDesc.ByteWidth = sizeof(XMFLOAT4X4);
	cbDesc.Usage = D3D11_USAGE_DYNAMIC;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;

	// Create the buffer.
	auto hr = game->GetDevice()->CreateBuffer(&cbDesc, nullptr, &ConstantBuffer);

	// Set the buffer.
	game->GetContext()->VSSetConstantBuffers(0, 1, &ConstantBuffer);

	rastDesc = {};
	rastDesc.CullMode = D3D11_CULL_NONE;
	rastDesc.FillMode = D3D11_FILL_SOLID;

	res = game->GetDevice()->CreateRasterizerState(&rastDesc, &rastState);
}

void Sphere::Draw() {
	UINT strides[] = { points.size() };
	UINT offsets[] = { 0 };

	world_matrix = XMMatrixTranspose(GetWorldMatrix());
	view_matrix = XMMatrixTranspose(GetGame()->GetCamera()->GetViewMatrix());
	projection_matrix = XMMatrixTranspose(GetGame()->GetCamera()->GetProjectionMatrix());

	game->GetContext()->RSSetState(rastState);

	game->GetContext()->IASetInputLayout(layout);
	game->GetContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	game->GetContext()->IASetIndexBuffer(ib, DXGI_FORMAT_R32_UINT, 0);
	game->GetContext()->IASetVertexBuffers(0, 1, &vb, strides, offsets);

	D3D11_MAPPED_SUBRESOURCE subresource{};
	game->GetContext()->Map(ConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subresource);

	Matrix m = world_matrix * view_matrix * projection_matrix;

	std::memcpy(subresource.pData, &m, sizeof(Matrix));
	game->GetContext()->Unmap(ConstantBuffer, 0);
	game->GetContext()->VSSetConstantBuffers(0, 1, &ConstantBuffer);

	game->GetContext()->VSSetShader(vertexShader, nullptr, 0);
	game->GetContext()->PSSetShader(pixelShader, nullptr, 0);

	game->GetContext()->DrawIndexed(indeces.size(), 0, 0);
}

void Sphere::Update() {
	vertexData.pSysMem = &points;
	game->GetDevice()->CreateBuffer(&vertexBufDesc, &vertexData, &vb);

	indexData.pSysMem = &indeces;

	game->GetDevice()->CreateBuffer(&indexBufDesc, &indexData, &ib);

	auto res = game->GetDevice()->CreateRasterizerState(&rastDesc, &rastState);
	Draw();
}