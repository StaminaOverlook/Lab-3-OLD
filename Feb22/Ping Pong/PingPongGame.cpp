#include "PingPongGame.h"

void PingPongGame::Update() {
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// If windows signals to end the application then exit out.
	if (msg.message == WM_QUIT) {
		isExitRequested = true;
	}

	for (int i = 0; i < Components.size(); i++) {
		Components[i]->Update();
	}

	std::vector <Platform*> players = GetPlayers();

	for (int i = 0; i < players.size(); i++) {
		if (GetBall()->GetCollider().Intersects(players[i]->GetCollider())) {
			GetBall()->direction[0] = - GetBall()->direction[0];
			GetBall()->speed += 0.001f;
		}
	}

	Context->ClearState();
}