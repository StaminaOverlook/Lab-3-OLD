#pragma once

#include "../Game.h"
#include "Ball.h"
#include "Platform.h"
#include "PlatformPlayer.h"

class PingPongGame : public Game
{
private:
	std::vector <Platform*> Players;
	Ball* ball;

public:
	void AssignBall(Ball* _ball) {
		ball = _ball;
	}
	Ball* GetBall() {
		return ball;
	}

	PingPongGame();

	void AddPlayer(Platform* pl) {
		Players.push_back(pl);
	}
	std::vector <Platform*> GetPlayers() {
		return Players;
	}

	void Update();
};

