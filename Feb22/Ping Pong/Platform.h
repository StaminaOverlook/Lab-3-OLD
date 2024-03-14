#pragma once

#include "../GameComponent.h"
#include "Ball.h";
#include <iostream>
#include <DirectXMath.h>

using namespace std;

class Platform : public GameComponent
{
protected:
	float width = 0.01f;
	float height = 0.1f;

	float position[2] = { -1.0f + width, 0.0f };
	float direction = 1.0f;
	float speed = 0.2f;

	Ball* target;

	DirectX::BoundingBox Collider;

	int indeces[6] = { 0, 1, 2, 1, 0, 3 };

	//This is 0, 0 position of the ball.
	DirectX::XMFLOAT4 points[8] = {
		DirectX::XMFLOAT4(width, 	height,	0.0f,	1.0f), // right upper corner
		DirectX::XMFLOAT4(0.00f,	0.00f,	0.0f,	1.0f), // ????
		DirectX::XMFLOAT4(-width,	-height,	0.0f,	1.0f), // left lower corner
		DirectX::XMFLOAT4(0.00f,	0.00f,	0.0f,	1.0f), // ???
		DirectX::XMFLOAT4(width, 	-height,	0.0f,	1.0f), // right lower corner
		DirectX::XMFLOAT4(0.00f,	0.00f,	0.0f,	1.0f), // ???
		DirectX::XMFLOAT4(-width,	height,	0.0f,	1.0f), // left upper corner
		DirectX::XMFLOAT4(0.00f,	0.00f,	0.0f,	1.0f) // ???
	};

public:
	Platform(Game* _game, int pos[2]) : GameComponent(_game) {
		position[0] = pos[0];
		if (pos[0] < 0.0f) {
			position[0] += width;
		}
		else {
			position[0] -= width;
		}

		position[1] = pos[1];

		Collider.Center.x = position[0];
		Collider.Center.y = position[1];
		Collider.Center.z = 0.0f;
		Collider.Extents.x = width;
		Collider.Extents.y = height;
		Collider.Extents.z = 0.0f;
	};

	Platform();

	DirectX::BoundingBox GetCollider() {
		return Collider;
	}
	float Position(int i) {
		return position[i];
	}
	float GetWidth() {
		return width;
	}
	float GetHeight() {
		return height;
	}

	void SetTarget(Ball* ball) {
		target = ball;
	}

	void Initialize() override;

	void Draw() override;

	void Update() override;

	void Move(float x, float y);
};

