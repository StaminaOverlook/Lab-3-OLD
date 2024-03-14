#pragma once

#include "Platform.h"
#include "../InputDevice.h"

class PlatformPlayer : public Platform
{
private:
	InputDevice* inputDevice;
public:
	PlatformPlayer(Game* _game, int pos[2]) : Platform(_game, pos) {
		position[0] = pos[0];
		if (pos[0] < 0.0f) {
			position[0] += width;
		}
		else {
			position[0] -= width;
		}

		position[1] = pos[1];
	};

	PlatformPlayer();

	void Initialize() override;

	void Update() override;
};

