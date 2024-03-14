//#include "Ping Pong/PingPongGame.h"
//#include "Ping Pong/Ball.h"
//#include "Ping Pong/Platform.h"
//#include "Ping Pong/PlatformPlayer.h"

#include "Planet System/PlanetsGame.h"
#include "Planet System/Camera.h"
#include "Planet System/Sphere.h"

void Planets(PlanetsGame* game) {


}

int main() {
	PlanetsGame* game = new PlanetsGame();

	Camera* camera = new Camera();
	game->AddComponent(camera);
	game->AssignCamera(camera);

	Sphere* s1 = new Sphere();
	s1->CreateSphere(0.0f, 0.0f, -2.0f);
	game->AddComponent(s1);

	game->Run();
}

/*void PingPong(PingPongGame* game) {

	Ball* ball = new Ball(game);
	game->AddComponent(ball);
	game->AssignBall(ball);

	int pos[2] = { 1.0f, 0.0f };
	PlatformPlayer* Player = new PlatformPlayer(game, pos);
	game->AddComponent(Player);
	game->AddPlayer(Player);
	Player->SetTarget(ball);

	pos[0] = -1.0f;
	Platform* AI = new Platform(game, pos);
	game->AddComponent(AI);
	game->AddPlayer(AI);

	game->Run();
}*/
