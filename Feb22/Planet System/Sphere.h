#pragma once

#include "../GameComponent.h"
#include <d3d.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include "SimpleMath.h"
#include "DirectXCollision.h"
#include "GeometricPrimitive.h"
#include "SimpleMath.h"

using namespace DirectX;
using namespace SimpleMath;

class PlanetsGame;
class Sphere : public GameComponent
{
private:
    float radius = 1.0f;
    int stacks = 16;
    int slices = 16;
    float PI = 3.14;

    std::vector<Vector4> points;
    std::vector<int> indeces;

	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

	Matrix model_matrix;

	Matrix world_matrix;
	Matrix view_matrix;
	Matrix projection_matrix;

	// Po * World * View * Projection

public:
    Sphere();

	PlanetsGame* GetGame() const;

	Matrix GetWorldMatrix() {
		return Matrix::Identity *
			XMMatrixScalingFromVector(scale) *
			XMMatrixRotationRollPitchYawFromVector(rotation) *
			XMMatrixTranslationFromVector(position);
	}

    void CreateSphere(float x = 0.0f, float y = 0.0f, float z = 0.0f);

    void Initialize() override;

    void Draw() override;

    void Update() override;

	void Move();
};

