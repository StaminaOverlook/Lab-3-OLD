#pragma once

#include "../GameComponent.h"

class Ball : public GameComponent
{
private:
	float size = 0.03f;

	DirectX::BoundingBox Collider;

	int indeces[6] = { 0, 1, 2, 1, 0, 3 };
	DirectX::XMFLOAT4 points[8] = {
	DirectX::XMFLOAT4(size, 	size,	0.0f,	1.0f), // right upper corner
	DirectX::XMFLOAT4(0.00f,	0.00f,	0.0f,	1.0f), // ????
	DirectX::XMFLOAT4(-size,	-size,	0.0f,	1.0f), // left lower corner
	DirectX::XMFLOAT4(0.00f,	0.00f,	0.0f,	1.0f), // ???
	DirectX::XMFLOAT4(size, 	-size,	0.0f,	1.0f), // right lower corner
	DirectX::XMFLOAT4(0.00f,	0.00f,	0.0f,	1.0f), // ???
	DirectX::XMFLOAT4(-size,	size,	0.0f,	1.0f), // left upper corner
	DirectX::XMFLOAT4(0.00f,	0.00f,	0.0f,	1.0f) // ???
	};

public:
	float position[2] = { 0.0f, 0.0f };
	float direction[2] = { 0.5f, 1.0f };
	float speed = 0.2f;

	Ball(Game* _game) : GameComponent(_game)
	{

	};
	Ball();

	DirectX::BoundingBox GetCollider() {
		return Collider;
	}
	float Position(int i) const {
		return position[i];
	}

	void SetPosition(float x, float y) {
		position[0] = x;
		position[1] = y;
	}
	void SetDirection(float x, float y) {
		direction[0] = x;
		direction[1] = y;
	}

	void Initialize() override;

	void Draw() override;

	void Update() override;

	void Move(float x, float y);

	void CheckForWalls();
};

